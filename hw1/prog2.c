#include <stdio.h>
#include <stdlib.h>
void bin (int x)
{
	int b, a = 1;
	a = a << 31;
	for (int i = 0; i < 32; i++){
		b = x & a;
		if (b != a){
			printf ("0");
		}else 
			printf ("1");
		x = x << 1;
	}
	printf ("\n");
}

int shift (char direction, unsigned int n, unsigned int x)
{
	int b, a = 1;
	a = a << 31;
	if (direction == 'L'){
		for(int i = 0; i < n; i++){
			b = x & a;
			x = x << 1;
			if (b == a){
				x++;
			}
		}
	}
	if (direction == 'R'){
		for(int i = 0; i < n; i++){
			b = x % 2;
			x = x >> 1;
			if (b == 1){
				x = x + a;
			}
		}
	}
	return x;
}

int main()
{
    int x, n, new;
    unsigned int x1;
    char dir = 0;
    printf("Enter the number:\n");
    scanf ("%d", &x);
    printf("Number in binary:\n");
    bin (x);
    printf("Enter unsigned number:\n");
    scanf ("%u", &x1);
    printf("Enter L/R\n");
    getchar();                           // очищение
    scanf("%c", &dir);
    printf ("Enter n\n");
    scanf ("%u", &n);
    new = shift (dir, n, x1);
    printf("%u\n", new);
    return 0;
}
