//Calculo de sistema não linear pelo Metodo de Newton-Raphson

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double *F_i(double *x, FILE *saida)
{
	double *K;
	K = malloc(sizeof(double)*2);
	
	K[0] = (x[0]*x[0]) + x[1];
	K[1] = 2*(x[0]*x[0]*x[0]) - x[1] - 3;
	
	fprintf(saida, "F_1(x) = %lf, F_2(x) = %lf\n\n", K[0], K[1]);
	return K;
}

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
	J[1][0] = 6*(x[0]*x[0]);
	J[1][1] = -1;
	
	fprintf(saida, "J_11 = %lf, J_12 = %lf, J_21 = %lf, J_22 = %lf\n\n",J[0][0], J[0][1], J[1][0], J[1][1]);

	return J;
}

double det_J(double **J)
{
	double det;

	det = J[0][0]*J[1][1] - J[0][1]*J[1][0];
	
	return det;
}

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
		exit(1);
	}


	return J_inv;
}

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

double *Newton_Raphson(double *x, double erro, FILE *saida)
{
	double *F, **J, **J_inv, *delta_x, x_temp_0, x_temp_1, *x_i, maximo;
	int i = 0;

	x_i = malloc(2*sizeof(double));

	x_i[0] = x[0];
	x_i[1] = x[1];
	
	
	if(((x[0]*x[0] + x[1]) == 0) && (2*x[0]*x[0] - x[1] == 0))
	{
		return x;
	}	

	do{
		i++;
		fprintf(saida, "Iteração %d\n\n", i);
		F = F_i(x_i, saida);
		J = J_i(x_i, saida);
	
		J_inv = inversa(J);
	
		delta_x = prod_matriz_2(F, J_inv);

		fprintf(saida, "delta_x1 = %lf, delta_x2 = %lf\n\n",delta_x[0], delta_x[1]);
		
		x_i[0] += delta_x[0]; 
		x_i[1] += delta_x[1];


		fprintf(saida, "x_1 = %lf, x_2 = %lf\n\n",x_i[0], x_i[1]);
	}while(max(F) > erro);
	
	return x_i;
	
}


double *Newton_Raphson_Direto(double *x, double erro, FILE *saida)
{
	double *F, **J, delta_x[2], x_temp_0, x_temp_1, *x_i, maximo;
	int i = 0;

	x_i = malloc(2*sizeof(double));
	
	
	x_i[0] = x[0];
	x_i[1] = x[1];

	if(((x[0]*x[0] + x[1]) == 0) && (2*x[0]*x[0] - x[1] == 0))
	{
		return x;
	}	

	do{
		i++;

		fprintf(saida, "Iteração %d\n\n", i);
		F = F_i(x_i, saida);
		J = J_i(x_i, saida);
		
		if(J[0][1] == 0)
		{
			printf("zero\n");
			exit(1);
		}

		if((J[1][0]*J[0][1] - J[0][0]*J[1][1]) == 0)
		{
			printf("zero\n");
			exit(1);
		}

		
		delta_x[0] = (J[1][1]*F[0] - F[1]*J[0][1]) / (J[1][0]*J[0][1] - J[0][0]*J[1][1]);
		delta_x[1] = (-F[0] - J[0][0]*delta_x[0])/J[0][1];
		
		fprintf(saida, "delta_x1 = %lf, delta_x2 = %lf \n\n", delta_x[0], delta_x[1]);
		
		x_i[0] += delta_x[0]; 
		x_i[1] += delta_x[1];

		fprintf(saida, "x1 = %lf, x2 = %lf \n\n", x_i[0], x_i[1]);
	}while(max(F) > erro);
	
	return x_i;
	
}

int main()
{
	double x[2], x_temp[2], erro, *x_f, *x_f2;

	FILE *saida_direto, *saida;


	saida_direto = fopen("solucao_sistema_direto_newton_raphson.txt", "w");
	saida = fopen("solucao_sistema_newton_raphson.txt", "w");
	
	erro = 1E-8;
	x[0] = 2;
	x[1] = -2;

	x_f = Newton_Raphson_Direto(x, erro, saida_direto);
	x_f2 = Newton_Raphson(x, erro, saida);
	
	fprintf(saida_direto, "Solução do sistema não linear\n\nx1 = %lf, x2 = %lf \n\n",x_f[0],x_f[1]);
	fprintf(saida, "Solução do sistema não linear\n\nx1 = %lf, x2 = %lf \n\n",x_f2[0],x_f2[1]);
	
	
	printf("x_1 = %lf, x_2 = %lf \n\n",x_f[0],x_f[1]);
	printf("xf_1 = %lf, xf_2 = %lf \n\n",x_f2[0],x_f2[1]);
	fclose(saida_direto);
	fclose(saida);

	return 0;
}
