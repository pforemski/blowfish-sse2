CFLAGS = -O0 -g

default: all
all: blowfish.o test test-loop-asm test-loop-ref

blowfish.o: blowfish.s
	as blowfish.s -o blowfish.o

blowfish2.o: ref/blowfish.c ref/blowfish.h
	gcc $(CFLAGS) -c ref/blowfish.c -o blowfish2.o

test: blowfish.o blowfish2.o blowfish.h test.c
	gcc $(CFLAGS) blowfish.o blowfish2.o test.c -o test

test-loop-asm: test test-loop-asm.c
	gcc blowfish.o test-loop-asm.c -o test-loop-asm

test-loop-ref: test test-loop-ref.c
	gcc $(CFLAGS) blowfish2.o test-loop-ref.c -o test-loop-ref

.PHONY: clean
clean:
	-rm -f *.o
