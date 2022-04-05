#include "LEA_ENC.h"

void BtoW(byte a[4], word b[1])
{
	b[0] = ((unsigned int)a[3] << 24) + ((unsigned int)a[2] << 16) + ((unsigned int)a[1] << 8) + (unsigned int)a[0];
}

void WtoB(byte a[4], word b[1])
{
	byte cutting = (0x1 << 8)-1;
	a[0] = b[0] & cutting;
	a[1] = (b[0] >> 8) & cutting;
	a[2] = (b[0] >> 16) & cutting;
	a[3] = (b[0] >> 24) & cutting;
}
void LEA_ENC(byte state[BLOCK], byte MK[BLOCK])
{
	word RK[6 * ROUND] = { 0, };
	
	word state_W[4] = { 0, };
	

	for (int i = 0; i < 4; i++)
	{
		BtoW(&state[i * 4], &state_W[i]);
	}

#if(ROUND == 24)
	ENC_KeySchedule_128(MK, RK);
#endif
	for (int i = 0; i < ROUND; i++)
	{
		ROUND_ENC(state_W, &RK[i * 6]);
	}
	for (int i = 0; i < (BLOCK >> 2); i++)
		{
			WtoB(&state[i * 4], &state_W[i]);
		}

}   
void ROUND_ENC(word state[4], word RK[6])
{
	word state_last[4] = { 0, };
	
	state_last[0] = state[0]; state_last[1] = state[1]; state_last[2] = state[2]; state_last[3] = state[3];


	state[0] = ROL(((state_last[0] ^ RK[0]) + (state_last[1] ^ RK[1])), 9);
	state[1] = ROR(((state_last[1] ^ RK[2]) + (state_last[2] ^ RK[3])), 5);
	state[2] = ROR(((state_last[2] ^ RK[4]) + (state_last[3] ^ RK[5])), 3);
	state[3] = state_last[0];
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


void ENC_KeySchedule_128(byte MK[BLOCK], word RK[6*ROUND]) {
	const word KeyCon[8] = { 0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957 };
	word T[(BLOCK / 4)] = { 0, };
	
	
	BtoW(&MK[0], &T[0]); BtoW(&MK[4], &T[1]); BtoW(&MK[8], &T[2]); BtoW(&MK[12], &T[3]);
	

	for (int i = 0; i < ROUND; i++) {
		T[0] = ROL(T[0] + ROL(KeyCon[i % 4], i), 1);
		T[1] = ROL(T[1] + ROL(KeyCon[i % 4], i+1), 3);
		T[2] = ROL(T[2] + ROL(KeyCon[i % 4], i+2), 6);
		T[3] = ROL(T[3] + ROL(KeyCon[i % 4], i+3), 11);
		RK[6 * i] = T[0];
		RK[6 * i + 1] = T[1];
		RK[6 * i + 2] = T[2];
		RK[6 * i + 3] = T[1];
		RK[6 * i + 4] = T[3];
		RK[6 * i + 5] = T[1];
	}
	
}


int main()
{
	byte Key[16] = { 0x0f,0x1e,0x2d,0x3c,0x4b,0x5a,0x69,0x78,0x87,0x96,0xa5,0xb4,0xc3,0xd2,0xe1,0xf0 };
	byte Plain[16] = { 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f };
	LEA_ENC(Plain, Key);

	for (int i=0;i<16;i++)
		printf("%02x ",Plain[i]);

	return 0;
}