#ifndef LISP_NODE_H
#define LISP_NODE_H

#include<stddef.h>

enum Node_Type{
	NODE_IDENTIFIER,
	NODE_NUMBER,
	NODE_LIST
};

struct Node {
	struct Node *car, *cdr;
	enum Node_Type type;
	size_t size;
};


struct Node *node_init(enum Node_Type type, struct Node *l, struct Node *r);
void node_print(struct Node *nd);

#endif
