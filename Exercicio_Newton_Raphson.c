//Exercicio 1 - Calculo do zero sistema não linear pelo Metodo de Newton-Raphson

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Calculando a F para o vetor x
double *F_i(double *x, FILE *saida, int i)
{
	double *F;
	F = malloc(sizeof(double)*2);
	
	F[0] = x[0]*x[0] + x[1]; //f1 = x1^2 + x2 
	F[1] = 2*(x[0]*x[0])-x[1]; //f2 = 2*(x1^2) - x2
	
	if(i != 0)
	{
		fprintf(saida, "F_1(x) = %lf, F_2(x) = %lf\n", F[0], F[1]);
	}
	return F;
}

//Calculando a matriz Jacobiana da F
double **J_i(double *x, FILE *saida)
{
	double **J;
	
	J = malloc(2 * sizeof(double*)); //Alocando dinamicamente as linhas da matriz Jacobiana

	for(int i = 0; i < 2; i++)
	{
		J[i] = malloc(2 * sizeof(double)); //Alocando dinamicamente as colunas da matriz Jacobiana
	}

	J[0][0] = 2*x[0];
	J[0][1] = 1; 
	J[1][0] = 4*x[0]; 
	J[1][1] = -1;
	
	fprintf(saida, "J_11 = %lf, J_12 = %lf, J_21 = %lf, J_22 = %lf\n",J[0][0], J[0][1], J[1][0], J[1][1]);

	return J;
}

//Calculando o maximo da F
double max(double *F)
{
	double max;
        int location = 0;
	
	for(int i = 0; i < 2; i++)
	{
		if(abs(F[i]) > abs(F[location])) location = i;
	}

	max = F[location];

	return max;
}

//Metodo para solução do sistema sem calcular a inversa da Jacobiana
double *Newton_Raphson_Direto(double *x, double erro, FILE *saida)
{
	double *F, **J, delta_x[2], x_temp_0, x_temp_1, *x_i, maximo;
	int i = 0;

	x_i = malloc(2*sizeof(double)); //Alocando dinamicamente o vetor x que será iterado
	
	x_i[0] = x[0];
	x_i[1] = x[1];

	F = F_i(x_i, saida, i);
	if(F[0] == 0 && F[1] == 0)
 	{
    		return x_i;
 	}
	
	do{
		i++;

		fprintf(saida, "Iteracao %d\n\n", i);
		F = F_i(x_i, saida, i); //Calculando a F para o vetor x
		J = J_i(x_i, saida); //Calculando a Jacobiana de F para o vetor x
		
		//Tratamento de erro para o delta_x2
		if(J[0][1] == 0) 
		{
			printf("Erro J_12 = 0\n");
			exit(1);
		}

		//Tratamento de erro para o delta_x1
		if((J[1][0]*J[0][1] - J[0][0]*J[1][1]) == 0)
		{
			printf("Erro -(det(J)) = 0\n");
			exit(1);
		}

		
		delta_x[0] = (J[1][1]*F[0] - F[1]*J[0][1]) / (J[1][0]*J[0][1] - J[0][0]*J[1][1]); //Calculando o delta_x1 direto
		delta_x[1] = (-F[0] - J[0][0]*delta_x[0])/J[0][1]; //Calculando o delta_x2 direto
		
		fprintf(saida, "delta_x1 = %lf, delta_x2 = %lf \n", delta_x[0], delta_x[1]);
		
		x_i[0] += delta_x[0]; //Novo x1 a partir do delta	
		x_i[1] += delta_x[1]; //Novo x2 a partir do delta

		fprintf(saida, "x1 = %lf, x2 = %lf \n\n", x_i[0], x_i[1]);
	}while(max(F) > erro); //Criterio de parada
	
	return x_i;
	
}

int main()
{
	double x[2], erro, *x_f;

	FILE *saida;

	saida = fopen("solucao_sistema_nao_linear_newton_raphson.txt", "w"); //Arquivo da solução do sistema
	
	erro = 1E-12; 
	
	x[0] = 1; //Entrada para o x1
	x[1] = 2; //Entrada para o x2

	fprintf(saida, "Objetivo do Programa: Calcular o zero de um sistema nao linear\n");
	fprintf(saida, "Nome: Hugo Xavier Rodrigues\n");	
	fprintf(saida, "Matricula: 190108622\n");
	fprintf(saida, "Data: 07-09-2021\n\n");
	
	

	printf("\nObjetivo do Programa: Calcular o zero de um sistema nao linear\n");
	printf("Nome: Hugo Xavier Rodrigues\n");	
	printf("Matricula: 190108622\n");
	printf("Data: 07-09-2021\n\n");
	
	x_f = Newton_Raphson_Direto(x, erro, saida); //vetor x final do metodo sem calcular a inversa da Jacobiana
	
	fprintf(saida, "Seja x1_inicial = 1; x2_inicial = 2; erro = 10^-12\n\n");

	fprintf(saida, "Solucao do sistema nao linear\n\nx1 = %lf, x2 = %lf \n\n",x_f[0],x_f[1]);
		
	printf("Seja x1_inicial = 1; x2_inicial = 2; erro = 10^-12\n\n");
	printf("Solucao do sistema nao linear\n\n");
	printf("x_1 = %lf, x_2 = %lf \n\n",x_f[0],x_f[1]);

	fclose(saida); //Fechando arquivo da solução do sistema
 
	return 0;
}
    
