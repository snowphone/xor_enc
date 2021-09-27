#pragma once


#include <bits/stdint-uintn.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <immintrin.h>


typedef uint8_t byte;

byte* const xor(byte* const arr, const uint32_t size, const uint8_t key);

byte* const slow_xor(byte* const arr, const uint32_t size, const uint8_t key);

byte* const avx_xor(byte* const arr, const uint32_t size, const uint8_t key);

byte* const sse_xor(byte* const arr, const uint32_t size, const uint8_t key);


void ignore_SIGILL();
