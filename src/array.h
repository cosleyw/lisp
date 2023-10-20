#ifndef LISP_ARRAY_H
#define LISP_ARRAY_H

#include<stddef.h>

typedef struct {
	size_t length, itemsz;
	void *data;
} Array;

Array array_init(size_t len, size_t itemsz);
void array_free(Array arr);
void array_resize(Array arr, size_t newsz);
void* array_get(Array arr, size_t ind);
Array array_slice(Array arr, size_t l, size_t r);

#endif
