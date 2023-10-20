#include"node.h"
#include<stdio.h>
#include<stdlib.h>

struct Node *node_init(enum Node_Type type, struct Node *l, struct Node *r){
	struct Node *nd = malloc(sizeof(struct Node));
	nd->type = type;
	nd->car = l;
	nd->cdr = r;
	return nd;
}

void node_print(struct Node *nd){
	if(nd == NULL)
		return;

	if(nd->type == NODE_LIST){
		printf("(");
		node_print(nd->car);
		printf(")");
	}else if(nd->type == NODE_IDENTIFIER){
		printf("%.*s ", (int)nd->size, (char*)nd->car);
	}else if(nd->type == NODE_NUMBER){
		printf("%ld ", nd->size);
	}else{
		printf("type%d ", nd->type);
	}

	node_print(nd->cdr);

}



