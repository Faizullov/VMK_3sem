#include <stdlib.h>
#include <stdio.h>
#define binprint(x){\
    if (sizeof(x) == 1)\
        bin((long long int)x, 8);\
    else if (sizeof(x) == 2)\
        bin((long long int)x, 16);\
    else if (sizeof(x) == 4)\
        bin((long long int)x, 32);\
    else if (sizeof(x) == 8)\
        bin((long long int)x, 64);\
    else \
        bin((long long int)x, sizeof(x)*8);\
}

void bin(long long int x, int size){
    long long int b, a = 1;
	a = a << 63;
    x = x << (64-size);
	for (int i = 0; i < size; i++){
		b = x & a;
		if (b != a){
			printf ("0");
		}else 
			printf ("1");
		x = x << 1;
	}
	printf ("\n");
}
int main(){
    printf("First test!\n");
    char c = -1;
    printf("Char:\n");
    if (c)
        binprint(c)
    else 
        printf("Zero!\n");
    int i = -1;
    long int l = -1;
    long long int ll = -1;
    short s = -1; 
    printf("Short\n");
    if (s)
        binprint(s)
    else 
        printf("Zero!\n");
    printf("Integer\n");
    if (i)
        binprint(i)
    else 
        printf("Zero!\n");
    printf("long:\n");
    if (l)
        binprint(l)
    else 
        printf("Zero!\n");
    printf("long long\n");
    if (ll)
        binprint(ll)
    else 
        printf("Zero!\n");

    printf("(Short)7:\n");
    binprint((short)7);
    l = 123;
    ll = 123;
    i = 123;
    c = 123;
    s = 123;
    printf("Char:\n");
    if (c)
        binprint(c)
    else 
        printf("Zero!\n");
    printf("Short\n");
    if (s)
        binprint(s)
    else 
        printf("Zero!\n");
    printf("Integer\n");
    if (i)
        binprint(i)
    else 
        printf("Zero!\n");
    printf("long:\n");
    if (l)
        binprint(l)
    else 
        printf("Zero!\n");
    printf("long long\n");
    if (ll)
        binprint(ll)
    else 
        printf("Zero!\n");

    /*char k;
    printf("If unincilized:\n");
    if (k)
        binprint(k)
    else 
        printf("Zero!\n"); */
    return 0;
}