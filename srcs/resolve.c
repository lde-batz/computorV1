

#include "computor.h"


void    printReductEquation(t_computor_list *reductEquation) {
    t_computor_list *equation = reductEquation;

    printf("           <=> ");
    if (equation->number == 0) {
        printf("0 = 0\n");
        equation->power = 0;
        return;
    }
    while (equation) {
        if (equation->power == 0) {
            printf("%g", equation->number);
        } else if (equation->power == 1 || equation->power == 2) {
            if (equation == reductEquation) {
                printf("%g * X", equation->number);
            } else {
                (equation->number < 0) ? printf(" - ") : printf(" + ");
                printf("%g * X", ft_absf(equation->number));
            }
            if (equation->power == 2)
                printf("^2");
        }
        equation = equation->next;
    }
    printf(" = 0\n");
    
}

int     polynomialDegree(t_computor_list *equation) {
    int max = 0;

    while (equation) {
        if (equation->power > max)
            max = equation->power;
        equation = equation->next;
    }
    printf("Polynomial degree: %i\n", max);
    return max;
}

void    resolveEquationDegree0(t_computor_list *equation) {
    if (equation->number == 0) {
        printf("The solution is : X belong to R.\n");
    } else {
        printf("The equation is wrong. There is no solution.\n");
    }
    free(equation);
}

void    resolveEquationDegree1(t_computor_list *equation) {
    double  a = 0;
    double  b = 0;
    double  x;
    int     numerator = 0;
    int     denominator = 0;
    t_computor_list *freeT;
    
    while (equation) {
        if (equation->power == 0) {
            b = equation->number;
        } else if (equation->power == 1) {
            a = equation->number;
        }

        freeT = equation;
        equation = equation->next;
        free(freeT);
    }
    printf("Resolution:\n");
    if (b == 0) {
        printf("    %g * X = 0\n<=>     X = 0\n", a);
        printf("\nThe solution is: X = 0\n");
    } else {
        x = -b / a;
        printf("    %g", b);
        (a < 0) ? printf(" - ") : printf(" + ");
        printf("%g * X = 0\n", ft_absf(a));
        printf("<=> %g * X = %g\n", a, -b);
        printf("<=> X = %g / %g\n", -b, a);
        printf("\nThe solution is: X = %g", x);
        if (x != (int)x)
            floatToFraction(x, &numerator, &denominator);
        if (numerator && denominator)
            printf(" = %i / %i", numerator, denominator);
        printf("\n");
    }
}

void    solveEquation(char *equation)
{
    t_computor_list *reductEquation = parcingEquation(equation);

    if (reductEquation == NULL) {
        return ;
    }

    printReductEquation(reductEquation);

    int     maxPolynom = polynomialDegree(reductEquation);

    if (maxPolynom == 0) {
        resolveEquationDegree0(reductEquation);
    } else if (maxPolynom == 1) {
        resolveEquationDegree1(reductEquation);
    } else if (maxPolynom == 2) {
        resolveEquationDegree2(reductEquation);
    }
    freeT_computor(reductEquation);
}

