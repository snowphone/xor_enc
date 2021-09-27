#include "xor.h"
#include <immintrin.h>
#include <stdint.h>

#define VOIDIFY(ptr) ((void*)(ptr))

// I don't know why but in my NAS (N4000 processor), building SSE intrinsics with -mavx2 flag won't work.

byte* const sse_xor(byte* const arr, const uint32_t size, const uint8_t key) {
	fprintf(stderr, "SSE accelerated\n");
	//__m128i key_chunk = _mm_set1_epi8(key);
	__m128i key_chunk;
	memset(&key_chunk, key, sizeof key_chunk);
	const uint32_t VECTOR_UNIT = 128 / 8;

	int i;
	for(i = 0; i + VECTOR_UNIT < size; i += VECTOR_UNIT) {
		__m128i chunk = _mm_loadu_si128(VOIDIFY(arr + i));
		chunk = _mm_xor_si128(chunk, key_chunk);
		_mm_storeu_si128(VOIDIFY(arr + i), chunk);
	}


	if (i < size) {
		slow_xor(arr + i, size - i, key);
	}

	return arr;
}
