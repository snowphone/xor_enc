#include "xor.h"
#include "byte_array.h"
#include <assert.h>

array_t* read_from_file(const char* path) {
	uint32_t capacity = 1;
	array_t* arr = init_array(capacity);

	FILE* fp = fopen(path, "rb");
	int n_read = 0;
	do {
		n_read = fread(arr->arr + arr->len, sizeof(byte), capacity - arr->len, fp);
		arr->len += n_read;

		if(arr->len == capacity) {
			arr = resize_array(arr, capacity *= 2);
		}
	}while (n_read);

	fclose(fp);
	return arr;
}

int main(int argc, const char* argv[]) {
	if(argc == 1) {
		printf("Usage: %s <number> [file path]\n", argv[0]);
		return 1;
	}

	int key = atoi(argv[1]);

	const char* path;
	if(argc == 2)
		path = "/dev/stdin";
	else
		path = argv[2];

	array_t* arr = read_from_file(path);
	xor(arr->arr, arr->len, key);

	fwrite(arr->arr, sizeof(byte), arr->len, stdout);

	return 0;
}
