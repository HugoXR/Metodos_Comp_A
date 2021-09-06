//Exemplo de integrador de Runge-Kutta de 2 ordem

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define DIMMAX 1000

//Oscilador harmonico com k = 1 e m = 1
double F(double *x, double t, int i)
{
	double valor;
	if(i == 0) valor = x[2];
	
	if(i == 1) valor = x[3];

	if(i == 2) valor = -x[0];

	if(i == 3) valor = -x[1];


	return valor;
}

int main()
{
	long n;
	int N;
	double t, delta_t, d2, t_final , x[DIMMAX], k1[DIMMAX], k2[DIMMAX], xl[DIMMAX];
	FILE *f_out;

	N = 4;
	t_final = 10;
	
	x[0] = 1.0;
	x[1] = 1.0;
	x[2] = 0.0;
	x[3] = 0.0;

	t = 0.0;
	delta_t = 0.01;
	d2 = delta_t / 2.0;
	
	f_out = fopen("solucao.dat", "w");
	

	while(t < t_final)
	{
		for(int i = 0; i < N; i++)
		{
			k1[i] = delta_t*F(x,t,i);
			xl[i] = x[i]+k1[i]/2.0;
		}

		for(int i = 0; i < N; i++)
		{
			k2[i] = delta_t*F(xl, t+d2, i);
			x[i] += k2[i];
		}

		t += delta_t;

		fprintf(f_out, "%lf %lf %lf %lf %lf\n", t, x[0], x[1], x[2], x[3]);
	}

	fclose(f_out);

	return 0;
}
