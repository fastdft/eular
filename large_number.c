#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "large_number.h"

static
int from_digital(const char *digital, int out[])
{
    int len = strlen(digital);
    int i;
    for (i=0; i<len; i++)
    {
        assert(*(digital + i) <= '9' && *(digital + i) >= 0);
        out[i] = *(digital + len -1 - i) - '0';
    }

    return len;
}

static
int to_digital(const int num[], int num_size, char *dig)
{
    int i;
    for (i=0; i<num_size; i++)
    {
        assert(num[i] >= 0 && num[i] <= 9);
        *(dig + num_size - 1 - i) = '0' + num[i];
    }
    *(dig + num_size) = 0;

    return num_size;
}

static
int array_to_base(int array[], int array_length, int limit, int base)
{
    int i, ret;

    ret = 0;
    for (i=0; i<array_length && i<limit; i++)
    {
        int k;
        int number = array[i];
        assert(number >= 0);
        array[i] %= base;

        for (k=i+1, number/=base; number>0 && k<limit; k++, number/=base)
        {
            array[k] += (number % base);
        }

        ret = (ret > k ? ret : k);
    }
    
    return ret;
}

static
int multiply_array_array(int array1[], int array1_length, int array2[], int array2_length, int array_out[], int limit)
{
    int i;
    int length = 0;

    for (i=0; i<limit; i++)
        array_out[i] = 0;

    for (i=0; i<array2_length && i<limit; i++)
    {
        int j;
        for (j=0; j<array1_length && i+j<limit; j++)
        {
            assert(array1[j] >= 0 && array1[j] <= 9);
            assert(array2[i] >= 0 && array2[i] <= 9);

            array_out[j + i] += array2[i] * array1[j];
            //************notice the difference between length and index
            length = (i+j+1 > length? i+j+1 : length);
        }
    }

    return array_to_base(array_out, length, limit, 10);
}

static
int add_array_array(int array1[], int array1_length, int array2[], int array2_length, int array_out[], int limit)
{
    int i, length, ret, longer;

    if (array1_length > array2_length)
    {
        longer = 1;
        length = array1_length;
    }
    else
    {
        longer = 2;
        length = array2_length;
    }

    length = (length > limit ? limit : length);

    for (i=0; i<array1_length && i<array2_length; i++)
    {
        //in order to avoid overflow of int
        assert(array1[i] >= 0 && array1[i] <= 9);
        assert(array2[i] >= 0 && array2[i] <= 9);
        array_out[i] = array1[i] + array2[i];
    }
    for (; i<length; i++)
    {
        array_out[i] = (longer == 1 ? array1[i] : array2[i]);
        assert(array_out[i] >= 0 && array_out[i] <= 9);
    }

    ret = array_to_base(array_out, length, limit, 10);

    return ret;
}


int ln_multiply(const char *dig1, const char *dig2, char *dig_out, int out_size)
{
    int dig1_len = strlen(dig1);
    int dig2_len = strlen(dig2);

    int *num1 = (int *)malloc(sizeof(int) * (dig1_len + 1));
    int *num2 = (int *)malloc(sizeof(int) * (dig2_len + 1));
    int ret = from_digital(dig1, num1);
    assert(ret == dig1_len);
    ret = from_digital(dig2, num2);
    assert(ret == dig2_len);

    int *num_out = (int *)malloc(sizeof(int) * (dig1_len + dig2_len + 1));

    ret = multiply_array_array(num1, dig1_len, num2, dig2_len, num_out, dig1_len + dig2_len);

    assert(out_size >= ret);
    ret = to_digital(num_out, ret, dig_out);

    return ret;
}

int ln_add(const char *num1, const char *num2, char *num_out, int out_size)
{
    return 0;
}

int ln_subtract(const char *num1, const char *num2, char *num_out, int out_size)
{
    return 0;
}
/*
int main()
{
    const char *num1 = "8907";
    const char *num2 = "8273";

    char *out = (char *)malloc(1000);
    ln_multiply(num1, num2, out, 1000);
    printf("%s\n", out);

    free(out);
}
*/ 
