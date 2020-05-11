




#ifndef COMPUTORV1_H
# define COMPUTORV1_H

# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct  s_splitEquation
{
    char                    *equation;
    struct s_splitEquation  *next;
}               t_splitEquation;

typedef struct  s_computor_list
{
    double                  number;
    int                     power;
    struct s_computor_list  *next;
}               t_computor_list;


void            solveEquation(char *equation);
t_computor_list *parcingEquation(char *equation);
t_computor_list *recoveryDataSideEquation(char *equation);


int             checkWrongChar(char *equation);
int             checkWrongCharNeighbor(char **bothSideEquation);

void            freeDoubleChar(char **ptr);
void            freeRecoveryData(t_splitEquation *splitEquation, t_computor_list *dataEquation,
                                t_computor_list *newData, char **splitPartEquation);
void            freeT_computor(t_computor_list *freeT);

void            resolveEquationDegree2(t_computor_list *equation);

void            floatToFraction(double x, int *a, int *b);


int             ft_arraystrlen(char **array);
int             ft_strfind(char *str, char chr);
int             ft_strfindlast(char *str, char chr);
int             *ft_atoi_strict(char *str, int *nb);
double          *ft_atof_strict(char *str, double *nb);
double  		ft_absf(double nb);


double  		ft_powf(double nb, int power);
double  		ft_atof(const char *str);



#endif
