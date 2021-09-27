#include "xor.h"
#include <immintrin.h>
#include <signal.h>
#include <stdio.h>

byte* const xor(byte* const arr, const uint32_t size, const uint8_t key) {
	if(__builtin_cpu_supports("avx2")) {
		return avx_xor(arr, size, key);
	} else if(__builtin_cpu_supports("sse2")) {
		return sse_xor(arr, size, key);
	} else {
		return slow_xor(arr, size, key);
	}
}

byte* const slow_xor(byte* const arr, const uint32_t size, const uint8_t key) {
	for(byte* it = arr; it != arr + size; ++it) {
		*it ^= key;
	}

	return arr;
}

static void catch_sigill(int errno) {
}

void ignore_SIGILL() {
	struct sigaction sa;
	memset(&sa, 0, sizeof sa);
	sa.sa_handler = catch_sigill;

	signal(SIGILL, catch_sigill);
}
