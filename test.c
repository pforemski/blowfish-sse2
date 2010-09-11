#include <stdlib.h>
#include <stdio.h>

#include "blowfish.h"
#include "ref/blowfish.h"

//extern void bfish_init(struct bf *bf, uint8_t *key, uint32_t keylen);
//extern void bfish_encrypt(struct bf *bf, void *block);

int main(int argc, char *argv[])
{
	struct bf bf;
	BLOWFISH_CTX ctx;

	bfish_init(&bf, "ABECADLO", 8);
	Blowfish_Init(&ctx, "ABECADLO", 8);

	printf("Hello, world!\n");
	return 0;
}
