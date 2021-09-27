#include "xor.h"
#include <immintrin.h>
#include <stdio.h>

#define VOIDIFY(ptr) ((void*)(ptr))

byte* const avx_xor(byte* const arr, const uint32_t size, const uint8_t key) {
	fprintf(stderr, "AVX accelerated\n");

	__m256i key_chunk = _mm256_set1_epi8(key);
	const uint32_t VECTOR_UNIT = 256 / 8;

	int i;
	for(i = 0; i + VECTOR_UNIT < size; i += VECTOR_UNIT) {
		__m256i chunk = _mm256_loadu_si256(VOIDIFY(arr + i));
		chunk = _mm256_xor_si256(chunk, key_chunk);
		_mm256_storeu_si256(VOIDIFY(arr + i), chunk);
	}


	if (i < size) {
		slow_xor(arr + i, size - i, key);
	}

	return arr;
}

