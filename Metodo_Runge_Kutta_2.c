//Exemplo de integrador de Runge-Kutta de 4 ordem

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

	if(i == 2) valor = -x[0]+1.0+x[0]+x[1];

	if(i == 3) valor = -x[1]+1.0-x[0]-x[1];


	return valor;
}


double energia(double *x)
{
	double energ;

	energ = (x[2]*x[2]+x[3]*x[3])/2.0 + (x[0]*x[0] + x[1]*x[1])/2.0;

	return energ;
}

int main()
{
	long n;
	int N;
	double energ, t, delta_t, d2, t_final , x[DIMMAX], k1[DIMMAX], k2[DIMMAX], k3[DIMMAX], k4[DIMMAX], xl[DIMMAX];
	FILE *f_out;

	N = 4;
	t_final = 100.0;
	
	x[0] = 1.0;
	x[1] = 2.0;
	x[2] = 0.0;
	x[3] = 0.0;

	t = 0.0;
	delta_t = 0.01;
	d2 = delta_t / 2.0;
	
	f_out = fopen("solucao2.dat", "w");
	

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
			xl[i] = x[i]+k2[i]/2.0;
		}


		for(int i = 0; i < N; i++)
		{
			k3[i] = delta_t*F(xl, t+d2, i);
			xl[i] = x[i]+k3[i];
		}



		for(int i = 0; i < N; i++)
		{
			k4[i] = delta_t*F(xl, t+delta_t, i);
			x[i] += k1[i]/6.0+k2[i]/3.0+k3[i]/3.0+k4[i]/6.0;
		}

		t += delta_t;
		energ = energia(x);

		fprintf(f_out, "%lf %lf %lf %lf %lf %lf\n", t, x[0], x[1], x[2], x[3], energ);
	}

	fclose(f_out);

	return 0;
}
