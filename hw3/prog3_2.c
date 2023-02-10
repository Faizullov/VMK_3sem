#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char *search(char *str, char *substr){
	char *begining;
	int k1, k2, cnt = 1;
	k1 = strlen(str);
	k2 = strlen(substr);
	for(int i = 0; i < k1; i++){
		cnt = 1;
		if (str[i] == substr[0]){
			for (int j = 1; j < k2; j++){
				if (str[i+j] != substr[j]){
					break;
				}
				cnt++;
			}
			if (cnt == k2){
				begining = &str[i];
				return begining;
			}
		}
	}
	return NULL;
}

int main(){
	char *str;
	char *substr;
	char *begining;
	int t = 0;
	printf("Enter string:\n");
	str = scanstr();
	printf("Enter substring:\n");
	substr = scanstr();
	begining = search(str, substr);
	if (begining == NULL){
		printf("SSS");
	}
	while (begining != NULL){
		t++;
		printf("%d) array:\n", t);
		printf("%s\n", begining);
		begining++;
		begining = search(begining, substr);
	}
	
	free(str);
	free(substr);
	return 0;	
}
