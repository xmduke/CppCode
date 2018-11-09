// Ex_FindIP.cpp : �������̨Ӧ�ó������ڵ㡣
//һ�������ֵ��ַ�����������б�׼��IP�����硰11022345��
// 110.2.234.5 1.102.234.5 1.102.23.45 110.2.23.45

// 1.1.0.22345
// 1.1.02.2345
// 1.1.022.345
// 1.1.0223.45
// 1.1.02234.5
// 1.10.2.2345
// 1.10.22.345
// 1.10.223.45
// 1.10.2234.5
// 1.102.2.345
// 1.102.23.45
// 1.102.234.5
// 1.1022.....
// 11.0.2.2345
// 11.0.22.345
// 11.0.223.45
// 11.0.2234.5
// 11.02.2.345
// 11.02.23.45
// 11.02.234.5
// 11.022.3.45
// 11.022.34.5


#include "stdafx.h"

int calcIPpart(char a, char b, char c)
{
	int num = 0;
	if (a != '\0' && b != '\0' && c!= '\0')
	{
		num = (a - '0') * 100 + (b - '0') * 10 + (c - '0');
	}
	else if (a != '\0' && b != '\0')
	{
		num = (a - '0') * 10 + (b - '0');
	}
	else if (a != '\0')
	{
		num = (a - '0');
	}
	return num;
}
bool IPpart(int num)
{
	if (num >= 0 && num <= 255)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �����ַ����������ip����ʼλ�ã���λ
void getIPpart(char *inIP, char* outIP, int pos, int size)
{
	while (size)
	{
		*outIP = *(inIP + pos);
		outIP++;
		inIP++;
		size--;
	}
}

int getIPLen(char *IP)
{
	int count = 0;
	while (*IP != '\0')
	{
		count++;
		IP++;
	}
	return count;
}

void FindIP(char *IP)
{
	//ѭ����ȡ��һ���ֵ�ip�ַ���
	char point1[3] = { 0 };
	char point2[3] = { 0 };
	char point3[3] = { 0 };
	char point4[3] = { 0 };
	int len = getIPLen(IP);
	//��һ����
	for (int i = 1; i <= 3; i++)
	{
		//point1 3�ֿ���
		getIPpart(IP, point1, 0, i);
		if (i == 1)
		{
			//�ڶ�����
			for (int j = 1; j <= 3; j++)
			{
				//point2 3�ֿ���
				getIPpart(IP, point2, i, j);
				if (j == 1)//point2 1λ��
				{
					for (int m = 1; m <= 3; m++)
					{
						//point3 ����ip�����ж�
						//��ʱpoint4���ݳ��ȿ����ж�
						//0< len - (i+j+m) < 3,����ip���Ϸ� 
						if ((len - (i + j + m)) <= 3 && (len - (i + j + m)) > 0)
						{
							//��ǰһ�α��������0
							point3[0] = 0;
							point3[1] = 0;
							point3[2] = 0;
							point4[0] = 0;
							point4[1] = 0;
							point4[2] = 0;
							getIPpart(IP, point3, i + j, m);
							getIPpart(IP, point4, i+ j + m, (len - (i + j + m)));
							//�жϸ���������0-255֮��
							int part1 = calcIPpart(point1[0], point1[1], point1[2]);
							int part2 = calcIPpart(point2[0], point2[1], point2[2]);
							int part3 = calcIPpart(point3[0], point3[1], point3[2]);
							int part4 = calcIPpart(point4[0], point4[1], point4[2]);
							if (IPpart(part1) && IPpart(part2) && IPpart(part3) && IPpart(part4))
							{
								//������ϵ�ipֵ
								printf("%d.%d.%d.%d\n", part1, part2, part3, part4);
							}
						}
					}
				}
				if (j == 2)//point2 2λ��
				{
					for (int m = 1; m <= 3; m++)
					{
						//point3 3�ֿ���
						//��ʱpoint4���ݳ��ȿ����ж�
						//0< len - (i+j+m) < 3,����ip���Ϸ� 
						if ((len - (i + j + m)) <= 3 && (len - (i + j + m)) > 0)
						{
							//��ǰһ�α��������0
							point3[0] = 0;
							point3[1] = 0;
							point3[2] = 0;
							point4[0] = 0;
							point4[1] = 0;
							point4[2] = 0;
							getIPpart(IP, point3, i+j, m);
							getIPpart(IP, point4, i+j+m, (len - (i + j + m)));
							//�жϸ���������0-255֮��
							int part1 = calcIPpart(point1[0], point1[1], point1[2]);
							int part2 = calcIPpart(point2[0], point2[1], point2[2]);
							int part3 = calcIPpart(point3[0], point3[1], point3[2]);
							int part4 = calcIPpart(point4[0], point4[1], point4[2]);
							if (IPpart(part1) && IPpart(part2) && IPpart(part3) && IPpart(part4))
							{
								//������ϵ�ipֵ
								printf("%d.%d.%d.%d\n", part1, part2, part3, part4);
							}
						}
					}
				}
				if (j == 3)//point2 3λ��
				{
					for (int m = 1; m <= 3; m++)
					{
						//point3 3�ֿ���
						//��ʱpoint4���ݳ��ȿ����ж�
						//0< len - (i+j+m) < 3,����ip���Ϸ� 
						if ((len - (i + j + m)) <= 3 && (len - (i + j + m)) > 0)
						{
							//��ǰһ�α��������0
							point3[0] = 0;
							point3[1] = 0;
							point3[2] = 0;
							point4[0] = 0;
							point4[1] = 0;
							point4[2] = 0;
							getIPpart(IP, point3, i+j, m);
							getIPpart(IP, point4, i+j+m, (len - (i + j + m)));
							//�жϸ���������0-255֮��
							int part1 = calcIPpart(point1[0], point1[1], point1[2]);
							int part2 = calcIPpart(point2[0], point2[1], point2[2]);
							int part3 = calcIPpart(point3[0], point3[1], point3[2]);
							int part4 = calcIPpart(point4[0], point4[1], point4[2]);
							if (IPpart(part1) && IPpart(part2) && IPpart(part3) && IPpart(part4))
							{
								//������ϵ�ipֵ
								printf("%d.%d.%d.%d\n", part1, part2, part3, part4);
							}
						}
					}
				}
			}
		}
		if (i == 2)
		{
			//�ڶ�����
			for (int j = 1; j <= 3; j++)
			{
				//point2 3�ֿ���
				point2[0] = 0;
				point2[1] = 0;
				point2[2] = 0;
				getIPpart(IP, point2, i, j);
				if (j == 1)//point2 1λ��
				{
					for (int m = 1; m <= 3; m++)
					{
						//point3 ����ip�����ж�
						//��ʱpoint4���ݳ��ȿ����ж�
						//0< len - (i+j+m) < 3,����ip���Ϸ� 
						if ((len - (i + j + m)) <= 3 && (len - (i + j + m)) > 0)
						{
							//��ǰһ�α��������0
							point3[0] = 0;
							point3[1] = 0;
							point3[2] = 0;
							point4[0] = 0;
							point4[1] = 0;
							point4[2] = 0;
							getIPpart(IP, point3, i + j, m);
							getIPpart(IP, point4, i + j + m, (len - (i + j + m)));
							//�жϸ���������0-255֮��
							//�жϸ���������0-255֮��
							int part1 = calcIPpart(point1[0], point1[1], point1[2]);
							int part2 = calcIPpart(point2[0], point2[1], point2[2]);
							int part3 = calcIPpart(point3[0], point3[1], point3[2]);
							int part4 = calcIPpart(point4[0], point4[1], point4[2]);
							if (IPpart(part1) && IPpart(part2) && IPpart(part3) && IPpart(part4))
							{
								//������ϵ�ipֵ
								printf("%d.%d.%d.%d\n", part1, part2, part3, part4);
							}
						}
					}
				}
				if (j == 2)//point2 2λ��
				{
					for (int m = 1; m <= 3; m++)
					{
						//point3 3�ֿ���
						//��ʱpoint4���ݳ��ȿ����ж�
						//0< len - (i+j+m) < 3,����ip���Ϸ� 
						if ((len - (i + j + m)) <= 3 && (len - (i + j + m)) > 0)
						{
							//��ǰһ�α��������0
							point3[0] = 0;
							point3[1] = 0;
							point3[2] = 0;
							point4[0] = 0;
							point4[1] = 0;
							point4[2] = 0;
							getIPpart(IP, point3, i+j, m);
							getIPpart(IP, point4, i+j+m, (len - (i + j + m)));
							//�жϸ���������0-255֮��
							int part1 = calcIPpart(point1[0], point1[1], point1[2]);
							int part2 = calcIPpart(point2[0], point2[1], point2[2]);
							int part3 = calcIPpart(point3[0], point3[1], point3[2]);
							int part4 = calcIPpart(point4[0], point4[1], point4[2]);
							if (IPpart(part1) && IPpart(part2) && IPpart(part3) && IPpart(part4))
							{
								//������ϵ�ipֵ
								printf("%d.%d.%d.%d\n", part1, part2, part3, part4);
							}
						}
					}
				}
				if (j == 3)//point2 3λ��
				{
					for (int m = 1; m <= 3; m++)
					{
						//point3 3�ֿ���
						//��ʱpoint4���ݳ��ȿ����ж�
						//0< len - (i+j+m) < 3,����ip���Ϸ� 
						if ((len - (i + j + m)) <= 3 && (len - (i + j + m)) > 0)
						{
							//��ǰһ�α��������0
							point3[0] = 0;
							point3[1] = 0;
							point3[2] = 0;
							point4[0] = 0;
							point4[1] = 0;
							point4[2] = 0;
							getIPpart(IP, point3, i+j, m);
							getIPpart(IP, point4, i+j+m, (len - (i + j + m)));
							//�жϸ���������0-255֮��
							int part1 = calcIPpart(point1[0], point1[1], point1[2]);
							int part2 = calcIPpart(point2[0], point2[1], point2[2]);
							int part3 = calcIPpart(point3[0], point3[1], point3[2]);
							int part4 = calcIPpart(point4[0], point4[1], point4[2]);
							if (IPpart(part1) && IPpart(part2) && IPpart(part3) && IPpart(part4))
							{
								//������ϵ�ipֵ
								printf("%d.%d.%d.%d\n", part1, part2, part3, part4);
							}
						}
					}
				}
			}
		}
		if (i == 3)
		{
			//�ڶ�����
			for (int j = 1; j <= 3; j++)
			{
				//point2 3�ֿ���
				point2[0] = 0;
				point2[1] = 0;
				point2[2] = 0;
				getIPpart(IP, point2, i, j);
				if (j == 1)//point2 1λ��
				{
					for (int m = 1; m <= 3; m++)
					{
						//point3 ����ip�����ж�
						//��ʱpoint4���ݳ��ȿ����ж�
						//0< len - (i+j+m) < 3,����ip���Ϸ� 
						if ((len - (i + j + m)) <= 3 && (len - (i + j + m)) > 0)
						{
							//��ǰһ�α��������0
							point3[0] = 0;
							point3[1] = 0;
							point3[2] = 0;
							point4[0] = 0;
							point4[1] = 0;
							point4[2] = 0;
							getIPpart(IP, point3, i + j, m);
							getIPpart(IP, point4, i + j + m, (len - (i + j + m)));
							//�жϸ���������0-255֮��
							int part1 = calcIPpart(point1[0], point1[1], point1[2]);
							int part2 = calcIPpart(point2[0], point2[1], point2[2]);
							int part3 = calcIPpart(point3[0], point3[1], point3[2]);
							int part4 = calcIPpart(point4[0], point4[1], point4[2]);
							if (IPpart(part1) && IPpart(part2) && IPpart(part3) && IPpart(part4))
							{
								//������ϵ�ipֵ
								printf("%d.%d.%d.%d\n", part1, part2, part3, part4);
							}
						}
					}
				}
				if (j == 2)//point2 2λ��
				{
					for (int m = 1; m <= 3; m++)
					{
						//point3 3�ֿ���
						//��ʱpoint4���ݳ��ȿ����ж�
						//0< len - (i+j+m) < 3,����ip���Ϸ� 
						if ((len - (i + j + m)) <= 3 && (len - (i + j + m)) > 0)
						{
							//��ǰһ�α��������0
							point3[0] = 0;
							point3[1] = 0;
							point3[2] = 0;
							point4[0] = 0;
							point4[1] = 0;
							point4[2] = 0;
							getIPpart(IP, point3, i+j, m);
							getIPpart(IP, point4, i+j+m, (len - (i + j + m)));
							//�жϸ���������0-255֮��
							int part1 = calcIPpart(point1[0], point1[1], point1[2]);
							int part2 = calcIPpart(point2[0], point2[1], point2[2]);
							int part3 = calcIPpart(point3[0], point3[1], point3[2]);
							int part4 = calcIPpart(point4[0], point4[1], point4[2]);
							if (IPpart(part1) && IPpart(part2) && IPpart(part3) && IPpart(part4))
							{
								//������ϵ�ipֵ
								printf("%d.%d.%d.%d\n", part1, part2, part3, part4);
							}
						}
					}
				}
				if (j == 3)//point2 3λ��
				{
					for (int m = 1; m <= 3; m++)
					{
						//point3 3�ֿ���
						//��ʱpoint4���ݳ��ȿ����ж�
						//0< len - (i+j+m) < 3,����ip���Ϸ� 
						if ((len - (i + j + m)) <= 3 && (len - (i + j + m)) > 0)
						{
							//��ǰһ�α��������0
							point3[0] = 0;
							point3[1] = 0;
							point3[2] = 0;
							point4[0] = 0;
							point4[1] = 0;
							point4[2] = 0;
							getIPpart(IP, point3, i+j, m);
							getIPpart(IP, point4, i+j+m, (len - (i + j + m)));
							//�жϸ���������0-255֮��
							int part1 = calcIPpart(point1[0], point1[1], point1[2]);
							int part2 = calcIPpart(point2[0], point2[1], point2[2]);
							int part3 = calcIPpart(point3[0], point3[1], point3[2]);
							int part4 = calcIPpart(point4[0], point4[1], point4[2]);
							if (IPpart(part1) && IPpart(part2) && IPpart(part3) && IPpart(part4))
							{
								//������ϵ�ipֵ
								printf("%d.%d.%d.%d\n", part1, part2, part3, part4);
							}
						}
					}
				}
			}
		}
	}
	
}
int _tmain(int argc, _TCHAR* argv[])
{
	printf("****test1****\n");
	char ip[] = { "11022345" };
	FindIP(ip);
	printf("****test2****\n");
	char ip2[] = { "19216811" };
	FindIP(ip2);
	return 0;
}
////
/*
void FindIP2(char *IP)
{
	char *point1, *point2, *point3;
	point1 = IP;
	char part1[3] = { 0 };
	char part2[3] = { 0 };
	char part3[3] = { 0 };
	char part4[3] = { 0 };
	int len = 0;
	while (*IP != '\0')
	{
		len++;
		IP++;
	}
	IP = point1;
	for (int i = 0; i < 3; i++)
	{
		switch (i + 1)
		{
		case 1://1-1λ//x.
			for (int j = 0; j < 3; j++)
			{
				switch (j + 1)
				{
				case 1://2-1λ//x.x.
					for (int m = 0; m < 3; m++)
					{
						switch (m + 1)
						{
						case 1://3-1λ//x.x.x.
							for (int n = 0; n < 3; n++)
							{
								part4[n] = *point3++;
								switch (n + 1)
								{
								case 1://4-1λ x.x.x.x
									if (len == 4)
									{
										//�ж�0-255

									}
									break;
								case 2://x.x.x.xx
									if (len == 5)
									{
										//�ж�0-255

									}
									break;
								case 3://x.x.x.xxx
									if (len == 6)
									{
										//�ж�0-255

									}
									break;
								}
							}
							break;
						case 2://x.x.xx.

							break;
						case 3://x.x.xxx.

							break;
						}
					}
					break;
				case 2://x.xx.
					
					break;
				case 3://x.xxx.
					break;
				}
			}
			break;
		case 2://xx.
			break;
		case 3://xxx.
			break;
		}
	}
	

}
*/

/*
void FindIP(char *IP)
{
char *point1, *point2, *point3;
point1 = IP;
char part1[3] = {0};
char part2[3] = { 0 };
char part3[3] = { 0 };
char part4[3] = { 0 };
for (int i = 0; i < 3; i++)
{
part1[i] = *point1;
point1++;
point2 = point1;//�ڶ���ָ��ָ���һ��ָ���ĩβ
for (int j = 0; j < 3; j++)
{
part2[j] = *point2;
point2++;
point3 = point2;//������ָ��ָ��ڶ���ָ���ĩβ
for (int m = 0; m < 3; m++)
{
if (*point3 != '\0')
{
part3[m] = *point3++;//���������ָ�������
}
else
{
break;
}
for (int n = 0; n < 3; n++)
{
part4[n] = *point3++;//�����4��������
if (*point3 == '\0')
{
//��4����1λ������
break;
}
}
if (*point3 != '\0')//�ж��Ƿ��Ѿ����ַ�����������
{
printf("ip���Ϸ�!");
point3 = point2;
point3 = point3 + m + 1;
continue;
}
// 1.1.022.345����ʼ�ж�IP�Ϸ���
if (i == 0)//��һ����ֻ��1λ
{
if (a2i(part1[0]) <= 2
&& a2i(part1[0]) >= 0)
{
if (j == 0)//�ڶ�����ֻ��1λ
{
if (a2i(part2[0]) <= 2
&& a2i(part2[0]) >= 0)
{
if (m == 0)//��������ֻ��1λ
{

}
else if (m == 1)//����������2λ
{

}
else//����������3λ
{
if (a2i(part3[0]) * 100 + a2i(part3[1]) * 10 + a2i(part3[2]) <= 255
&& a2i(part3[0]) * 100 + a2i(part3[1]) * 10 + a2i(part3[2]) >= 0)
{
if (a2i(part4[0]) * 100 + a2i(part4[1]) * 10 + a2i(part4[2]) <= 255
&& a2i(part4[0]) * 100 + a2i(part4[1]) * 10 + a2i(part4[2]) >= 0)
{
//4�����ֶ�����0-255
printf("%d.%d.%d.%d\n",
a2i(part1[0]),
a2i(part1[0]),
a2i(part1[0]) * 100 + a2i(part1[1]) * 10 + a2i(part1[2]),
a2i(part1[0]) * 100 + a2i(part1[1]) * 10 + a2i(part1[2]));
}
else
{
printf(" > 255\n");
}
}
}

}
}
else if (j == 1)//�ڶ�������2λ
{

}
else//�ڶ�������3λ
{

}
}
}
else if (i == 1)//��һ������2λ
{
}
else //��һ������3λ
{

}

}
part3[3] = {0};
point2 = point1;
point2 = point2 + j + 1;
}
//

}



/*point1 = point2 = point3 = IP;
char ip[16] = {0};
int i1 = 3;
int i2 = 3;
int i3 = 3;
while (point1 != '\0' && i1 > 0)
{
while (point2 != '\0' && i2 > 0)
{
point1++;
point2 = point1;

while (point3 != '\0' && i3 > 0)
{
point2++;
point3 = point2;
point3++;

i3++;

}
point2++;
i2++;
}
point1++;
i1++;
}*/






