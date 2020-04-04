


#include "computor.h"

int checkWrongChar(char *equation) {
    int i = -1;

    while (equation[++i]) {
        char chr = equation[i];

        if ((chr < '*' || chr > '.') && (chr < '0' || chr > '9')
                && chr != '=' && chr != 'X' && chr != '^') {
            ft_putstr("ERROR!!! This character '");
            ft_putchar(chr);
            ft_putendl("' isn't permit.");
            return 0;
        }
    }
    return 1;
}

int checkWrongCharStarEnd(char *equation) {
    char start = equation[0];
    if (start == '*' || start == ',' || start == '.' || start == '^')
    {
        printf("ERROR!!! This character '%c' can't be at the beginning of a side of the equation.", start);
        return 0;
    }
    
    char    end = equation[ft_strlen(equation) -1];
    if ((end >= '*' && end <= '.') || end == '^')
    {
        printf("ERROR!!! This character '%c' can't be at the end of a side of the equation.", end);
        return 0;
    }
    return 1;
}

int errorCheckWrongCharNeighbor(char chr, char preChr) {
    printf("ERROR!!! This character '%c' can't be before the character '%c'.", preChr, chr);
    return 0;
}

int checkWrongCharNeighbor(char **bothSideEquation) {
    int i = -1;

    while (bothSideEquation[++i]) {
        if (!checkWrongCharStarEnd(bothSideEquation[i]))
            return 0;

        int j = 0;
        while (bothSideEquation[i][++j]) {
            char    chr = bothSideEquation[i][j];
            char    preChr = bothSideEquation[i][j - 1];

            if (chr == '*')
                if((preChr >= '*' && preChr <= '.') || preChr == 'X' || preChr == '^')
                    return errorCheckWrongCharNeighbor(chr, preChr);
            if (chr == '+' || chr == '-')
                if(preChr >= '+' && preChr <= '.')
                    return errorCheckWrongCharNeighbor(chr, preChr);
            if (chr == ',' || chr == '.')
                if(preChr < '0' && preChr > '9')
                    return errorCheckWrongCharNeighbor(chr, preChr);
            if (preChr >= '0' && preChr <= '9')
                if(preChr == '*' || preChr == 'X')
                    return errorCheckWrongCharNeighbor(chr, preChr);
            if (chr == 'X')
                if(preChr == ',' || preChr == '.' || (preChr >= '0' && preChr <= '9')
                                || preChr == 'X' || preChr == '^')
                    return errorCheckWrongCharNeighbor(chr, preChr);
            if (chr == '^')
                if(preChr != 'X')
                    return errorCheckWrongCharNeighbor(chr, preChr);
        }
    }
    return 1;
}