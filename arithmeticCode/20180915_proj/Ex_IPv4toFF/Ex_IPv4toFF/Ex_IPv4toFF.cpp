// Ex_IPv4toFF.cpp : �������̨Ӧ�ó������ڵ㡣
//Ex.��һ��IPv4��ַ�ַ�����32λ��������ת�� 255.255.255.255 <-> 0xFFFFFFFF
//

#include "stdafx.h"

int CharToDec_v2(char *bchar, int size)
{
	int iNum;
	if (size == 1)
	{
		iNum = (*bchar) - 0x30;
	}
	if (size == 2)
	{
		iNum = ((*bchar) - 0x30) * 10 + (*(bchar + 1) - 0x30);
	}
	if (size == 3)
	{
		iNum = ((*bchar) - 0x30) * 100 + (*(bchar + 1) - 0x30) * 10 + (*(bchar + 2) - 0x30);
	}
	return iNum;
}

int IPv4To10_v2(char *ip)
{
	//˼·������ָȻ��ת����ʮ����������ͨ��λ�������
	char iptmp[3] = { 0 };
	int i = 0;
	int iparray[4] = { 0 };
	int times = 0;
	int nRes = 0;

	while (*ip != '\0')
	{
		iptmp[i] = *ip;
		//*iptmp++;
		i++;
		*ip++;
		if (*ip == '.' || *ip == '\0')
		{
			//תʮ����

			iparray[times] = CharToDec_v2(iptmp, i);
			times++;
			if (times == 4)
			{
				break;
			}
			*ip++;
			i = 0;
		}
	}

	for (int n = 0; n < 4; n++)
	{
		if (iparray[n] > 255)
		{
			//ipֵУ��
			return -2;
		}
	}

	nRes = ((*iparray) << 24)
		| ((*(iparray + 1) << 16))
		| ((*(iparray + 2) << 8))
		| ((*(iparray + 3)));

	return nRes;
}

int DecToChar(char nRes[], int ipNum)
{
	//char nRes[3] = { 0 };
	int flag = 0;
	if (ipNum >= 0 && ipNum <= 255)
	{
		if (ipNum < 10)//��λ
		{
			flag = 1;
			nRes[0] = ipNum + 0x30;
		}
		else if (ipNum < 100 && ipNum >= 10)//ʮλ
		{
			flag = 2;
			nRes[0] = (ipNum / 10) + 0x30;
			nRes[1] = (ipNum % 10) + 0x30;
		}
		else//��λ
		{
			flag = 3;
			*nRes = (ipNum / 100) + 0x30;
			*(nRes+1) = ((ipNum / 10) % 10) + 0x30;
			*(nRes+2) = (ipNum % 10) + 0x30;
		}
	}
	else
	{
		//
		return NULL;
	}
	return flag;
}

char *ipNumToipstr(char *ipstr, unsigned int ipNum)
{
	//˼·�����������ֽڻ�ȡ�������浽һ�������У�����ֵ����ת��Ϊ�ַ�����Ȼ�����ƴ�Ӳ��� '.'
	unsigned int iptmp[4] = { 0 };
	iptmp[0] = (ipNum & 0xff000000) >> 24;
	iptmp[1] = (ipNum & 0x00ff0000) >> 16;
	iptmp[2] = (ipNum & 0x0000ff00) >> 8;
	iptmp[3] = ipNum & 0x000000ff;

	char ipstrtmp[4][3] = {0};

	//�����ַ���Ŀ
	int size[4] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		size[i] = DecToChar(ipstrtmp[i], iptmp[i]);
		if (size[i] == NULL)
		{
			return NULL;
		}
	}

	//ƴ��
	//char ipstr[15] = { 0 };
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < size[i]; j++)
		{
			ipstr[count] = ipstrtmp[i][j];
			count++;
		}
		if (i == 3)
		{
			ipstr[count] = '\0';
			//count++;
			return ipstr;
		}
		ipstr[count] = '.';
		count++;
	}
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//����ipת����
	int iparray = IPv4To10_v2("192.168.1.1");
	if (iparray != -2)
	{
		printf("0x%08x\n", iparray);
	}

	int iparray2 = IPv4To10_v2("255.255.255.255");
	if (iparray2 != -2)
	{
		printf("0x%08x\n", iparray2);
	}

	int iparray3 = IPv4To10_v2("0.0.0.0");
	if (iparray3 != -2)
	{
		printf("0x%08x\n", iparray3);
	}

	int iparray4 = IPv4To10_v2("256.0.0.0");
	if (iparray4 != -2)
	{
		printf("0x%08x\n", iparray4);
	}
	else
	{
		printf("ipֵ���Ϸ�\n");
	}
/*int *iparray = IPv4To10_v2("192.168.1.1");
	if (iparray != 0)
	{
		printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
	}

	int *iparray2 = IPv4To10_v2("255.255.255.255");
	if (iparray2 != 0)
	{
		printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
	}

	int *iparray3 = IPv4To10_v2("0.0.0.0");
	if (iparray3 != 0)
	{
		printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
	}

	int *iparray4 = IPv4To10_v2("256.0.0.0");
	if (iparray4 == 0)
	{
		printf("ipֵ���Ϸ�\n");
		//printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
	}*/


	//��������תip�ַ���
	printf("\n");
	char ipcharstr[16] = {0};
	ipNumToipstr(ipcharstr, 0xffffffff);
	if (NULL == *ipcharstr)
	{
		printf("ip���Ϸ�\n");
	}
	else
	{
		printf("%s\n", ipcharstr);
	}
	
	char ipcharstr2[16] = { 0 };
	ipNumToipstr(ipcharstr2, 0xc0a80101);
	if (NULL == *ipcharstr2)
	{
		printf("ip���Ϸ�\n");
	}
	else
	{
		printf("%s\n", ipcharstr2);
	}

	char ipcharstr3[16] = { 0 };
	ipNumToipstr(ipcharstr3, 0x00000000);
	if (NULL == *ipcharstr3)
	{
		printf("ip���Ϸ�\n");
	}
	else
	{
		printf("%s\n", ipcharstr3);
	}

	return 0;
}

/*����һ����ȱ��
int CharToDec(char bchar, char bchar2, char bchar3)
{
int btmp = 0;

//��λ
if (bchar == '1')
{
btmp = 100;
}
else if (bchar == '2')
{
btmp = 200;
}
else
{
btmp = 0;
}

//ʮλ
if (btmp != 0)
{
//�а�λ
btmp = btmp + (bchar2 - 0x30) * 10;
}
else
{
if (bchar2 == 0)
{
btmp = 0;
}
else
{
//ֻ��ʮλ
btmp = (bchar2 - 0x30) * 10;
}
}

//��λ
if (btmp == 0)
{
//ֻ�и�λ
btmp = bchar3 - 0x30;
}
else
{
btmp = btmp + (bchar3 - 0x30);
}

return btmp;

}

int* IPv4To10(char *ip)
{
char iptmp[3] = {0};
int i = 0;
int iparray[4] = { 0 };
int times = 0;
//int nRes = 0;

while (*ip != '\0')
{
if (*ip == '.' || times == 3)
{
//תʮ����

iparray[times] = CharToDec(iptmp[0], iptmp[1], iptmp[2]);
times++;
if (times == 4)
{
break;
}
*ip++;
i = 0;
}
else
{
iptmp[i] = *ip;
//*iptmp++;
i++;
*ip++;
}
}

for (int n = 0; n < 4; n++)
{
if (iparray[n] > 255)
{
//ipֵУ��
return 0;
}
}
//nRes = (unsigned char)iparray[0] << 3 | (unsigned char)iparray[1] << 2 | (unsigned char)iparray[2] << 1 | (unsigned char)iparray[3];
return iparray;
}
*/

/*
/*
int *iparray = IPv4To10("192.168.001.001");
if (iparray != 0)
{
printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
}

int *iparray2 = IPv4To10("255.255.255.255");
if (iparray2 != 0)
{
printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
}

int *iparray3 = IPv4To10("000.000.000.000");
if (iparray3 != 0)
{
printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
}

int *iparray4 = IPv4To10("256.000.000.000");
if (iparray4 == 0 )
{
printf("ipֵ���Ϸ�\n");
//printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
}
*/
