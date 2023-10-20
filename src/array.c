#include"array.h"
#include<stdlib.h>
#include<string.h>

Array array_init(size_t len, size_t itemsz){
	return (Array){.length = len, .itemsz = itemsz, .data = malloc(len * itemsz)};
}

void array_free(Array arr){
	free(arr.data);
}

void array_resize(Array arr, size_t newsz){
	void *odata = arr.data;
	size_t olength = arr.length;

	arr.length = newsz;
	arr.data = malloc(newsz * arr.itemsz);

	size_t to_copy = olength < newsz ? newsz : olength;
	memcpy(arr.data, odata, to_copy*arr.itemsz);

	free(odata);
}

void* array_get(Array arr, size_t ind){
	return (char*)arr.data + ind*arr.itemsz;
}

Array array_slice(Array arr, size_t l, size_t r){
	Array ret = array_init(r - l, arr.itemsz);
	memcpy(ret.data, (char*)arr.data + l*arr.itemsz, (r-l)*arr.itemsz);
	return ret;
}




