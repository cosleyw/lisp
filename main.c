#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include"src/array.h"
#include"src/node.h"

int one_or_more(char **str, int (*fn)(int)){
	char *cur = *str;
	if(fn(*cur)){
		while(fn(*(++cur)));
		*str = cur;
		return 1;
	}

	return 0;
}

int parse_whitespace(char **str){
	return one_or_more(str, isspace);

}

int parse_identifier(char **str, struct Node **l){
	char *st = *str;
	if(isalpha(**str) && one_or_more(str, isalnum)){
		*l = node_init(NODE_IDENTIFIER, (struct Node*)st, NULL);
		(*l)->size = *str - st;
		return 1;
	}
	return 0;

}

int parse_number(char **str, struct Node **l){
	char *st = *str;
	if(one_or_more(str, isdigit)){
		*l = node_init(NODE_NUMBER, (struct Node*)st, NULL);
		int num = 0;
		sscanf(st, "%d", &num);
		(*l)->size = num;
		return 1;
	}
	return 0;
}

int parse_list(char **str, struct Node **l){
	char *cur = *str;
	*l = node_init(NODE_LIST, NULL, NULL);
	l = &((*l)->car);

	parse_whitespace(&cur);
	if(*cur == '('){
		cur++;
		parse_whitespace(&cur);

		struct Node *r;
		while(parse_identifier(&cur, &r) || parse_number(&cur, &r) || parse_list(&cur, &r)){
			*l = r;
			l = &((*l)->cdr);
			parse_whitespace(&cur);
		}

		if(*cur == ')'){
			cur++;
			*str = cur;
			return 1;
		}
	}

	return 0;
}



size_t builtin_addfn_(struct Node *nd){
	if(nd == NULL)
		return 0;
	return nd->size + builtin_addfn_(nd->cdr); 
}

struct Node *builtin_addfn(struct Node *nd){
	nd->type = NODE_NUMBER;
	nd->size = builtin_addfn_(nd->car->cdr);
	nd->car = (struct Node*)"";
	return nd;
}

size_t builtin_mulfn_(struct Node *nd){
	if(nd == NULL)
		return 1;
	return nd->size * builtin_addfn_(nd->cdr); 
}

struct Node *builtin_mulfn(struct Node *nd){
	nd->type = NODE_NUMBER;
	nd->size = builtin_mulfn_(nd->car->cdr);
	nd->car = (struct Node*)"";
	return nd;
}

struct Node *builtin_carfn(struct Node *nd){
	struct Node *k = nd->car->cdr->car;
	k->cdr = nd->cdr;

	return k;
}

struct Node *builtin_cdrfn(struct Node *nd){
	struct Node *k = nd->car->cdr->car->cdr;
	k->cdr = nd->cdr;
	return k;
}




struct Symbol{
	char *name;
	struct Node *(*fn)(struct Node*);
};

struct Symbol Symbol[] = {
	{"add", builtin_addfn},
	{"mul", builtin_mulfn},
	{"car", builtin_carfn},
	{"cdr", builtin_cdrfn}
};

struct Node* eval(struct Node *nd){
	if(nd == NULL)
		return NULL;

	switch(nd->type){
		case NODE_IDENTIFIER:

		case NODE_NUMBER:
		break;
		case NODE_LIST:
			nd->car = eval(nd->car);
			if(nd->car->type == NODE_IDENTIFIER){
				for(size_t i = 0; i < sizeof(Symbol) / sizeof(Symbol[0]); i++)
					if(strncmp(Symbol[i].name, (char*)nd->car->car, nd->car->size) == 0)
						return Symbol[i].fn(nd);
			}
		break;
			
	}

	nd->cdr = eval(nd->cdr);
	return nd;
}

int main(int c, char **v){
	(void)c;
	char *str = v[1];
	struct Node *nd = NULL;

	if(parse_list(&str, &nd)){
		node_print(nd);
		printf("\n");
		node_print(eval(nd));
		printf("\n");
	}
}


