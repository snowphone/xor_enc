#include "byte_array.h"

array_t* init_array(int capacity) {
	array_t* arr = malloc(sizeof *arr + capacity);
	arr->len = 0;
	return arr;
}

array_t* resize_array(array_t* arr, int new_capacity) {
	arr = realloc(arr, sizeof *arr + new_capacity);
	return arr;
}

