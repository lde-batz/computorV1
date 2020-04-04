

#include "computor.h"

double  ft_powf(double nb, int power) {
    double  nbr;
    int     i;

    if (power == 0)
        return 1;
    else if (power > 0) {
        nbr = nb;
        i = 1;
        while (i++ < power)
            nbr *= nb;
    }
    else {
        nbr = 1;
        i = 0;
        while (i-- > power)
            nbr /= nb;
    }
    return nbr;
}

double  ft_atof(const char *str) {
    int	    i;
	double	ret;
	int		sign;
    int     point;

	i = 0;
	ret = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
		sign = (str[i++] == 45) ? 0 : sign;
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
    if (str[i] != ',' && str[i] != '.') {
        (!sign) ? ret = -ret : ret;
        return ret;
    }
    point = i++;
    while (str[i] >= '0' && str[i] <= '9') {
        ret += (str[i] - 48) * ft_powf(10, point - i);
        i++;
    }
	(!sign) ? ret = -ret : ret;
    return ret;
}