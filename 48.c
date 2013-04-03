#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

int main(int argc, const char *argv[])
{
    int limit;
    int i;
    int digitals_sum[10];
    int digitals_sum_length;

    if (argc != 2)
        return -1;

    limit = atoi(argv[1]);

    memset(digitals_sum, 0, sizeof(digitals_sum));
    digitals_sum_length = 0;
    for (i=1; i<=limit; i++)
    {
        int digitals[10];
        int digitals_length;
        int j;
        int iter;
        int tmp[10], tmp2[10];
        int tmp_length;
        char digitals_init;

        //compute digitals
        memset(digitals, 0, sizeof(digitals));
        digitals_length = 0;
        memset(tmp, 0, sizeof(tmp));
        memset(tmp2, 0, sizeof(tmp2));

        tmp[0] = i;
        tmp_length = array_to_base(tmp, 1, 10, 10);
        digitals_init = 0;
        for (iter=i; iter; iter>>=1)
        {
            if (iter & 0x01)
            {
                if (digitals_init)
                {
                    digitals_length = multiply_array_array(digitals, digitals_length, tmp, tmp_length, tmp2, 10);
                    memcpy(digitals, tmp2, digitals_length * sizeof(int));
                }
                else
                {
                    memcpy(digitals, tmp, tmp_length * sizeof(int));
                    digitals_length = tmp_length;
                    digitals_init = 1;
                }
            }

            //update tmp
            tmp_length = multiply_array_array(tmp, tmp_length, tmp, tmp_length, tmp2, 10);
            memcpy(tmp, tmp2, tmp_length * sizeof(int));
        }

        //compute sum
        memset(tmp, 0, sizeof(tmp));
        digitals_sum_length = add_array_array(digitals, digitals_length, digitals_sum, digitals_sum_length, tmp, 10);
        memcpy(digitals_sum, tmp, digitals_sum_length * sizeof(int));
    }
    
    for (i=9; i>=0; i--)
        printf("%d", digitals_sum[i]);

    printf("\n\n");

    return 0;
}
