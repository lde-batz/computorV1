



#include "computor.h"


int     PGCD(int a, int b) {
    if (b == 0)
        return a;
    else
        return PGCD(b, a % b);
}

void    irreducFract(int *a, int *b) {
    int intPGCD = PGCD(*a, *b);

    if (intPGCD != 0) {

        *a /= intPGCD;
        *b /= intPGCD;
    }
}

void    decimalToFraction(double x, int len, int *a, int *b) {
    *b = ft_pow(10, len);
    *a = x * *b;
    irreducFract(a, b);
}

void    infinitDecimalToFraction(double x, int *a, int *b) {
    int start = -1;
    int i = -1;
    int j, k, len;
    double x1, x2;

    while (++i < 6) {
        j = 0;
        start = i;
        while (++j < 5) {
            k = 0;
            len = j;
            while (++k < 6) {
                x1 = x * ft_pow(10, start);
                x1 -= (int)x1;
                x1 *= ft_pow(10, len);
                x2 = x * ft_pow(10, start + (len * k));
                x2 -= (int)x2;
                x2 *= ft_pow(10, len);
                if ((int)x1 != (int)x2)
                    k = 9;
            }
            if (k == 6) {
                i = 9;
                j = 9;
            }
        }
    }
    if (i == 10) {
        *a = (int)(x * ft_pow(10, start + len)) - (int)(x * ft_pow(10, start));
        *b = ft_pow(10, start + len) - ft_pow(10, start);
        irreducFract(a, b);
    } else {
        *a = 0;
        *b = 0;
    }
}

void    floatToFraction(double x, int *a, int *b) {
    double  copy;
    int     len = 0;
    int     sign = (x < 0) ? 0 : 1;

    x = (x < 0) ? -x : x;
    copy = x - (int)x;
    while (copy != (int)copy && len++ <= 6) {
        copy *= 10;
        copy -= (int)copy;
    }
    if (copy == (int)copy)
        decimalToFraction(x, len, a, b);
    else
        infinitDecimalToFraction(x, a, b);
    if (!sign)
        *a = -*a;
}
