// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

char buffer[33]; //���ڴ��ת���õ�ʮ�������ַ������ɸ�����Ҫ���峤��
char * inttohex(int aa)
{
	static int i = 0;
	if (aa < 16)            //�ݹ�������� 
	{
		if (aa < 10)        //��ǰ��ת�����ַ������ַ��� 
			buffer[i] = aa + '0';
		else
			buffer[i] = aa - 10 + 'A';
		buffer[i + 1] = '\0'; //�ַ���������־ 
	}
	else
	{
		inttohex(aa / 16);  //�ݹ���� 
		i++;                //�ַ�������+1 
		aa %= 16;           //���㵱ǰֵ
		if (aa < 10)        //��ǰ��ת�����ַ������ַ��� 
			buffer[i] = aa + '0';
		else
			buffer[i] = aa - 10 + 'A';
	}
	return (buffer);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int num;
	char * hex_str;
	printf("Enter a number: ");
	scanf("%d", &num);
	hex_str = inttohex(num);
	printf("Hexadecimal number: %sH\n", hex_str);
	getchar();
	return 0;
}

