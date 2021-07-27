#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(){

	//Variáveis
	double a, b, c, d; //Elementos da Matriz
	double M[2][2]; //Matriz
	double e, f; //Vetor solução
	double lambda1, lambda2; //Autovalores 
	double v1[2], v2[2]; //Autovetores
	double discriminante_eq_segundo_grau;
	double sum1;
	double pw;
	int i, j;

	a = 1.0;
	b = -2.0;
	c = -2.0;
	d = 7.0;

	M[0][0] = a;
	M[0][1] = b;
	M[1][0] = c;
	M[1][1] = d;

	//pw = pow(M[0][0] + M[1][1], 2)
	sum1 = M[0][0] + M[1][1];
	pw = sum1 * sum1;

	discriminante_eq_segundo_grau = pw - 4*(M[0][0]*M[1][1] - M[0][1]*M[1][0]);

	if(discriminante_eq_segundo_grau < 0)
	{
		printf("Discriminante negativo!\n");
		return -1;
	}

	lambda1 = (sum1 + sqrt(discriminante_eq_segundo_grau)) / 2.0;
	lambda2 = (sum1 - sqrt(discriminante_eq_segundo_grau)) / 2.0;
 	
 	printf("Autovalores lambda1 = %lf, lambda2 = %lf \n", lambda1, lambda2);
 	return 0;
}