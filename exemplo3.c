#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long fatorial(int m, int n)
{
	if(m == 1){
		return 1;
	}

	return m*fatorial(n-1);
}

int main()
{
	
	return 0;
}