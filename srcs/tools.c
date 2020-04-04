



#include "computor.h"

int         ft_arraystrlen(char **array) {
    int i = -1;

    if (!array)
        return -1;
    while(array[++i]) {}

    return i;
}

int         ft_strfind(char *str, char chr) {
    int i = -1;

    while (str[++i]) {
        if (str[i] == chr)
            return i;
    }
    return -1;
}

int         ft_strfindlast(char *str, char chr) {
    int i = ft_strlen(str);

    while (--i >= 0) {
        if (str[i] == chr)
            return i;
    }
    return -1;
}

int    *ft_atoi_strict(char *str, int *nb) {
    int	i;
	int	ret;
	int	neg;
    int error;

	i = 0;
	ret = 0;
	neg = 0;
    error = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
		neg = (str[i++] == '-') ? 1 : 0;
    if (str[i] >= '0' && str[i] <= '9') {
        error = 0;
    }
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
    if (str[i] || error) {
        return NULL;
    }
	ret = (neg) ? -ret : ret;
    *nb = ret;
	return nb;
}

double  *ft_atof_strict(char *str, double *nb) {
    int	    i;
	double	ret;
	int		sign;
    int     point;
    int     error;

	i = 0;
	ret = 0;
	sign = 1;
    error = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
		sign = (str[i++] == 45) ? 0 : sign;
    if (str[i] >= '0' && str[i] <= '9') {
        error = 0;
    }
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
    if (!str[i]) {
        ret = (!sign) ? -ret : ret;
        *nb = ret;
        return nb;
    }
    if (str[i] != ',' && str[i] != '.')
	    return NULL;
    point = i++;
    while (str[i] >= '0' && str[i] <= '9') {
        ret += (str[i] - 48) * ft_powf(10, point - i);
        i++;
    }
    if (error || point + 1 == i)
        return NULL;
    ret = (!sign) ? -ret : ret;
    *nb = ret;
    return nb;
}

double  ft_absf(double nb) {
    if (nb < 0) {
        return -nb;
    }
    return nb;
}