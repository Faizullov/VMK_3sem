#include <stdio.h>
#include <stdlib.h>
#define n 4

char *scanstr(){
	char st;
	char *s;
	int count1 = 0, count = 1;
	int cnt = 1;
	s = (char*)malloc(sizeof(char)*n);
	while (scanf("%c", &st)){
		if (st == '\n'){
			break;
		}
		if (count == n){
			cnt++;
			s = (char*)realloc(s, sizeof(char)*cnt*n); 
			count = 1;
		} 
		count1++;
		count++;
		s[count1-1] = st; 
	}
	if (count == n){
		s = (char*)realloc(s, sizeof(char)*cnt*n + sizeof(char)); 
		s[count1] = '\0';
	} else {
		s[count1] = '\0';
	}
	return s;
}

int main(){
	char *str;
	str = scanstr();
	printf("%s\n", str);
	free(str);
	return 0;	
}
