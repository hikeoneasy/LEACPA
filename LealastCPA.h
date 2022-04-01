
#ifndef __LEALASTCPA_H_

#define __LEALASTCPA_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <direct.h>

typedef uint8_t byte;
typedef uint32_t word;


/*평문 개수*/
#define PLAIN_NUM 10000

/*파형개수*/
#define _TRACE_NUM 10000

/*암호문 개수*/
#define CIPHER_NUM 10000
#define find 1


/*SPA 구간*/
#define _START_POINT_				0
#define _END_POINT_					3780

/*HW 계산함수 */
double HW(word t);
double HW2(word t);
double HW3(word t);
double HW1(word t);
/* CORR 계산 함수*/
double CORR(double CORR_L, double CORR_R);
//corr_r과 corr_l을 계산해서 넣어야 한다.

void L2M_key(byte* key, byte* firstroundkey, byte* MASTERKEY);
//operation


word ROL(word arr, int k);
word ROR(word arr, int k);

void BtoW(byte a[4], word b[1]);
void WtoB(byte a[4], word* b);
//FILE I/O
void FILE_OPEN();
void FILE_CLOSE();

void CPA(byte* lastroundkey);


typedef struct TRACE_HEADER {
	unsigned char strID[20];
	unsigned int trace_no;
	unsigned int point_no;
	unsigned char strEND[4];
} trace_HEADER;

#define _FILE_NAME_SIZE_	1000
#define _PASS_				1
#define _FAIL_				0

int POINT_VERIFY(int* POINTS, int* TRACE_NUM);

#endif

#pragma once
