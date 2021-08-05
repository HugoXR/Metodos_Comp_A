#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Calculo Discriminante 

double discriminante(double M[2][2]){
	double discriminante_eq_segundo_grau, sum1, pw;

	sum1 = M[0][0] + M[1][1];
	pw = sum1 * sum1;

	printf("a = %lf, b = %lf, c = %lf, d = %lf\n", M[0][0], M[0][1], M[1][0], M[1][1]);

	discriminante_eq_segundo_grau = pw - 4*(M[0][0]*(M[1][1]) - M[0][1]*(M[1][0]));

	return discriminante_eq_segundo_grau;
}

//Sol Sistema Linear 2x2
int resolve(double a, double b, double c, double d, double e, double f, double* x, double* y)
{
	double M[2][2], e_linha, f_linha, lambda1, lambda2,  v1[2], v2[2], discriminante_eq_segundo_grau, sum1, pw, lambda1_menos_a, lambda2_menos_a, prod_escalar; 

	M[0][0] = a;
	M[0][1] = b;
	M[1][0] = c;
	M[1][1] = d;

	discriminante_eq_segundo_grau = discriminante(M);

	if(discriminante_eq_segundo_grau < 0)
	{
		printf("Discriminante negativo!\n");
		return -1;
	};

	lambda1 = (sum1 + sqrt(discriminante_eq_segundo_grau)) / 2.0;
	lambda2 = (sum1 - sqrt(discriminante_eq_segundo_grau)) / 2.0;
 	 	
 	lambda1_menos_a = lambda1 - M[0][0];

 	v1[0] = sqrt(1.0/(1.0 + (lambda1_menos_a*lambda1_menos_a/(M[0][1]*M[0][1]))));
 	v1[1] = (((lambda1_menos_a)*v1[0])/M[0][1]);

 	lambda2_menos_a = lambda2 - M[0][0];

 	v2[0] = sqrt(1.0/(1.0 + ((lambda2_menos_a*lambda2_menos_a)/(M[0][1]*M[0][1]))));
 	v2[1] = (((lambda2_menos_a)*v2[0])/M[0][1]);

 	printf("v1[0] = %lf, v1[1] = %lf\n",v1[0], v1[1]);
 	printf("v2[0] = %lf, v2[1] = %lf\n",v2[0], v2[1]);

 	e_linha = e*v1[0] + f*v1[1];
 	f_linha = e*v2[0] + f*v2[1];

 	*x = (e_linha / lambda1)* v1[0] + (f_linha / lambda2) * v2[0];
 	*y = (e_linha / lambda1)* v2[1] + (f_linha / lambda2) * v2[1];

 	return 0;
}

int main(){

	//Variáveis
	double a, b, c, d; //Elementos da Matriz
	//double M[2][2]; //Matriz
	double e, f; //Vetor solução
	double e_linha, f_linha;
	double lambda1, lambda2; //Autovalores 
	double v1[2], v2[2]; //Autovetores
	double discriminante_eq_segundo_grau;
	double sum1; //Soma da diagonal principal
	double pw; //Quadrado da soma da diagonal principal
	double lambda1_menos_a, lambda2_menos_a; //Autovalor menos o primeiro elemento da matriz
	double prod_escalar; //Produto escalar entre os autovetores
	double x, y; //Solução
	int i;
	FILE *entrada, *saida; //Arquivos de entrada e saida de dados

	entrada=fopen("exemplo1.txt", "r");

	fscanf(entrada, "%lf", &a);
	fscanf(entrada, "%lf", &b);
	fscanf(entrada, "%lf", &c);
	fscanf(entrada, "%lf", &d);
	fscanf(entrada, "%lf", &e);
	fscanf(entrada, "%lf", &f);
	fclose(entrada);

	printf("x = %lf   y = %lf\n", x, y);

	i = resolve(a, b, c, d, e, f, &x, &y);
 	
	if(i == -1){
		printf("Discriminante negativo \n");
		return -1;
	}

 	printf("Solução do Sistema\n");
 	printf("x = %lf   y = %lf\n", x, y);


 	return 0;
}