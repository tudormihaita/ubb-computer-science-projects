#include <string.h>
#include <stdlib.h>
#include "repository.h"


Vector* create_empty(DestroyFct dfnc) {
	Vector* vector = (Vector*)malloc(sizeof(Vector));
	if (vector) {
		vector->capacity = 2;
		vector->size = 0;
		vector->elems = (TElem*)malloc(vector->capacity * sizeof(TElem));
		vector->dfnc = dfnc;
	}
	return vector;
}


Vector* copy_vector(Vector* vector, CopyFct copy) {
	Vector* copy_vector = create_empty(vector->dfnc);
	if (copy_vector) {
		for (int i = 0; i < vector->size; i++) {
			TElem elem = get_element(vector, i);
			add_element(copy_vector, copy(elem));
		}
	}
	return copy_vector;
}


int get_size(Vector* vector) {
	return vector->size;
}


TElem get_element(Vector* vector, int id) {
	//if (id > 0 && id <= vector->size)
	return vector->elems[id];
}


void set_size(Vector* vector, int size) {
	vector->size = size;
}


TElem set_element(Vector* vector, int id, TElem elem) {
	TElem replaced = vector->elems[id];
	vector->elems[id] = elem;
	return replaced;
}


void redim_vector(Vector* vector) {
	int new_capacity = vector->capacity * 2;
	TElem* new_vector = (TElem*)malloc(new_capacity * sizeof(TElem));
	if (new_vector) {
		for (int i = 0; i < vector->size; i++) {
				new_vector[i] = vector->elems[i];
		}
		free(vector->elems);
		vector->elems = new_vector;
		vector->capacity = new_capacity;
	}
}


void add_element(Vector* vector, TElem elem) {
	if (vector->size >= vector->capacity)
		redim_vector(vector);

	vector->elems[vector->size] = elem;
	vector->size++;
}


TElem delete_element(Vector* vector, int id) {
	TElem deleted = vector->elems[id];
	for (int i = id; i < vector->size - 1; i++)
		vector->elems[i] = vector->elems[i + 1];
	vector->size--;
	return deleted;
}


int exchange_elements(Vector* vector, int id1, int id2) {
	if (id1 >= 0 && id1 < vector->size && id2 >= 0 && id2 < vector->size) {
		TElem aux;
		aux = vector->elems[id1];
		vector->elems[id1] = vector->elems[id2];
		vector->elems[id2] = aux;
		return  0;}
	else
		return -1;
}


void destroy_vector(Vector* vector) {
	for (int i = 0; i < vector->size; i++) {
		vector->dfnc(vector->elems[i]);
	}
	vector->size = 0;
	free(vector->elems);
	free(vector);
}