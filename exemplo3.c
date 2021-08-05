#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long fatorial(int m)
{
	if(m >= 1){
		return m*fatorial(m-1);
	} else {
		return 1;
	}

}

int main()
{
	long f;

	long entrada;
	printf("Digite o valor do input\n");
	scanf("%lu", &entrada);

	f = fatorial(entrada);

	printf("%ld\n", f);
	return 0;
}