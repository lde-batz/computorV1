


#include "computor.h"


t_splitEquation *splitSideEquation(char *equation) {
    t_splitEquation *splitEquation = NULL;
    int             i = 0;
    int             start = 0;
    int             end = 1;

    while(equation[++i]) {
        if (equation[i] == '+' || equation[i] == '-') {
            if (equation[i - 1] != '^') {
                t_splitEquation *newSplit = (t_splitEquation*)malloc(sizeof(t_splitEquation));
                
                newSplit->equation = ft_strsubuntil(equation, start, end, 0);
                newSplit->next = splitEquation;
                splitEquation = newSplit;
                start = i;
            }
        }
        end++;
    }
    t_splitEquation *newSplit = (t_splitEquation*)malloc(sizeof(t_splitEquation));                
    newSplit->equation = ft_strsubuntil(equation, start, end, 0);
    newSplit->next = splitEquation;
    splitEquation = newSplit;

    free(equation);
    return splitEquation;
}


int        parceOnlyOneX(t_computor_list *newData, char *str) {
    int sign = 1;
    int start = 0;
    if (str[0] == '+' || str[0] == '-') {
        if (str[0] == '-')
            sign = -1;
        start++;
    }
    if (str[start] == 'X' && !str[start + 1]) {
        newData->number = 1;
        newData->power = 1;
    } else if (str[start] != 'X' || str[start + 1] != '^') {
        printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow' or 'X^Pow' with Num = 1.\n");
        return 0;
    } else {
        start += 2;
        char    *strNb = ft_strsubuntil(str, start, ft_strlen(str), 0);
        newData->number = sign;
        if (ft_atoi_strict(strNb, &newData->power) == NULL){
            printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow' or 'X^Pow' with Num = 1 and Pow belong to Z.\n");
            free(strNb);
            return 0;
        }
        free(strNb);
    }
    return 1;
}

int         parceOnlyOnePartEquation(t_computor_list *newData, char *str) {
    if (ft_strfind(str, 'X') == -1) {
        if (ft_atof_strict(str, &newData->number) == NULL) {
            printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow' or 'Num' with Pow = 0 and Num belong to R.\n");
            return 0;
        }
        newData->power = 0;
    } else if (ft_strfind(str, 'X') == ft_strfindlast(str, 'X')) {
        if (!parceOnlyOneX(newData, str))
            return 0;
    } else {
        printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow' or 'X^Pow' with Num = 1 and one and only one 'X'.\n");
        return 0;
    }
    return 1;
}

int         parceNormalPartEquation(t_computor_list *newData, char **str) {
    if (ft_atof_strict(str[0], &newData->number) == NULL) {
        printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow' with Num belong to R.\n");
        return 0;
    }
    if (ft_strfind(str[1], 'X') == -1) {
        printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow' with one and only one 'X'.\n");
        return 0;
    } else if (ft_strfind(str[1], 'X') == ft_strfindlast(str[1], 'X')) {
        if (str[1][0] == 'X' && !str[1][1]) {
            newData->power = 1;
        } else if (str[1][0] != 'X' || str[1][1] != '^') {
            printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow'.\n");
            return 0;
        } else {
            char    *strNb = ft_strsubuntil(str[1], 2, ft_strlen(str[1]), 0);
            if (ft_atoi_strict(strNb, &newData->power) == 0){
                printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow' with Pow belong to Z.\n");
                free(strNb);
                return 0;
            }
            free(strNb);
        }
    } else {
        printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow' with one and only one 'X'.\n");
        return 0;
    }
    return 1;
}


t_computor_list  *recoveryDataSideEquation(char *equation) {
    t_splitEquation *splitEquation = splitSideEquation(equation);
    t_computor_list      *dataEquation = NULL;
    
    while (splitEquation) {
        t_computor_list *newData = (t_computor_list*)malloc(sizeof(t_computor_list));

        char    **splitPartEquation = ft_strsplit(splitEquation->equation, '*');
        if (ft_arraystrlen(splitPartEquation) == 1) {
            if (!parceOnlyOnePartEquation(newData, splitPartEquation[0])){
                freeRecoveryData(splitEquation, dataEquation, newData, splitPartEquation);
                return NULL;
            }
        } else if (ft_arraystrlen(splitPartEquation) == 2) {
            if (!parceNormalPartEquation(newData, splitPartEquation)) {
                freeRecoveryData(splitEquation, dataEquation, newData, splitPartEquation);
                return NULL;
            }
        } else {
            printf("ERROR!!! The syntaxe of the equation is wrong. It's 'Num * X^Pow' with one and only one '*'.\n");
            freeRecoveryData(splitEquation, dataEquation, newData, splitPartEquation);
            return NULL;
        }

        newData->next = dataEquation;
        dataEquation = newData;
        
        t_splitEquation *freeSplitEquation = splitEquation;
        splitEquation = splitEquation->next;
        free(freeSplitEquation->equation);
        free(freeSplitEquation);

        int i = -1;
        while (splitPartEquation[++i])
            free(splitPartEquation[i]);
        free(splitPartEquation);
    }
    return dataEquation;
}