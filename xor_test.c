#include "xor.h"

#include "bdd-for-c.h"
#include <stdint.h>

#define SIZE(arr) (sizeof arr / sizeof arr[0])

typedef uint8_t byte;

#define ASSERT_AVX2(label)                                                     \
  do {                                                                         \
    if (!__builtin_cpu_supports("avx2")) {                                     \
      check(NULL, "Not allowed to test AVX2 intrinsics");                      \
      goto label;                                                              \
    }                                                                          \
  } while (0)

spec("xor") {
  int test_size = 300;
  uint8_t src[test_size];
  uint8_t expected[test_size];
  uint8_t key = 123;

  before_each() {
    for (int i = 0; i < SIZE(src); ++i) {
      src[i] = i + 1;
    }

    memcpy(expected, src, sizeof src);

    for (int i = 0; i < test_size; ++i) {
      expected[i] ^= key;
    }
  }

  it("should be byte-wisely applied with a naive way") {
    uint8_t *actual = slow_xor(src, test_size, key);

    check(memcmp(expected, actual, sizeof expected) == 0);
  }

  it("should be byte-wisely applied with SSE intrinsics") {
    uint8_t *actual = sse_xor(src, test_size, key);

    check(memcmp(expected, actual, sizeof expected) == 0);
  }

  it("should be byte-wisely applied with AVX intrinsics") {
    ASSERT_AVX2(done1);
    uint8_t *actual = avx_xor(src, SIZE(src), key);

    check(memcmp(expected, actual, sizeof expected) == 0);
  done1:;
  }

  it("should be byte-wisely applied with AVX intrinsics even if the array is "
     "too small") {
    int test_size = 7;
    uint8_t src[test_size];
    uint8_t expected[test_size];
    uint8_t key = 3;

    ASSERT_AVX2(done2);

    for (int i = 0; i < SIZE(src); ++i) {
      src[i] = i + 1;
    }

    memcpy(expected, src, sizeof src);

    for (int i = 0; i < SIZE(src); ++i) {
      expected[i] ^= key;
    }
    uint8_t *actual = avx_xor(src, SIZE(src), key);

    check(memcmp(expected, actual, sizeof expected) == 0);
  done2:;
  }

  it("should choose a proper one based on intrinsics support") {
    byte *const actual = xor(src, SIZE(src), key);

    check(memcmp(expected, actual, sizeof expected) == 0);
  }
}
