// Ex4_ChangeInt.cpp : �������̨Ӧ�ó������ڵ㡣
//4.�ı�һ�������Ĵ洢��ʽ��0x12345678->0x87654321��

#include "stdafx.h"

//˼·��ͨ��λ���㽫�ֽڽ����ƶ���
void ToLittle(int * i){
	*i = ((*i & 0xf0000000) >> 28)
		| ((*i & 0x0f000000) >> 20)
		| ((*i & 0x00f00000) >> 12)
		| ((*i & 0x000f0000) >> 4)
		| ((*i & 0x0000f000) << 4)
		| ((*i & 0x00000f00) << 12)
		| ((*i & 0x000000f0) << 20)
		| ((*i & 0x0000000f) << 28);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i = 0x12345678;
	printf("0x%x\n", i);
	ToLittle(&i);
	printf("0x%x\n", i);
	return 0;
}
