//Exercicio 1 - Calculo de sistema não linear pelo Metodo de Newton-Raphson

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Calculando a F para o vetor x
double *F_i(double *x, FILE *saida)
{
	double *F;
	F = malloc(sizeof(double)*2);
	
	F[0] = x[0]*x[0] + x[1]; //f1 = x1^2 + x2 
	F[1] = 2*(x[0]*x[0])-x[1]; //f2 = 2*(x1^2) - x2
	
	fprintf(saida, "F_1(x) = %lf, F_2(x) = %lf\n\n", F[0], F[1]);
	return F;
}

//Calculando a Jacobiana da F
double **J_i(double *x, FILE *saida)
{
	double **J;
	
	J = malloc(2 * sizeof(double*));

	for(int i = 0; i < 2; i++)
	{
		J[i] = malloc(2 * sizeof(double));
	}

	J[0][0] = 2*x[0];
	J[0][1] = 1; 
	J[1][0] = 4*x[0]; 
	J[1][1] = -1;
	
	fprintf(saida, "J_11 = %lf, J_12 = %lf, J_21 = %lf, J_22 = %lf\n\n",J[0][0], J[0][1], J[1][0], J[1][1]);

	return J;
}

//Calculando a determinante de uma matriz 2x2
double det_J(double **J)
{
	double det;

	det = J[0][0]*J[1][1] - J[0][1]*J[1][0];
	
	return det;
}

//Calculando a inversa de uma matriz 2x2
double **inversa(double **J)
{

	double **J_inv, det;
	

	J_inv = malloc(2 * sizeof(double*));

	for(int i = 0; i < 2; i++)
	{
		J_inv[i] = malloc(2 * sizeof(double));
	}

	det = det_J(J);

	if(det != 0)
	{
		J_inv[0][0] = J[1][1]/det;
		J_inv[0][1] = -J[0][1]/det;
		J_inv[1][0] = -J[1][0]/det;
		J_inv[1][1] = J[0][0]/det;
	
	} else{
		printf("Solução não encontrada\n");
		exit(1);
	}


	return J_inv;
}

//Realizando o produto de duas matrizes 2x2(Neste caso J_inv x -F)
double *prod_matriz_2(double *F, double **J_inv)
{
	double *prod;

	prod = malloc(2*sizeof(double));

	prod[0] = 0;
	prod[1] = 0;
	
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			prod[i] += J_inv[i][j]*(-F[j]);
		}	
	}

	return prod;
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

//Metodo para solução do sistema calculando a inversa da Jacobiana
double *Newton_Raphson(double *x, double erro, FILE *saida)
{
	double *F, **J, **J_inv, *delta_x, x_temp_0, x_temp_1, *x_i, maximo;
	int i = 0;

	x_i = malloc(2*sizeof(double)); //Alocando dinamicamente o x que será iterado

	x_i[0] = x[0];
	x_i[1] = x[1];
	
	do{
		i++;
		fprintf(saida, "Iteração %d\n\n", i);
		F = F_i(x_i, saida); //Calculando a função no x
		J = J_i(x_i, saida); //Calculando a Jacobiana no x
	
		J_inv = inversa(J); //Calculando a inversa da Jacobiana
	
		delta_x = prod_matriz_2(F, J_inv); //Calculando o delta pelo produto de matrizes

		fprintf(saida, "delta_x1 = %lf, delta_x2 = %lf\n\n",delta_x[0], delta_x[1]);
		
		x_i[0] += delta_x[0]; //Novo x1 a partir do delta
		x_i[1] += delta_x[1]; //Novo x2 a partir do delta


		fprintf(saida, "x_1 = %lf, x_2 = %lf\n\n",x_i[0], x_i[1]);

	}while(max(F) > erro); //Criterio de parada
	
	return x_i;
	
}

//Metodo para solução do sistema sem calcular a inversa da Jacobiana
double *Newton_Raphson_Direto(double *x, double erro, FILE *saida)
{
	double *F, **J, delta_x[2], x_temp_0, x_temp_1, *x_i, maximo;
	int i = 0;

	x_i = malloc(2*sizeof(double)); //Alocando dinamicamente o vetor x que será iterado
	
	
	x_i[0] = x[0];
	x_i[1] = x[1];
	
	do{
		i++;

		fprintf(saida, "Iteração %d\n\n", i);
		F = F_i(x_i, saida); //Calculando a F para o vetor x
		J = J_i(x_i, saida); //Calculando a Jacobiana de F para o vetor x
		
		//Tratamento de erro para o delta_x2
		if(J[0][1] == 0) 
		{
			printf("zero\n");
			exit(1);
		}

		//Tratamento de erro para o delta_x1
		if((J[1][0]*J[0][1] - J[0][0]*J[1][1]) == 0)
		{
			printf("zero\n");
			exit(1);
		}

		
		delta_x[0] = (J[1][1]*F[0] - F[1]*J[0][1]) / (J[1][0]*J[0][1] - J[0][0]*J[1][1]); //Calculando o delta_x1 direto
		delta_x[1] = (-F[0] - J[0][0]*delta_x[0])/J[0][1]; //Calculando o delta_x2 direto
		
		fprintf(saida, "delta_x1 = %lf, delta_x2 = %lf \n\n", delta_x[0], delta_x[1]);
		
		x_i[0] += delta_x[0]; //Novo x1 a partir do delta	
		x_i[1] += delta_x[1]; //Novo x2 a partir do delta

		fprintf(saida, "x1 = %lf, x2 = %lf \n\n", x_i[0], x_i[1]);
	}while(max(F) > erro); //Criterio de parada
	
	return x_i;
	
}

int main()
{
	double x[2], x_temp[2], erro, *x_f, *x_f2;

	FILE *saida_direto, *saida;


	saida_direto = fopen("solucao_sistema_nao_linear_direto.txt", "w"); //Arquivo da solução do sistema sem calcular a inversa da Jacobiana
	saida = fopen("solucao_sistema_nao_linear.txt", "w"); //Arquivo da solução do sistema calculando a inversa da Jacobiana
	
	erro = 1E-8; 
	
	x[0] = 1; //Entrada para o x1
	x[1] = 2; //Entrada para o x2

	x_f = Newton_Raphson_Direto(x, erro, saida_direto); //vetor x final do metodo sem calcular a inversa da Jacobiana
	x_f2 = Newton_Raphson(x, erro, saida); //vetor x final do metodo calculando a inversa da Jacobiana
	
	fprintf(saida_direto, "Solução do sistema não linear\n\nx1 = %lf, x2 = %lf \n\n",x_f[0],x_f[1]);
	fprintf(saida, "Solução do sistema não linear\n\nx1 = %lf, x2 = %lf \n\n",x_f2[0],x_f2[1]);
	
	
	printf("x_1 = %lf, x_2 = %lf \n\n",x_f[0],x_f[1]);
	printf("xf_1 = %lf, xf_2 = %lf \n\n",x_f2[0],x_f2[1]);

	fclose(saida_direto); //Fechando arquivo da solução do sistema sem calcular a inversa da Jacobiana
	fclose(saida);//Fechando arquivo da solução do sistema calculando a inversa da Jacobiana
 
	return 0;
}
