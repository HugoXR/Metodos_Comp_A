//Exemplo de integrador simpletico 2 ordem

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define DIMMAX 1000

//Oscilador harmonico com k = 1 e m = 1
double F(double *x, double t, int i)
{
	double valor;
	if(i == 0) valor = -x[0];
	
	if(i == 1) valor = -x[1];

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
	double energ, t, delta_t, d2, t_final , x[DIMMAX], xl[DIMMAX];
	FILE *f_out;

	N = 4;
	t_final = 100.0;
	
	x[0] = 1.0000001;
	x[1] = 2.0;
	x[2] = 0.0;
	x[3] = 0.0;

	t = 0.0;
	delta_t = 0.01;
	d2 = delta_t / 2.0;
	
	f_out = fopen("solucao_integrador_simpletico.dat", "w");
	

	while(t < t_final)
	{
		
		for(int i = 0; i<N/2; i++)
		{
			xl[i] = x[i] + x[i+N/2]*(delta_t/2.0);
			xl[i+N/2] = x[i + N/2];
		}
	
		
		for(int i = 0; i<N/2; i++)
		{
			xl[i+N/2] += F(xl,t,i)*delta_t;
		}

		
		for(int i = 0; i<N/2; i++)
		{
			x[i] = xl[i]+xl[i+N/2]*delta_t/2.0;
			x[i+N/2]=xl[i+N/2];
		}
		energ = energia(x);

		t += delta_t;
	
		printf("%lf %lf %lf %lf %lf %lf\n", t, x[0], x[1], x[2], x[3], energ);

		fprintf(f_out,"%lf %lf %lf %lf %lf %lf\n", t, x[0], x[1], x[2], x[3], energ);
	}

	fclose(f_out);

	return 0;
}
