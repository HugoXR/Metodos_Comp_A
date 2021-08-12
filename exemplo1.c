#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Calculo Discriminante 

double discriminante(double ***M, double pw){
	double discriminante_eq_segundo_grau;

	printf("a = %lf, b = %lf, c = %lf, d = %lf\n", *M[0][0], *M[0][1], *M[1][0], *M[1][1]);

	discriminante_eq_segundo_grau = pw - 4*(*M[0][0]*(*M[1][1]) - *M[0][1]*(*M[1][0]));

	return discriminante_eq_segundo_grau;
}

double **aloca_matriz(int linhas, int colunas)
{
	double **matriz;

	matriz = (double **)malloc(sizeof(int *)*linhas);
	if(matriz == NULL)
	{
		printf("Memória insuficiente\n");
		exit(1);
	}

	for(int i = 0; i < linhas; i++)
	{
		matriz[i] = (double *)malloc(sizeof(int *)*colunas);
		
		if(matriz[i] == NULL)
		{
			printf("Memória insuficiente\n");
			exit(1);
		}
	}

	return matriz;

}

void popula_matriz(double ***matriz, char nome_arquivo[13], int *linhas, int *colunas, double *e, double *f)
{
	FILE *entrada;
	char caracter;
	entrada = fopen("exemplo1.txt", "r");
	int tamanho_linhas_arquivo = 0;
	int tamanho_matriz = 0;

	while(caracter != EOF)
	{
		caracter = fgetc(entrada);
		if(caracter == '\n')
		{
			tamanho_linhas_arquivo++;
		}

	}

	fseek(entrada, 0, SEEK_SET);
	int count = 1;
	while(tamanho_matriz == 0)
	{
		count++;
		if(tamanho_linhas_arquivo % count == 0)
		{
			tamanho_matriz = tamanho_linhas_arquivo - count;
			*linhas = tamanho_matriz / count;
			*colunas = tamanho_matriz / count;
			
		}
	}
	double value = 0.0;

	for(int i = 0; i < *linhas; i++)
	{
		for(int j = 0; j < *colunas; j++)
		{
			fscanf(entrada, "%lf", &value);
			*matriz[i][j] = value;
		
		}
	}

	printf("\n%lf\n",matriz[0][0]);	
	
	fscanf(entrada, "%lf", &*e);
	fscanf(entrada, "%lf", &*f);
	fclose(entrada);
	
}

//Sol Sistema Linear 2x2
int resolve(double ***M, double *e, double *f, double* x, double* y, int *linhas, int *colunas)
{
	double e_linha, f_linha, lambda1, lambda2,  v1[2], v2[2], discriminante_eq_segundo_grau, sum1, pw, lambda1_menos_a, lambda2_menos_a, prod_escalar; 
	

	*M = aloca_matriz(2, 2);
	
	popula_matriz(&*M, "exemplo1.txt", &*linhas, &*colunas, &*e, &*f);
	
	printf("\naaaaaa\n");	
	sum1 = *M[0][0] + *M[1][1];
	pw = sum1 * sum1;

	discriminante_eq_segundo_grau = discriminante(&*M, pw);

	if(discriminante_eq_segundo_grau < 0)
	{
		printf("Discriminante negativo!\n");
		return -1;
	};

	lambda1 = (sum1 + sqrt(discriminante_eq_segundo_grau)) / 2.0;
	lambda2 = (sum1 - sqrt(discriminante_eq_segundo_grau)) / 2.0;

	printf("lambda1 = %lf, lambda2 = %lf\n",lambda1, lambda2);
 	 	
 	lambda1_menos_a = lambda1 - *M[0][0];

 	v1[0] = sqrt(1.0/(1.0 + (lambda1_menos_a*lambda1_menos_a/(*M[0][1]*(*M[0][1])))));
 	v1[1] = (((lambda1_menos_a)*v1[0])/ *M[0][1]);

 	lambda2_menos_a = lambda2 - *M[0][0];

 	v2[0] = sqrt(1.0/(1.0 + ((lambda2_menos_a*lambda2_menos_a)/(*M[0][1]*(*M[0][1])))));
 	v2[1] = (((lambda2_menos_a)*v2[0])/ *M[0][1]);

 	printf("v1[0] = %lf, v1[1] = %lf\n",v1[0], v1[1]);
 	printf("v2[0] = %lf, v2[1] = %lf\n",v2[0], v2[1]);

 	e_linha = *e*v1[0] + *f*v1[1];
 	f_linha = *e*v2[0] + *f*v2[1];

 	*x = (e_linha / lambda1)* v1[0] + (f_linha / lambda2) * v2[0];
 	*y = (e_linha / lambda1)* v2[1] + (f_linha / lambda2) * v2[1];

 	return 0;
}

void desaloca_matriz(double **matriz, int linhas)
{
	for(int i = 0; i < linhas; i++)
	{

		printf("teste\n");
		free(matriz[i]);
	}
	free(matriz);

}


int main(){

	//Variáveis
	double a, b, c, d; //Elementos da Matriz
	double **M; //Matriz
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
	FILE *saida; //Arquivos de entrada e saida de dados
	int linhas, colunas;


	printf("x = %lf   y = %lf\n", x, y);

	i = resolve(&M, &e, &f, &x, &y, &linhas, &colunas);
 	printf("\n%lf\n", M[0][0]);
	if(i == -1){
		printf("Discriminante negativo \n");
		return -1;
	}

 	printf("Solução do Sistema\n");
 	printf("x = %lf   y = %lf\n", x, y);
	
	desaloca_matriz(M, linhas);

 	return 0;
}
