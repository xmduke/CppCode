// Ex_IPv4toFF.cpp : 定义控制台应用程序的入口点。
//Ex.把一个IPv4地址字符串与32位整数进行转换 255.255.255.255 <-> 0xFFFFFFFF
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
	//思路：按点分割，然后转换成十进制数，再通过位运算组合
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
			//转十进制

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
			//ip值校验
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
		if (ipNum < 10)//个位
		{
			flag = 1;
			nRes[0] = ipNum + 0x30;
		}
		else if (ipNum < 100 && ipNum >= 10)//十位
		{
			flag = 2;
			nRes[0] = (ipNum / 10) + 0x30;
			nRes[1] = (ipNum % 10) + 0x30;
		}
		else//百位
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
	//思路，把整数按字节获取出来保存到一个数组中，按数值进行转换为字符串，然后进行拼接并加 '.'
	unsigned int iptmp[4] = { 0 };
	iptmp[0] = (ipNum & 0xff000000) >> 24;
	iptmp[1] = (ipNum & 0x00ff0000) >> 16;
	iptmp[2] = (ipNum & 0x0000ff00) >> 8;
	iptmp[3] = ipNum & 0x000000ff;

	char ipstrtmp[4][3] = {0};

	//保存字符数目
	int size[4] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		size[i] = DecToChar(ipstrtmp[i], iptmp[i]);
		if (size[i] == NULL)
		{
			return NULL;
		}
	}

	//拼接
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
	//测试ip转整数
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
		printf("ip值不合法\n");
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
		printf("ip值不合法\n");
		//printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
	}*/


	//测试整数转ip字符串
	printf("\n");
	char ipcharstr[16] = {0};
	ipNumToipstr(ipcharstr, 0xffffffff);
	if (NULL == *ipcharstr)
	{
		printf("ip不合法\n");
	}
	else
	{
		printf("%s\n", ipcharstr);
	}
	
	char ipcharstr2[16] = { 0 };
	ipNumToipstr(ipcharstr2, 0xc0a80101);
	if (NULL == *ipcharstr2)
	{
		printf("ip不合法\n");
	}
	else
	{
		printf("%s\n", ipcharstr2);
	}

	char ipcharstr3[16] = { 0 };
	ipNumToipstr(ipcharstr3, 0x00000000);
	if (NULL == *ipcharstr3)
	{
		printf("ip不合法\n");
	}
	else
	{
		printf("%s\n", ipcharstr3);
	}

	return 0;
}

/*方案一存在缺陷
int CharToDec(char bchar, char bchar2, char bchar3)
{
int btmp = 0;

//百位
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

//十位
if (btmp != 0)
{
//有百位
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
//只有十位
btmp = (bchar2 - 0x30) * 10;
}
}

//个位
if (btmp == 0)
{
//只有个位
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
//转十进制

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
//ip值校验
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
printf("ip值不合法\n");
//printf("0x%02x%02x%02x%02x\n", *iparray, *(iparray + 1), *(iparray + 2), *(iparray + 3));
}
*/
