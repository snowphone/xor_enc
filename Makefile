CFLAGS+=  -O0 -g
OBJECTS = xor_main.o avx_xor.o sse_xor.o xor.o byte_array.o

encrypt: $(OBJECTS)
	$(CC) -o $@ $^ 

libxor.so: sse_xor.o xor.c
	$(CC) -shared -fPIC -o $@ $^ $(CFLAGS)

test: avx_xor.o sse_xor.o xor.o
	$(CC) xor_test.c $^ -ldl -o _test $(CFLAGS) && ./_test
	$(RM) _test

avx_xor.o: avx_xor.c
	$(CC) $(CFLAGS) -mavx2 -c $^ 

clean:
	$(RM) libxor.so $(OBJECTS) encrypt _test
