#include "LealastCPA.h"


FILE* stream_Cipher;
FILE* stream_Plain;
FILE* stream_KEY;
FILE* stream_Trace;



int POINT_VERIFY(int* POINTS, int* TRACE_NUM)
{
	trace_HEADER	in_trace = { 0, };
	FILE* fp = NULL;
	char			FILE_MERGE[_FILE_NAME_SIZE_] = "";


	fopen_s(&fp, "C:\\Users\\easyboan\\Documents\\카카오톡 받은 파일\\exploit\\trace1.trace", "rb");
	if (fp == NULL) {
		printf(" -----------------------------------------------------------------------\n");
		printf("|                          Failed To Read Trace                         |\n");
		printf(" -----------------------------------------------------------------------\n");
		return _FAIL_;
	}

	// 파형 헤더 읽기 (32 바이트)
	fread(in_trace.strID, sizeof(unsigned char), 20, fp);
	fread(&in_trace.trace_no, sizeof(unsigned int), 1, fp);
	fread(&in_trace.point_no, sizeof(unsigned int), 1, fp);
	fread(in_trace.strEND, sizeof(unsigned char), 4, fp);

	fclose(fp);


	printf(" ---------------------------Trace Information---------------------------\n");
	printf("|	The Type Of Point	:	FLOAT				|\n");
	printf("|	The Number Of Trace	:	%d				|\n", in_trace.trace_no);
	printf("|	The Number Of Point	:	%d				|\n", in_trace.point_no);
	printf(" -----------------------------------------------------------------------\n");


	*POINTS = (int)in_trace.point_no;
	*TRACE_NUM = (unsigned int)in_trace.trace_no;

	return _PASS_;
}

double HW(word t)
{
	double cnt = 0;
	for (int i = 0; i < 32; i++)
	{
		cnt += (t >> i) & 0x1;
	}
	return cnt;
}
double HW2(word t)
{
	double cnt = 0;
	for (int i = 0; i < 16; i++)
	{
		cnt += (t >> i) & 0x1;
	}
	return cnt;
}
double HW3(word t)
{
	double cnt = 0;
	for (int i = 0; i < 24; i++)
	{
		cnt += (t >> i) & 0x1;
	}
	return cnt;
}
double HW1(word t)
{
	double cnt = 0;
	for (int i = 0; i < 8; i++)
	{
		cnt += (double)((t >> i) & 0x1);
	}
	return cnt;
}
double CORR(double CORR_L, double CORR_R)
{
	double Correlation = 0.0;
	if (CORR_R <= (double)0) {
		Correlation = (double)0;
	}
	else {
		Correlation = CORR_L / sqrt(CORR_R);
		Correlation = fabs(Correlation);
	}


	return Correlation;
}

word ROL(word arr, int k)
{
	if (k == 0) return arr;

	arr = (arr >> (32 - k)) ^ (arr << k);
	return arr;
}

word ROR(word arr, int k)
{
	int t = 0x1 << (k);
	t -= 1;
	arr = ((arr & t) << (32 - k)) ^ (arr >> k);
	return arr;
}

void FILE_OPEN()
{
	/**/
	fopen_s(&stream_Plain, "C:\\Users\\easyboan\\Documents\\카카오톡 받은 파일\\exploit\\plain.txt", "r");
	if (stream_Plain == NULL)
	{
		puts("1파일 열기 실!패!");
		return;
	}

	fopen_s(&stream_Cipher, "C:\\Users\\easyboan\\Documents\\카카오톡 받은 파일\\exploit\\cipher.txt", "r");
	if (stream_Cipher == NULL)
	{
		puts("2파일 열기 실!패!");
		return;
	}

	fopen_s(&stream_KEY, "C:\\Users\\easyboan\\Documents\\카카오톡 받은 파일\\exploit\\key.txt", "r");
	if (stream_KEY == NULL)
	{
		puts("3파일 열기 실!패!");
		return;
	}

	fopen_s(&stream_Trace, "C:\\Users\\easyboan\\Documents\\카카오톡 받은 파일\\exploit\\trace1.trace", "rb");
	if (stream_Trace == NULL)
	{
		puts("4파일 열기 실!패!");
		return;
	}


}
void BtoW(byte a[4], word b[1])
{
	b[0] = ((word)a[3] << 24) + ((word)a[2] << 16) + ((word)a[1] << 8) + (word)a[0];
}
void WtoB(byte a[4], word* b)
{

	a[0] = *b & 0xff;
	a[1] = (*b >> 8) & 0xff;
	a[2] = (*b >> 16) & 0xff;
	a[3] = (*b >> 24) & 0xff;
}
void FILE_CLOSE()
{
	fclose(stream_Plain);
	fclose(stream_Cipher);
	fclose(stream_KEY);
	fclose(stream_Trace);
}

void CPA( byte* lastroundkey)
{

	char			FOLD_MERGE[_FILE_NAME_SIZE_] = "C:\\Users\\easyboan\\Documents\\카카오톡 받은 파일\\exploit";
	char			FILE_MERGE[_FILE_NAME_SIZE_] = "";
	unsigned int B = 0;
	FILE* fp;
	//int PN = 0;
	//unsigned int TN = 0;
	//POINT_VERIFY(&PN, &TN);
	int POINT_NUM = 0;
	unsigned int TRACE_NUM;
	POINT_VERIFY(&POINT_NUM, &TRACE_NUM);
	//POINT_NUM = _END_POINT_ - _START_POINT_ + (int)1;
	//TRACE_NUM = 5000;
	//POINT_NUM = 3796;



	byte* cipher = NULL;
	cipher = (byte*)malloc(sizeof(byte) * 10000 * 16);
	if (cipher == NULL) return;
	for (int i = 0; i < 10000 * 16; i++)
	{
		cipher[i] = 0;
	}

	word* C0 = NULL;
	C0 = (word*)malloc(sizeof(word) * 10000);
	if (C0 == NULL) return;
	for (int i = 0; i < 10000; i++)
	{
		C0[i] = 0;
	}


	word* C4 = NULL;
	C4 = (word*)malloc(sizeof(word) * 10000);
	if (C4 == NULL) return;
	for (int i = 0; i < 10000; i++)
	{
		C4[i] = 0;
	}



	double* Mid_value_EX = NULL;
	Mid_value_EX = (double*)malloc(sizeof(double) * 256);
	if (Mid_value_EX == NULL) return;

	double* Mid_value_EXX = NULL;
	Mid_value_EXX = (double*)malloc(sizeof(double) * 256);
	if (Mid_value_EXX == NULL) return;
	



	double* POINT_BUFFER = NULL;
	POINT_BUFFER = (double*)malloc(sizeof(double) * 3884);
	if (POINT_BUFFER == NULL) return;

	


	double* Mid_value_EY = NULL;
	Mid_value_EY = (double*)malloc(sizeof(double) * POINT_NUM);
	if (Mid_value_EY == NULL) return;
	
	//
	double* Mid_value_EYY = NULL;
	Mid_value_EYY = (double*)malloc(sizeof(double) * POINT_NUM);
	if (Mid_value_EYY == NULL) return;
	




	double* MaxPeak = NULL;
	MaxPeak = (double*)malloc(256 * sizeof(double));
	if (MaxPeak == NULL) return;
	
	double Correlation_L = 0; double Correlation_R = 0;
	double Correlation = 0; float P_temp_float = 0.0;

	double** Mid_value_EXY = NULL;
	Mid_value_EXY = (double**)malloc(256 * sizeof(double*));
	if (Mid_value_EXY == NULL) return;

	for (int i = 0; i < 256; i++) {
		Mid_value_EXY[i] = (double*)malloc((unsigned int)POINT_NUM * sizeof(double));
	}
	for (int i = 0; i < 256; i++) { if (Mid_value_EXY[i] == NULL) return; }
	FILE_OPEN();



	for (int i = 0; i < (10000 * 16); i++)
	{
		fscanf_s(stream_Cipher, "%hhx", &cipher[i]);

	}

	int cnt = 0;
	for (int i = 0; i < 10000 * 16; i = i + 16)
	{
		BtoW(&cipher[i], &C0[cnt]);
		cnt++;
	}



	cnt = 0;
	for (int i = 12; i < 10000 * 16; i = i + 16)
	{
		BtoW(&cipher[i], &C4[cnt]);
		cnt++;
	}




	for (int i = 0; i < (CIPHER_NUM); i++)
	{
		C0[i] = ROR(C0[i], 9);

	}



	double a = 0.0;
	for (int attack_byte = 0; attack_byte < 4; attack_byte++) {
		for (int i = 0; i < 256; i++)
		{
			Mid_value_EXX[i] = 0;
			Mid_value_EX[i] = 0;
		}
		for (int i = 0; i < 256; i++)
		{
			MaxPeak[i] = 0.0;
		}

		for (int i = 0; i < POINT_NUM; i++) Mid_value_EYY[i] = 0.0;
		for (int i = 0; i < POINT_NUM; i++) Mid_value_EY[i] = 0.0;
		for (int i = 0; i < POINT_NUM; i++) POINT_BUFFER[i] = 0.0;

		for (int i = 0; i < 256; i++)
		{
			for (int j = 0; j < POINT_NUM; j++)
				Mid_value_EXY[i][j] = 0.0;
		}

		_fseeki64(stream_Trace, 32, SEEK_SET);
		for (int i = 0; i < (int)TRACE_NUM; i++)
		{


			for (int j = 0; j < POINT_NUM; j++)
			{
				fread(&P_temp_float, sizeof(float), 1, stream_Trace);
				POINT_BUFFER[j] = (double)P_temp_float;
				Mid_value_EY[j] += (double)P_temp_float;
				Mid_value_EYY[j] += (double)((double)P_temp_float * P_temp_float);
				P_temp_float = 0.0;
			}
			//_fseeki64(stream_Trace, 32+3796*(i+1), SEEK_SET);
			//_fseeki64(stream_Trace, 32+(3696*(i+1)-(int)_END_POINT_+(int)_START_POINT_), SEEK_SET);

			// 0b f6 ad ba   df69029d   5b72305a   df69029d   cb47c19f   df69029d
			for (int GUESS_KEY = 0; GUESS_KEY < 256; GUESS_KEY++)
			{

				if (attack_byte == 0)
					//1
					a = HW1(C0[i] - (C4[i] ^ (word)(GUESS_KEY)));

				else if (attack_byte == 1)
					//2
					a = HW(C0[i] - (C4[i] ^ (word)((GUESS_KEY) << 8) ^ lastroundkey[0]));

				else if (attack_byte == 2)
					//3

					a = HW(C0[i] - (C4[i] ^ (word)((GUESS_KEY) << 16)));

				else if (attack_byte == 3)
					//4

					a = HW(C0[i] - (C4[i] ^ (word)((GUESS_KEY) << 24) ^ (lastroundkey[0] + lastroundkey[1] << 8 + lastroundkey[2] << 16)));

				else
					printf("err\n");

				Mid_value_EX[GUESS_KEY] += a;
				Mid_value_EXX[GUESS_KEY] += a * a;


				for (int k = 0; k < POINT_NUM; k++)
				{
					Mid_value_EXY[GUESS_KEY][k] += a * POINT_BUFFER[k];

				}
				a = 0.0;
			}




		}

		sprintf_s(FILE_MERGE, _FILE_NAME_SIZE_ * sizeof(char), "%s\\%d", FOLD_MERGE, B + 1);
		_mkdir(FILE_MERGE);

		for (int GUESS_KEY = 0; GUESS_KEY < 256; GUESS_KEY++)
		{
			sprintf_s(FILE_MERGE, _FILE_NAME_SIZE_ * sizeof(char), "%s\\%d\\%03d(0x%02X).txt", FOLD_MERGE, B + 1, GUESS_KEY, GUESS_KEY);
			fopen_s(&fp, FILE_MERGE, "w");
			if (fp == NULL)
			{
				puts("aaa파일 열기 실!패!");
				return;
			}
			for (int j = 0; j < POINT_NUM; j++) {
				Correlation_L = (double)((double)(TRACE_NUM)*Mid_value_EXY[GUESS_KEY][j]) - ((double)Mid_value_EX[GUESS_KEY] * Mid_value_EY[j]);

				Correlation_R = (double)(((double)(TRACE_NUM)*Mid_value_EXX[GUESS_KEY]) - ((double)Mid_value_EX[GUESS_KEY] * Mid_value_EX[GUESS_KEY])) * (((double)(TRACE_NUM)*Mid_value_EYY[j]) - ((double)Mid_value_EY[j] * Mid_value_EY[j]));


				Correlation = CORR(Correlation_L, Correlation_R);

				fprintf_s(fp, "%f\n", Correlation);
				Correlation_L = 0; Correlation_R = 0;

				if (MaxPeak[GUESS_KEY] < Correlation) MaxPeak[GUESS_KEY] = Correlation;
			}
			fclose(fp);
		}

#if 1



		sprintf_s(FILE_MERGE, _FILE_NAME_SIZE_ * sizeof(char), "%s\\%d_GUESS_KEY_PEAK.txt", FOLD_MERGE, B + 1);
		fopen_s(&fp, FILE_MERGE, "w");
		if (fp == NULL)
		{
			puts("aaa파일 열기 실!패!");
			return;
		}
		double Max = 0; unsigned int R_Key = 0;
		for (int Guess_Key = 0; Guess_Key < 256; Guess_Key++) {
			fprintf_s(fp, "%f\n", MaxPeak[Guess_Key]);

			if (Max < MaxPeak[Guess_Key]) {
				Max = MaxPeak[Guess_Key];
				R_Key = Guess_Key;
			}
		}

		fclose(fp);
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++

		double max = 0.0; int maxkey = 0;

		/*

		*/

		for (int guess = 0; guess < 256; guess++)
		{

			if (MaxPeak[guess] > max) {
				max = MaxPeak[guess];
				maxkey = guess;
			}

		}
		printf("%d-th byte attacked \n", attack_byte + 1);
		printf("maxkey %02x      corr:%f\n\n", maxkey, max);
		lastroundkey[attack_byte] = maxkey;

		maxkey = 0;
		max = 0;
		for (int i = 0; i < 2; i++) {
			for (int guess = 0; guess < 256; guess++)
			{

				if (MaxPeak[guess] > max) {
					max = MaxPeak[guess];
					maxkey = guess;
				}

			}
			printf("maxkey %02x      corr:%f\n", maxkey, max);
			MaxPeak[maxkey] = 0.0;
			maxkey = 0;
			max = 0;

		}


		printf("\n\n");

	}
	FILE_CLOSE();
















	free(cipher); free(C0); free(C4); free(Mid_value_EX); free(Mid_value_EXX); free(POINT_BUFFER); free(Mid_value_EY);
	free(Mid_value_EYY); free(MaxPeak);
	for (int i = 0; i < 256; i++) free(Mid_value_EXY[i]);
	free(Mid_value_EXY);
}

void L2M_key(byte* key, word* firstroundkey, byte* MASTERKEY) {
	word Rkey[1] = { 0, };
	const word KeyCon[8] = { 0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957 };
	BtoW(key, Rkey);
	for (int i = 23; i > 0; i--)
	{
		Rkey[0] = ROR(Rkey[0], 1) - ROL(KeyCon[i % 4], i);
	}
	firstroundkey[0] = Rkey[0];
	Rkey[0] = ROR(Rkey[0], 1) - ROL(KeyCon[0], 0);

	WtoB(&MASTERKEY[0], Rkey);
	
}


