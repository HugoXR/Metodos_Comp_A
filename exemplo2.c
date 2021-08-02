#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	//Exemplo Repetidores

 	double xi, xf, dx, x, func;
 	int num_pontos = 100;
 	FILE *dados;

 	xi = 0.1;
 	xf = 10.0;

 	dx = (xf - xi)/(double)(num_pontos - 1);

 	x = xi;

 	dados = fopen("grafico.dat", "w");

 	for (int i = 1; i <= num_pontos; ++i){
 		func=sin(log(x));
 		fprintf(dados, "%lf  %lf\n", x, func);
 		x += dx;
 	};

 	fclose(dados);

	return 0;
}