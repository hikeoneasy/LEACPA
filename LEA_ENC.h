#ifndef __LEAENC_H_
#define __LEAENC_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t byte;
typedef uint32_t word;
#define ROUND 24
#define BLOCK (128/8)
//Byte to Word
void BtoW(byte a[4], word b[1]);
// Word to Byte
void WtoB(byte a[4], word b[1]);


//make round key : empty
void LEA_ENC(byte state[BLOCK], byte MK[BLOCK]);

//round func
void ROUND_ENC(word state[BLOCK >> 2], word RK[6]);


//operation

word ROL(word arr, int k);

word ROR(word arr, int k);







//key schedule
void ENC_KeySchedule_128(byte MK[BLOCK], word RK[6 * ROUND]);


#endif // !1
