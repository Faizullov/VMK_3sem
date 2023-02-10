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


int printmas (int *a, int n){
	for (int i = 0; i < n; i++){
		printf("%d ", a[i]);
	}
	return 0;
}


int bits (int x){
	int cnt = 0;
	while (x != 0) {
		if (x % 2 == 1){
			cnt ++;
		}
		x = x / 2;	
	}
	return cnt;
}


int bitsort (int *a, int n){
	int dop, bitcounter1, bitcounter2, j;
	for (int i = 1; i < n; i ++){
		bitcounter2 = bits(a[i]);
		bitcounter1 = bits(a[i-1]);
		j = i;
		while (((bitcounter2 < bitcounter1) || ((bitcounter2 == bitcounter1) && (a[j] > a[j-1]))) && (j != 0)){
			dop = a[j];
			a[j] = a[j-1];
			a[j-1] = dop;
			j--;
			bitcounter2 = bits(a[j]);
			bitcounter1 = bits(a[j-1]);
		} 		
	}
	return 0;
}


int main(){
	int x, counter = 0;
	int *p;
	printf ("Enter numbers\n");
	p = malloc(sizeof(int));		  // выделяю память для 1 элемента
	while (scanf("%d", &x)){          // считываем массив пока не будет не будет CTRL^D
		counter++;
		p = realloc (p, counter * sizeof(int));    // расширяю массив
		p[counter-1] = x;
	}
	printmas(p, counter);
	printf ("\n");
	for (int i = 0; i < counter; i++){
		bin(p[i]);
	}
	bitsort(p, counter);
	printmas(p, counter);
	printf("\n");
	free(p);
	return 0;	
}
