/*
 * Blowfish implementation in SSE2
 * Copyright (C) 2010 Pawel Foremski <pjf@foremski.pl>
 * Licensed under GNU GPL v3
 */

#ifndef _BLOWFISH_H_
#define _BLOWFISH_H_

#include <stdint.h>

struct bf {
	uint32_t P[18];
	uint32_t S[4][256];
};

extern void bfish_init(struct bf *bf, uint8_t *key, uint32_t keylen);
extern void bfish_encrypt(struct bf *bf, void *block);
extern void bfish_decrypt(struct bf *bf, void *block);

#endif
