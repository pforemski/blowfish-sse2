default: all
all: blowfish.o test

blowfish.o: blowfish.s
	as -g blowfish.s -o blowfish.o

blowfish2.o: ref/blowfish.c ref/blowfish.h
	gcc -g -c ref/blowfish.c -o blowfish2.o

test: blowfish.o blowfish2.o blowfish.h test.c
	gcc -g blowfish.o blowfish2.o test.c -o test

.PHONY: clean
clean:
	-rm -f *.o
