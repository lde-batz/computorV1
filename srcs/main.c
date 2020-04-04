

#include "computor.h"

/*            BONUS              */
// gestion erreur
// osef ordre power
// notation normal
// prise en compte d'autres puissances
// fractionn irréductible
// afficher détails 

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage : ./computor \"equation\"\n");
		printf("original equation form is: Num * X^0 + Num * X^1 + Num * X^2 = Num * X^0 + Num * X^1 + Num * X^2\n");
		printf("or\nnatural equation form is : Num + Num * X + Num * X^2 = Num + Num * X + Num * X^2\n");
		printf("with Num belong to R, the order of powers isn't important and the presence of all the powers isn't compulsory\n");
		exit(EXIT_FAILURE);
	}
    solveEquation(argv[1]);

	return (0);
}