


#include "computor.h"


char        *deleteWhiteSpaces(char *str) {
    char    *cleanStr;
    int     len = 0;
    int     i = -1;

    while (str[++i]) {
        if (!(str[i] >= 9 && str[i] <= 13) && str[i] != ' ')
            len++;
    }
    cleanStr = (char*)malloc(sizeof(char) * (len + 1));
    i = -1;
    len = 0;
    while (str[++i]) {
        if (!(str[i] >= 9 && str[i] <= 13) && str[i] != ' ')
            cleanStr[len++] = str[i];
    }
    return cleanStr;
}

void            deleteDuplicatesPower(t_computor_list *leftSideEquation) {
    t_computor_list *leftEquation = leftSideEquation;
    t_computor_list *equation;
    t_computor_list *save;
    t_computor_list *freeT;

    while (leftEquation->next) {
        equation = leftEquation->next;
        save = leftEquation;
        while (equation) {
            if (leftEquation->power == equation->power) {
                leftEquation->number += equation->number;
                freeT = equation;
                equation = equation->next;
                free(freeT);
                save->next = equation;
            } else {
                equation = equation->next;
                save = save->next;
            }
        }
        if (leftEquation->next)
            leftEquation = leftEquation->next;
    }
}

t_computor_list *reductionEquation(t_computor_list *leftSideEquation, t_computor_list *rightEquation) {
    t_computor_list *leftEquation;
    t_computor_list *save;
    int             newPower;

    while (rightEquation) {
        leftEquation = leftSideEquation;
        newPower = 0;

        while (leftEquation) {
            if (leftEquation->power == rightEquation->power) {
                leftEquation->number -= rightEquation->number;
                leftEquation = NULL;
            } else if (leftEquation->next == NULL) {
                newPower = 1;
                leftEquation = NULL;
            } else {
                leftEquation = leftEquation->next;
            }
        }
        save = rightEquation;
        rightEquation = rightEquation->next;
        if (newPower == 1) {
            save->next = leftSideEquation;
            leftSideEquation = save;
        } else {
            free(save);
        }
    }
    return leftSideEquation;
}

void    printBadReductEquation(t_computor_list *reductEquation) {
    t_computor_list *equation = reductEquation;

    printf("Reducted form: ");
    while (equation) {
        if (equation == reductEquation) {
            printf("%g * X^%i", equation->number, equation->power);
        } else {
            (equation->number < 0) ? printf(" - ") : printf(" + ");
            printf("%g * X^%i", ft_absf(equation->number), equation->power);
        }
        equation = equation->next;
    }
    printf(" = 0\n");
    
}

t_computor_list *checkGoodPower(t_computor_list *leftEquation) {
    t_computor_list *equation = leftEquation;
    t_computor_list *save = leftEquation;

    while (equation) {
        if ((equation->power < 0 || equation->power > 2) && equation->number != 0) {
            printf("ERROR!!! Impossible to resolve equation with a polynomial degree = %i\n", equation->power);
            freeT_computor(leftEquation);
            return NULL;
        } else if (equation->number == 0) {
            if (equation == leftEquation) {
                if (equation->next) {
                    leftEquation = leftEquation->next;
                    save = leftEquation;
                    free(equation);
                    equation = NULL;
                }
            } else{
                save->next = equation->next;
                free(equation);
                equation = save;
            }
        }
        equation = (equation) ? equation->next : leftEquation;
        save = (save == equation || save->next == equation) ? save : save->next;
    }
    return leftEquation;
}

t_computor_list *sortEquation(t_computor_list *equation) {
    t_computor_list *sortEquation = equation;
    t_computor_list *swapEquation;
    t_computor_list *swapEquation2;
    double          swapDouble;
    int             swapInt;

    while (sortEquation->next) {
        swapEquation = equation;
        while(swapEquation->next) {
            swapEquation2 = swapEquation->next;
            if (swapEquation->power > swapEquation2->power) {
                swapDouble = swapEquation->number;
                swapEquation->number = swapEquation2->number;
                swapEquation2->number = swapDouble;
                swapInt = swapEquation->power;
                swapEquation->power = swapEquation2->power;
                swapEquation2->power = swapInt;
            }
            swapEquation = swapEquation->next;
        }
        sortEquation = sortEquation->next;
    }
    return equation;
}

t_computor_list *parcingEquation(char *equation) {
    equation = deleteWhiteSpaces(equation);

    if (!checkWrongChar(equation)) {
        free(equation);
        return NULL;
    }

    char    **bothSideEquation = ft_strsplit(equation, '=');
    free(equation);
    
    if (ft_arraystrlen(bothSideEquation) != 2) {
        printf("ERROR!!! The equation must have one and only one '=' and something on each side.");
        freeDoubleChar(bothSideEquation);
        return NULL;
    }

    if (!checkWrongCharNeighbor(bothSideEquation)) {
        freeDoubleChar(bothSideEquation);
        return NULL;
    }

    t_computor_list  *leftSideEquation = recoveryDataSideEquation(bothSideEquation[0]);
    t_computor_list  *rightSideEquation = recoveryDataSideEquation(bothSideEquation[1]);
    free(bothSideEquation);
    if (!leftSideEquation || !rightSideEquation){
        freeT_computor(leftSideEquation);
        freeT_computor(rightSideEquation);
        return NULL;
    }

    deleteDuplicatesPower(leftSideEquation);

    leftSideEquation = reductionEquation(leftSideEquation, rightSideEquation);

    printBadReductEquation(leftSideEquation);
    if (!(leftSideEquation = checkGoodPower(leftSideEquation)))
        return NULL;

    return sortEquation(leftSideEquation);
}