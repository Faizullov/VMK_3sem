#include <stdio.h>
#include <stdlib.h>
int main()
{
    double e;
    double x, xn, xl; // xn - новый, xl - пред.
    printf ("Enter the constant (e):\n");
    scanf ("%lf", &e);
    printf ("Enter the number:\n");
    while(scanf("%lf",&x)){
    	xn = 1;
    	do {
    		xl = xn;
    		xn = (xl + x/xl)/2;
    	} while ((xn-xl) >= e || (xl-xn) >= e);
    	printf ("Result (f): %f\n", xn);
    	printf ("Result (g): %g\n", xn);
    	printf ("Result (e): %e\n", xn);
    	printf ("Result (.10g): %.10g\n", xn);
    	printf ("Enter the number:\n");
    }
    return 0;
}
