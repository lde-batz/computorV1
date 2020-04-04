


#include "computor.h"


void    freeDoubleChar(char **ptr) {
    int i = -1;

    if (ptr) {
        while(ptr[++i]) {
            free(ptr[i]);
        }
        free(ptr);
    }
}

void        freeRecoveryData(t_splitEquation *splitEquation, t_computor_list *dataEquation,
                            t_computor_list *newData, char **splitPartEquation) {
    t_splitEquation *freeSplit;
    t_computor_list *freeData;

    while (splitEquation) {
        freeSplit = splitEquation;
        splitEquation = splitEquation->next;
        free(freeSplit->equation);
        free(freeSplit);
    }
    while (dataEquation) {
        freeData = dataEquation;
        dataEquation = dataEquation->next;
        free(freeData);
    }
    free(newData);
    int i = -1;
    while (splitPartEquation[++i])
        free(splitPartEquation[i]);
    free(splitPartEquation);
}

void            freeT_computor(t_computor_list *freeT) {
    t_computor_list *freeT2;

    while (freeT) {
        freeT2 = freeT;
        freeT = freeT->next;
        free(freeT2);
    }
}
