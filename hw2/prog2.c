#include <stdio.h>
#include <stdlib.h>

int printmas(char **a, int n, int m){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			printf("%c ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}

char **change1(char **a, int n, int m, char x){
	char **p;
	p = malloc(sizeof(char*)*n);
	for (int i = 0; i < n; i++){
		p[i] = malloc(sizeof(char)*m);
	}
	int counter = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			p[i][j] = a[i][j];
		}
	}
	
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (a[i][j] == x){
				for(int k = 0; k < m; k++){
					p[counter][k] = '#';
				}
				for(int k = 0; k < n; k++){
					p[k][j] = '#';
				}
			}
		}
		counter++;
	}
	return p;                  								// adress return
}

char **change2(char **a, int n, int m, char x){
	int t;
	a = realloc(a, sizeof(*a)*(n+1));						// changing size
	a[n] = malloc (sizeof(char)*m);
	for (int j = 0; j < m; j ++){
		a[n][j] = '-'; 
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (a[i][j] == x){
				if (a[n][j] != '-'){
					t = a[n][j] - '0';
					for (int k = 0; k < m; k++){
						a[t][k] = '#';
					}
				} 
				a[n][j] = '0' + i;	
			}
		}
	}
	for (int j = 0; j < m; j++){
		if (a[n][j] != '-'){
			t = a[n][j] - '0';
			for (int k = 0; k < m; k++){
				a[t][k] = '#';
			}
			for (int k = 0; k < n; k++){
				a[k][j] = '#';
			}
		}
	}
	free(a[n]);
	a = realloc(a, sizeof(*a)*n);
	return a;
}

int main(){
	int n, m;
	char x;
	char **new;
	printf("Enter n:\n");
	scanf("%d", &n);
	printf("Enter m:\n");
	scanf("%d", &m);
	printf("Enter x:\n");
	getchar();
	scanf("%c", &x);
	char **a;
	a = malloc(sizeof(char*)*n);
	for (int i = 0; i < n; i++){
		a[i] = malloc(sizeof(char)*m);
	}
	printf ("Enter array of numbers:\n");
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			getchar();						// space, \n
			scanf("%c", &a[i][j]);
		}
	}
	printf("Print array of numbers:\n");
	printmas(a, n, m);
	new = change1(a, n, m, x);
	printf("New array, first option:\n");
	printmas(new, n, m);
	printf("New array, second option:\n");
	a = change2(a, n, m, x);
	printmas(a, n, m);
	for (int i = 0; i < n; i++){           // clear
		free (new [i]);
	}
	free (new);
	for (int i = 0; i < n; i++){
		free (a[i]);
	}
	free(a);
	return 0;	
}
