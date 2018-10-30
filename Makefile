CFLAGS = -O0 -g -m32 -no-pie -fno-pic

default: all
all: test test-loop-asm test-loop-ref

test: blowfish.s blowfish.h ref/blowfish.c ref/blowfish.h test.c
	gcc $(CFLAGS) blowfish.s ref/blowfish.c test.c -o test

test-loop-asm: blowfish.s blowfish.h test-loop-asm.c
	gcc $(CFLAGS) blowfish.s test-loop-asm.c -o test-loop-asm

test-loop-ref: ref/blowfish.c ref/blowfish.h test-loop-ref.c
	gcc $(CFLAGS) ref/blowfish.c test-loop-ref.c -o test-loop-ref

.PHONY: clean
clean:
	-rm -f test test-loop-asm test-loop-ref
