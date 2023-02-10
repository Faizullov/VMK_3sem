#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tree {
	char *str;
	struct tree* left;
	struct tree* right;
} tree;

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
	if(lst){
		clear(lst->next);
		free(lst->str);
		free(lst);
	}
}

void cleartree(tree *lst){
	if (lst){
		cleartree(lst->left);
		cleartree(lst->right);
		free(lst);
	}
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
	//printf("%d\n", len);
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

node *changenode(node *lst, word *tmp){
	if (lst == NULL){
		lst = malloc(sizeof(node));
		//printf("%s ", wordtostr(tmp));
		lst->str = wordtostr(tmp);
		lst->next = NULL;
	} else{
		lst->next = changenode(lst->next, tmp);
	}
	return lst;
}

word *changeword(word *tmp, char c){
	if(tmp == NULL){
		tmp = malloc (sizeof(word));
		tmp->let = c;
		tmp->next = NULL;
	}
	else {
		tmp->next = changeword(tmp->next, c);
	}
	return tmp;
}

tree *create(tree *lst, char *s){
	if (lst == NULL){
		lst = malloc(sizeof(tree));
		lst->str = s;
		lst->left = NULL;
		lst->right = NULL;
	}
	else {
		if (strcmp(s, lst->str)){
			lst->right = create(lst->right, s);
	    }else {
			lst->left = create(lst->left, s);
		}
	}
	return lst;
}

tree* createtree(tree* tr, node* lst){
	while(lst != NULL){
		tr = create(tr, lst->str);
		lst = lst->next;
	}
	return tr;
}

void printtree(tree *lst){
	if (lst == NULL)
		return;
	printtree(lst->left);
	printtree(lst->right);
	printf("%s ", lst->str);
	
}

int main(){

	tree *tr;
	tr = NULL;
    char c = 'a', prev = ' ';
	node *lst = NULL;
	word *tmp = NULL;
	printf("ENTER WORDS:\n");
	while ((c != EOF) && (c != '\n')){
		scanf("%c", &c);
		//printf("!");
		if ((c == ' ') && (prev == ' ')){
			prev = c;
			continue;
		}
		if (((c != ' ') && (c != EOF) && (c != '\n')) && (prev == ' ')){
			//printf("?");
			tmp = changeword(tmp, c);
		}
		if (((c != ' ') && (c != EOF) && (c != '\n')) && (prev != ' ')){
			//printf("#");
			tmp = changeword(tmp, c);
		}
		if (((c == ' ') || (c == EOF) || (c == '\n')) && (prev != ' ')){
			tmp = changeword(tmp, '\0');
			lst = changenode(lst, tmp);
			clearword(tmp);
			tmp = NULL;
		}	
		prev = c;	
	}
    printf("PRINT WORDS:\n");
	printnode(lst);    // created list
	tr = createtree(tr, lst);
	printf("\n");
	 printf("PRINT WORDS FROM TREE:\n");
	printtree(tr);
	cleartree(tr);
	clear(lst);
	printf("\n");
    return 0;
}