# LEA 부채널 분석


**Chipwhisperer** 를 이용하여 32bit lea의 암호화 파형을 수집하였고, *CPA*(상관전력분석)을 진행하였습니다.


중간값은 **암호화 마지막 라운드**의 첫 word(4byte)와 Key Xor된 값과 암호문의 두번째 word(4byte)의 뺄셈을 이용하여 잡았습니다.

그이후 **암호화 첫라운드**로 다시 파형을 수집한뒤 나머지 키를 공격하였습니다.

이는  LEA의 Keyschedule이 한라운드만 알아도 역으로 거슬러 올라감을 이용한 공격법입니다.



# 구성은 다음과 같습니다.


**LEA 암호화 코드**: LEA.c , LEA.h

**LEA CPA 코드**: LEAlastcpa.c, LEAlastcpa.h LEAlastcpa (2).c, LEAlastcpa (2).h 

**LEA 파형 수집을 위한 코드**: simpleserial-aes.c (기존, aes 파형 수집시 사용했던 코드를 변형 한 것이라 파일명을 바꾸지 않았습니다. makefile을 수정하기 귀찮다,,,,)

