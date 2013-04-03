#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "large_number.h"

char digitals_equal(const char *n1, const char *n2)
{
    int len = strlen(n1);
    if (len != strlen(n2))
        return 0;

    char bitmap[16] = {0};
    int i;
    for (i=0; i<len; i++)
    {
        int d = *(n1 + i) - '0';
        bitmap[d]++;
    }

    for (i=0; i<len; i++)
    {
        int d = *(n2 + i) - '0';
        bitmap[d]--;
    }

    for (i=0; i<10; i++)
    {
        if (bitmap[i] != 0)
            return 0;
    }

    return 1;
}

int main(int argc, const char *argv[])
{
    int n;
    for (n=1; n<0xffffffff; n++)
    {
        char s[16];
        char d[16];
        sprintf(s, "%d", n);

        ln_multiply(s, "2", d, 16);
        char ret = digitals_equal(s, d);
        if (ret == 0)
            continue;

        ln_multiply(s, "3", d, 16);
        ret = digitals_equal(s, d);
        if (ret == 0)
            continue;

        ln_multiply(s, "4", d, 16);
        ret = digitals_equal(s, d);
        if (ret == 0)
            continue;

        ln_multiply(s, "5", d, 16);
        ret = digitals_equal(s, d);
        if (ret == 0)
            continue;

        ln_multiply(s, "6", d, 16);
        ret = digitals_equal(s, d);
        if (ret == 0)
            continue;

        printf("%s\n", s);
        break;
    }

    return 0;
}
