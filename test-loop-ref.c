#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ref/blowfish.h"

#define KEY "TESTKEY"
#define TESTV { 0xDF, 0x33, 0x3F, 0xD2, 0x30, 0xA7, 0x1B, 0xB4 }

int main(int argc, char *argv[])
{
	BLOWFISH_CTX ctx;
	char LR[8] = TESTV;
	char TEST[8] = TESTV;
	unsigned int i, j, iter;

	if (argc < 2) {
		fprintf(stderr, "Usage: test-loop-ref <iterations*10^6 = 1>\n");
		return 1;
	}

	iter = atoi(argv[1]);
	printf("Test of reference implementation speed - doing %u milions iterations\n\n", iter);

	Blowfish_Init(&ctx, KEY, sizeof(KEY));
	printf("Blowfish_Init OK\n");

	printf("Blowfish_Encrypt...");
	for (i = 0; i < iter; i++)
		for (j = 0; j < 1000000; j++)
			Blowfish_Encrypt(&ctx, (unsigned long *) (LR+0), (unsigned long *) (LR+4));
	printf(" done\n");

	printf("Blowfish_Decrypt...");
	for (i = 0; i < iter; i++)
		for (j = 0; j < 1000000; j++)
			Blowfish_Decrypt(&ctx, (unsigned long *) (LR+0), (unsigned long *) (LR+4));
	printf(" done\n");

	printf("is the result valid...");
	assert(LR[0] == TEST[0]);
	assert(LR[1] == TEST[1]);
	assert(LR[2] == TEST[2]);
	assert(LR[3] == TEST[3]);
	assert(LR[4] == TEST[4]);
	assert(LR[5] == TEST[5]);
	assert(LR[6] == TEST[6]);
	assert(LR[7] == TEST[7]);
	printf(" it is!: 0x%hhx%hhx%hhx%hhx 0x%hhx%hhx%hhx%hhx\n",
		LR[0], LR[1], LR[2], LR[3], LR[4], LR[5], LR[6], LR[7]);

	return 0;
}
