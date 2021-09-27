#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef struct {
	uint32_t len;
	uint8_t arr[0];
} array_t;

array_t* init_array(int capacity);

array_t* resize_array(array_t* arr, int new_capacity);
