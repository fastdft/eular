#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    int i;
    int digitals[1024] = {0};
    int max_length = 0;
    int sum = 0;
    int num = 0;

    if (argc != 2)
    {
        printf("error parameters\n");
        return -1;
    }

    num = atoi(argv[1]);

    digitals[0] = 1;
    max_length = 1;
    for (i=2; i<=num; i++)
    {
        int j;

        for (j=0; j<max_length; j++)
        {
            digitals[j] *=i;
        }

        for (j=0; j<max_length; j++)
        {
            int k;
            int number = digitals[j];
            digitals[j] %= 10;
            for (k=j+1, number /= 10; number; k++, number /= 10)
            {
                int last = number % 10;
                digitals[k] += last;
                if (k+1 > max_length)
                    max_length = k + 1;
            }
        }
    }

    sum = 0;
    for (i=0; i<max_length; i++)
    {
        printf("%d", digitals[i]);
        sum += digitals[i];
    }

    printf("\n%d\n", sum);
}
