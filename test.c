/*
 * Blowfish implementation in SSE2
 * Copyright (C) 2010 Pawel Foremski
 * Licensed under GNU GPL v3
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "blowfish.h"
#include "ref/blowfish.h"

#define KEY "TESTKEY"
#define TESTV { 0xDF, 0x33, 0x3F, 0xD2, 0x30, 0xA7, 0x1B, 0xB4 }

int main(int argc, char *argv[])
{
	struct bf bf;
	BLOWFISH_CTX ctx;
	char LR1[8] = TESTV;
	char LR2[8] = TESTV;
	char TEST[8] = TESTV;

	printf("Test of asm vs. reference implementation\n\n");

	bfish_init(&bf, KEY, sizeof(KEY));
	Blowfish_Init(&ctx, KEY, sizeof(KEY));
	assert(bf.P[0] == ctx.P[0]);
	assert(bf.S[0][0] == ctx.S[0][0]);
	assert(bf.S[1][0] == ctx.S[1][0]);
	assert(bf.S[2][0] == ctx.S[2][0]);
	assert(bf.S[3][0] == ctx.S[3][0]);
	printf("bfish_init OK, 0x%lx == 0x%lx\n", (long unsigned int) bf.P[0], ctx.P[0]);

	bfish_encrypt(&bf, LR1);
	Blowfish_Encrypt(&ctx, (unsigned long *) (LR2+0), (unsigned long *) (LR2+4));
	assert(LR1[0] == LR2[0]);
	assert(LR1[1] == LR2[1]);
	assert(LR1[2] == LR2[2]);
	assert(LR1[3] == LR2[3]);
	assert(LR1[4] == LR2[4]);
	assert(LR1[5] == LR2[5]);
	assert(LR1[6] == LR2[6]);
	assert(LR1[7] == LR2[7]);
	printf("bfish_encrypt OK, 0x%x == 0x%x\n", LR1[0], LR2[0]);

	bfish_decrypt(&bf, LR1);
	Blowfish_Decrypt(&ctx, (unsigned long *) (LR2+0), (unsigned long *) (LR2+4));
	assert(LR1[0] == LR2[0] && LR1[0] == TEST[0]);
	assert(LR1[1] == LR2[1] && LR1[1] == TEST[1]);
	assert(LR1[2] == LR2[2] && LR1[2] == TEST[2]);
	assert(LR1[3] == LR2[3] && LR1[3] == TEST[3]);
	assert(LR1[4] == LR2[4] && LR1[4] == TEST[4]);
	assert(LR1[5] == LR2[5] && LR1[5] == TEST[5]);
	assert(LR1[6] == LR2[6] && LR1[6] == TEST[6]);
	assert(LR1[7] == LR2[7] && LR1[7] == TEST[7]);
	printf("bfish_decrypt OK, 0x%hhx == 0x%hhx\n", LR1[0], TEST[0]);

	printf("\nOK!\n");
	return 0;
}
