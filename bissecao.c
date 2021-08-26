//Calculo do zero de uma função real pelo método da bissecção
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double function(double x)
{
	double res;
	res = cos(x);
	return res;
}

double bissect_relative_error(double a, double b, double erro)
{
	double x_a, x_b, x_c, f_a, f_b, f_c, final;
	
	x_a = a;
	x_b = b;

	f_a = function(x_a); //Valor de a na função
	f_b = function(x_b); //Valor de b na função
	
	//Verificando se há zero nos pontos a e b, e cancelando iteração caso haja mais de um, ou nenhum, zero no intervalo
	if(f_a == 0)
	{
		return x_a;
	}
	else if(f_b == 0)
	{
		return x_b;
	}
	else if ((f_b > 0 && f_a > 0) || (f_b < 0 && f_a < 0))
	{
		printf("Não há zero, ou há mais de um zero no intervalo [%lf,%lf]\n",x_a,x_b);
		exit(1);
	}
	
	//Iterações
	while((fabs((x_b-x_a)/x_b)) > erro)
	{
		x_c = (x_a + x_b)/2;
		f_c = function(x_c);

		printf("x_1 = %lf, x_2 = %lf, f_1 = %lf, f_2 = %lf\n\n", x_a, x_b, f_a, f_b);
		if(f_a*f_c < 0 && f_b*f_c > 0)
		{
			x_b = x_c;
		}
		else if(f_a*f_c > 0 && f_b*f_c < 0)
		{
			x_a = x_c;
		} else if(f_c == 0)
		{
			return x_c;
		}

		f_a = function(x_a);
		f_b = function(x_b);
	}
	
	final = (x_a + x_b)/2; //Valor do zero, para o erro relativo dado
	
	return final;
}

int main()
{
	double a; //ponto inicial do intervalo
	double b; //ponto final do intervalo
	double zero; //zero da função
	double erro; //Erro
	
	a = 0;
	b = 2;
	erro = 1.0e-8;
	

	zero = bissect_relative_error(a, b, erro);
	printf("Zero da função = %.8lf\n", zero);
	
	return 1;
}

