#ifndef __LEAFOCPA_H_

#define __LEAFOCPA_H_

#include "LealastCPA.h"

//FILE I/O
void FILE_OPEN2();
void FILE_CLOSE2();

void CPA2(byte* lastroundkey, word f_byte_f_round);



typedef struct TRACE_HEADER2 {
	unsigned char strID[20];
	unsigned int trace_no;
	unsigned int point_no;
	unsigned char strEND[4];
} trace_HEADER2;


int POINT_VERIFY2(int* POINTS, int* TRACE_NUM);

#endif
