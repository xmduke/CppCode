// Ex3_LittleOrBig.cpp : �������̨Ӧ�ó������ڵ㡣
//3.�ж�һ��ƽ̨�ǵ�λ���Ȼ��Ǹ�λ����

#include "stdafx.h"

void LittleOrBig()
{
	int a = 0x01;
	char *p = (char*)&a;
	if (0 == *p)
	{
		printf("��λ����\n");
	}
	else
	{
		printf("��λ����\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//˼·��ͨ������һ��4�ֽڵ����ݣ�������2���ֽڸ��Ƴ��������жԱ�
	//     ��������Ϊ��λ���ȣ����������Ϊ��λ����
	//��˶���int����
	/*int a = 0xFF;
	short b;
	memcpy(&b, &a, 2);
	if (a == b)
	{
		printf("��λ����\n");
	}
	else
	{
		printf("��λ����");
	}*/
	LittleOrBig();
	return 0;
}

