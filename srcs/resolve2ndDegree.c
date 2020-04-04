


#include "computor.h"

double ft_sqrtf(const double m)
{
   double i = 0;
   double x1, x2;

   while (i * i <= m)
        i += 0.1f;
   x1 = i;
   for(int j = 0; j < 10; j++) {
        x2 = m;
        x2 /= x1;
        x2 += x1;
        x2 /= 2;
        x1 = x2;
   }
   return x2;
} 

void    resolveDiscPos(double disc, double a, double b) {
    double  sqrtDisc = ft_sqrtf(disc);
    double  x1 = (-b - sqrtDisc) / (2 * a);
    double  x2 = (-b + sqrtDisc) / (2 * a);
    int numerator = 0;
    int denominator = 0;

    printf("\nDiscriminant is strictly positive then:\n");
    printf("x1 = ( −(%g) − √%g ) / ( 2 * %g )\n", b, disc, a);
    if (sqrtDisc == (int)sqrtDisc) {
        printf("   = %g / %g\n   = %g\n", -b - sqrtDisc, 2 * a, x1);
    } else {
        printf("   = ( %g - %g ) / %g\n", -b, sqrtDisc, 2 * a);
        printf("   = %g / %g\n   = %g\n", -b - sqrtDisc, 2 * a, x1);
    }

    printf("and\n");
    printf("x2 = ( −(%g) + √%g ) / ( 2 * %g )\n", b, disc, a);
    if (sqrtDisc == (int)sqrtDisc) {
        printf("   = %g / %g\n   = %g\n", -b + sqrtDisc, 2 * a, x2);
    } else {
        printf("   = ( %g + %g ) / %g\n", -b, sqrtDisc, 2 * a);
        printf("   = %g / %g\n   = %g\n", -b + sqrtDisc, 2 * a, x2);
    }
    if (x1 != (int)x1)
        floatToFraction(x1, &numerator, &denominator);
    printf("\nThe two solutions are:\n%g", x1);
    if (numerator && denominator) {
        printf(" = %i / %i", numerator, denominator);
    }
    if (x2 != (int)x2)
        floatToFraction(x2, &numerator, &denominator);
    printf("\nand\n%g", x2);
    if (numerator && denominator) {
        printf(" = %i / %i", numerator, denominator);
    }
    printf("\n");
}

void    resolveDiscZero(double a, double b) {
    double x = -b / (2 * a);
    int numerator = 0;
    int denominator = 0;

    printf("\nDiscriminant is zero then:\nx = -(%g) / (2 * %g)\n", b, a);
    printf("  = %g / %g\n  = %g\n", -b, 2 * a, x);
    if (x != (int)x)
        floatToFraction(x, &numerator, &denominator);
    printf("\nThe solution is: %g", x);
    if (numerator && denominator)
        printf(" = %i / %i", numerator, denominator);
    printf("\n");
}

void    resolveDiscNeg(double disc, double a, double b) {
    double  sqrtDisc = ft_sqrtf(-disc);
    double  solReal = -b / (2 * a);
    double  solImag = sqrtDisc / (2 * a);
    int numReal = 0;
    int denReal = 0;
    int numImag = 0;
    int denImag = 0;

    printf("\nDiscriminant is strictly negative then:\n");
    printf("x1 = ( −(%g) − i√(-(%g)) / ( 2 * %g )\n", b, disc, a);
    if (sqrtDisc == (int)sqrtDisc) {
        printf("   = ( %g - %gi ) / %g\n", -b, sqrtDisc, 2 * a);
        printf("   = %g - %gi\n", solReal, solImag);
    } else {
        printf("   = ( %g - i√%g ) / %g\n", -b, -disc, 2 * a);
        printf("   = (%g / %g) - (%gi / %g)\n", -b, 2 * a, sqrtDisc, 2 * a);
        printf("   = %g - %gi\n", solReal, solImag);
    }
    printf("and\n");
    printf("x2 = ( −(%g) + i√(-(%g)) / ( 2 * %g )\n", b, disc, a);
    if (sqrtDisc == (int)sqrtDisc) {
        printf("   = ( %g + %gi ) / %g\n", -b, sqrtDisc, 2 * a);
        printf("   = %g + %gi\n", solReal, solImag);
    } else {
        printf("   = ( %g + i√%g ) / %g\n", -b, -disc, 2 * a);
        printf("   = (%g / %g) + (%gi / %g)\n", -b, 2 * a, sqrtDisc, 2 * a);
        printf("   = %g + %gi\n", solReal, solImag);
    }
    if (solReal != (int)solReal)
        floatToFraction(solReal, &numReal, &denReal);
    if (solImag != (int)solImag)
        floatToFraction(solImag, &numImag, &denImag);
    printf("\nThe two solutions are:\n%g - %gi", solReal, solImag);
    if ((numReal && numReal) || (numImag && denImag)) {
        if (numReal && denReal)
            printf(" = %i / %i", numReal, denReal);
        else
            printf(" = %g", solReal);
        if (numImag && denImag)
            printf(" - %ii / %i", numImag, denImag);
        else
            printf(" - %gi", solImag);
    }
    printf("\nand\n%g + %gi", solReal, solImag);
    if ((numReal && numReal) || (numImag && denImag)) {
        if (numReal && denReal)
            printf(" = %i / %i", numReal, denReal);
        else
            printf(" = %g", solReal);
        if (numImag && denImag)
            printf(" + %ii / %i", numImag, denImag);
        else
            printf(" + %gi", solImag);
    }
    printf("\n");
}

void    resolveEquationDegree2(t_computor_list *equation) {
    double  a = 0;
    double  b = 0;
    double  c = 0;
    t_computor_list *freeT;
    
    while (equation) {
        if (equation->power == 0) {
            c = equation->number;
        } else if (equation->power == 1) {
            b = equation->number;
        } else if (equation->power == 2) {
            a = equation->number;
        }

        freeT = equation;
        equation = equation->next;
        free(freeT);
    }

    double  disc = (b * b) - (4 * a * c);
    printf("\nRESOLUTION:\nDiscriminant = (%g)² - 4 * %g * %g\n", b, a, c);
    printf("             = %g\n", disc);

    if (10.0000001 == (int)10.0000001) {
        printf("OOUI\n");
    }

    if (disc > 0) {
        resolveDiscPos(disc, a, b);
    } else if (disc == 0) {
        resolveDiscZero(a, b);
    } else {
        resolveDiscNeg(disc, a, b);
    }
}