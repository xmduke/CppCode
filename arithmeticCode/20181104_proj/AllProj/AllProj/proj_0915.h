#pragma once
#include <stdio.h>
int ipstr2int(const char *ip, unsigned int *ipvalue)
{
	if (ip == NULL || ipvalue == NULL)
		return -1;

	unsigned int result = 0;
	int tmp = 0;
	int shift = 24;
	const char *pEnd = ip;
	const char *pStart = ip;

	while (*pEnd != '\0')
	{
		//�ҵ���ַ����ġ�.��
		while (*pEnd != '.' && *pEnd != '\0')
			pEnd++;
		tmp = 0;
		//����ÿ����.��֮�����ֵ"192"-->192
		//atoi
		while (pStart < pEnd)
		{
			tmp = tmp * 10 + (*pStart - '0');
			pStart++;
		}
		if (tmp < 0 || tmp >255)
		{
			return -1;
		}
		//������õ���ֵ�ֱ�����24λ��16λ��8λ��0λ
		result += (tmp << shift);
		shift -= 8;
		if (*pEnd == '\0')
			break;
		pStart = pEnd + 1;
		pEnd++;
	}
	*ipvalue = result;
	return 1;
}
//0x12 34 56 78-->��18.52.86.120��
int ip2str(unsigned int ip, char *buf, size_t len)
{
	if (buf == NULL || len < 16)
	{
		return -1;
	}
	size_t length = sizeof(ip);//32λip��ַ���ֽ���
	unsigned char *p = (unsigned char *)&ip + sizeof(ip) - 1;//ָ��ip��ַ����ֽ�,��λ����
	char *p1 = buf;
	while (length)
	{
		unsigned char tmp = *p;
		char *pstart = p1;
		//18-->'81'-->'18'
		do
		{
			*p1++ = tmp % 10 + '0';
			tmp /= 10;
		} while (tmp);

		char *pend = p1 - 1;//pendָ�����һ���ַ�
		//'81'-->'18'
		for (; pstart < pend; pstart++, pend--)
		{
			char ch = *pstart;
			*pstart = *pend;
			*pend = ch;
		}

		if (length > 1)
			*p1++ = '.';//����һ��.�����һ�����֣�����Ҫ��
		length--;

		p--;//ָ��͵�ַ���ֽ�
	}
	*p1 = '\0';//ip��ַ���ú���
	return 1;

}
//0x12 34 56 78-->��18.52.86.120��
int iptostr(unsigned int ip, char *buf, size_t len)
{
	if (buf == NULL || len < 16)
	{
		return -1;
	}
	unsigned char *p = (unsigned char *)&ip;
	sprintf(buf, "%u.%u.%u.%u", *(p + 3), *(p + 2), *(p + 1), *(p));//��λ����ϵͳ
	return 0;
}