#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void aloca_matriz(double ***matriz,int linhas, int colunas)
{
	*matriz = (double **)malloc(sizeof(int *)*linhas);
	printf("Teste 1.1\n");	
	if(*matriz == NULL)
	{
		printf("Memória insuficiente\n");
		exit(1);
	}

	for(int i = 0; i < linhas; i++)
	{
		*matriz[i] = (double *)malloc(sizeof(int *)*colunas);
		if(*matriz[i] == NULL)
		{
			printf("Memória insuficiente\n");
			exit(1);
		}
	}

	
}

double *aloca_vetor(int linhas)
{
	double *vetor;
	vetor = (double *)malloc(sizeof(int*)*linhas);
	if(vetor == NULL)
	{
		printf("Memória insuficiente \n");
		exit(1);
	}

	return vetor;
}

void popula_matriz(double ***matriz, FILE *entrada, int linhas, int colunas)
{
	if(linhas != colunas)
	{
		printf("Error\n");
		exit(1);
	}
		
	double value = 0.0;

	for(int i = 0; i < linhas; i++)
	{
		for(int j = 0; j < colunas; j++)
		{
			fscanf(entrada, "%lf", &value);
			*matriz[i][j] = value;
		}
	}

}

void popula_vetor(double **vetor, FILE *entrada, int linhas)
{
	double value = 0.0;
	for(int i = 0; i < linhas; i++)
	{
		fscanf(entrada, "%lf", &value);
		*vetor[i] = value;
	}

}

void cria_matriz(double ***matriz, int *linhas, int *colunas, double **vetor)
{
	FILE *entrada;
	entrada = fopen("exemplo4.txt", "r");
	
	int tamanho_linhas_arquivo = 0;
	int tamanho_matriz = 0;
	char caracter;
	int count = 1;

	while(caracter != EOF)
	{
		caracter = fgetc(entrada);
		if(caracter == '\n')
		{
			tamanho_linhas_arquivo++;
		}

	}

	fseek(entrada, 0, SEEK_SET);
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

	printf("linhas = %d colunas = %d\n", *linhas, *colunas);
	aloca_matriz(&*matriz,*linhas, *colunas);
	printf("Teste2\n");
	*matriz[0][0] = 3.4;
	printf("%lf\n", *matriz[0][0]);
	*vetor = aloca_vetor(*linhas);
	printf("Teste3\n");
	popula_matriz(&*matriz, entrada, *linhas, *colunas);
	printf("Teste4\n");
	popula_vetor(&*vetor, entrada, *linhas);
}



int main(){
	
	double ***matriz;
	int linhas;
	int colunas;
	double **vetor;
	
	cria_matriz(&*matriz, &linhas, &colunas, &*vetor);

	printf("%lf\n", matriz[0][0]);

	return 0;

}
