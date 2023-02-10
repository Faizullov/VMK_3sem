#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char* str;
	struct node *next;

} node;

typedef struct word{
	char let;
	struct word *next;
} word;

void clearword(word *tmp)
{
	if(tmp != NULL){
		clearword(tmp->next);
		free(tmp);
	}
}

void clear (node* lst){
	if(lst != NULL){
		clear(lst->next);
		free(lst);
	}
}

int readword(word *tmp, char c){
	char k;
	int n;
	if (c == EOF){
		tmp->let = '\0';
		tmp->next = NULL;
		return 0;
	} else
	if (c == '\n'){
		tmp->let = '\0';
		tmp->next = NULL;
		return 0;
	} else
	if (c == ' '){
		tmp->let = '\0';
		tmp->next = NULL;
		return 1;
	}
	tmp->let = c;
	scanf("%c", &k);
	tmp->next = malloc(sizeof(word));
	n = readword(tmp->next, k);              //!!!!
	return n;
}

int length(word *tmp){
	int p = 0;
	word* help = tmp;
	while (help != NULL){
		help = help->next;
		p++;
	}
	return p;
}

char *wordtostr(word *tmp){
	
	int len;
	word *help = tmp;
	len = length(tmp);
	char *s;
	s = malloc(sizeof(char)*len);
	for(int i = 0;i < len; i++){
		s[i] = help->let;
		help = help->next;
	}
	return s;
}

void printnode(node*lst){
	while(lst != NULL){
		printf("%s ", lst->str);
		lst = lst->next;
	} 
}

void changenode(node *lst){
	int check = 1;
	node* help;
	char c;
	while (check == 1){
		word *tmp;        // free tmp
		tmp = malloc(sizeof(word));
		scanf("%c", &c);
		if (c == ' '){	
			clearword(tmp);
			continue;
		} 
		if((c != EOF) && (c != '\n')){
			if((c != ' ') && (c != '\n')){
				check = readword(tmp, c);
				lst->str = wordtostr(tmp);
				clearword(tmp);
			}
		} else {
			check = 0;
		}
		if (check == 0){
			if ((c == '\n') || (c == EOF)){
				help->next = NULL;
			} else{
				lst = NULL;
			}
		} else if ((c != ' ') && (c != '\n')){
			lst->next = malloc(sizeof(node));
			help = lst;
			lst = lst->next;
		}
	}
}

void reverse (node* lst){
	if(lst != NULL){
		reverse(lst->next);
		printf("%s ", lst->str);
	}
}

node* element(node*lst, int k){
	for(int i = 0; i < k; i++){
		lst = lst->next;
	}
	return lst;
}

void alphabet(node* lst){
	int wide = 0;
	node* help = lst;
	char *change;
	while (help != NULL){
		help = help->next;
		wide++;
	}
	for (int i = 0; i < wide-1; i++){
		for (int j = i + 1; j < wide; j++){
			if ((strcmp(element(lst,i)->str, element(lst,j)->str)) > 0){
				change = element(lst,i)->str;
				element(lst,i)->str = element(lst,j)->str;
				element(lst,j)->str = change;
			}
		}
	}
}

int main(){
	node *lst;
	lst = malloc(sizeof(node));
	printf("ENTER WORDS:\n");
	changenode(lst);
	printf("PRINT WORDS:\n");
	printnode(lst);
	printf("\n");
	printf("REVERSED:\n");
	reverse(lst);
	printf("\n");
	printf("FORMATED BY ALPHABET:\n");
	alphabet(lst);
	printnode(lst);
	printf("\n");
	clear(lst);
	return 0;	
}
