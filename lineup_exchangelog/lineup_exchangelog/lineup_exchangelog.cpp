// lineup_exchangelog.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include <vector>
//using namespace std;

unsigned char CharToHex(char bchar, char bchar2)
{
	unsigned char btmp = 0;
	//short btmp1 = ((short)bchar << 4);
	//short btmp2 = ((bchar2));
	//btmp = (bchar << 4) | (bchar2);
	//btmp[1] = bchar2;

	//unsigned char bHex = strtoul(btmp, btmp, 16);
	if ((bchar >= '0') && (bchar <= '9'))
	{
		bchar -= 0x30;
		//bchar = bchar << 4
	}
	else if ((bchar >= 'a') && (bchar <= 'f'))//Capital
	{
		bchar -= 0x57;//0x61 - = 0xa
		//bchar = bchar << 4;
	}
	else
	{
		bchar = 0xf;
	}

	if ((bchar2 >= '0') && (bchar2 <= '9'))
	{
		
		bchar2 -= 0x30;
	}
	else if ((bchar2 >= 'a') && (bchar2 <= 'f'))//Capital
	{
		bchar2 -= 0x57;//0x61 - = 0xa
	}
	else
	{
		bchar2 = 0xf;
	}
	bchar = bchar << 4;
	btmp = bchar | bchar2;

	return btmp;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//打开文件
	FILE * fidr = fopen(argv[1], "r");
	if (fidr == NULL)
	{
		printf("打开%s失败\n", argv[1]);
		return 0;
	}
	FILE * fidw = fopen("txt_out.txt", "w");
	if (fidw == NULL)
	{
		printf("写出文件失败！\n");
		return 0;
	}
	while (!feof(fidr))
	{
		char line[64];
		char sublinechar[8][16];
		char *subline;
		for (int i = 0; i < 8; i++)
		{
			fgets(line, 64, fidr);
			printf("%s\n", line); //输出
			subline = strrchr(line, ' ') + 1;
			printf("%s\n", subline);
			for (int j = 0; j < 16; j++)
			{
				sublinechar[i][j] = *subline;
				subline++;
			}
		}
		int n = 0;
		while (true)
		{
			for (int m = 7; m >= 0; m--)
			{
				printf("%c%c ", sublinechar[m][n], sublinechar[m][n + 1]);
				//转为十六进制数
				unsigned char chartmp = CharToHex(sublinechar[m][n], sublinechar[m][n + 1]);
				//chartmp = CharToHex(sublinechar[m][n], sublinechar[m][n + 1]);
				//sublinechar[m][n+1] = CharToHex(sublinechar[m][n+1]);
				//写入文件
				//printf("0x%x ", chartmp);
				fwrite(&chartmp, sizeof(unsigned char), 1, fidw);
				//fwrite(&sublinechar[m][n + 1], sizeof(char), 1, fidw);
			}
			n = n + 2;

			if (n == 16)
			{
				break;
			}
		}
	}
	fclose(fidw);
	fclose(fidr);
	
	//循环读取8行
	/*char line[64];
	char *subline;
	vector <vector<char>>linevector;
	//vector <char>charvector;
	memset(line, 0, 64);
	while (!feof(fid))
	{
		for (int i = 0; i < 8; i++)
		{
			vector <char>charvector;
			fgets(line, 64, fid);
			printf("%s\n", line); //输出
			//查找第二个空格
			subline = strrchr(line, ' ') + 1;
			printf("%s\n", subline);
			//char tmp[16] = { 0 };
			for (int j = 0; j < 16; j++)
			{
				charvector.push_back(subline[j]);
			}
			linevector.push_back(charvector);
			subline++;
		}
		//进行解析
		vector<vector<char>>::iterator it;
		for (it = linevector.begin(); it != linevector.end(); it++)
		{
			printf("%c%c ", linevector.at(i), linevector.at(i + 1));
			//vector<char>::iterator itchar;
			//int i = 0;
			/*for (itchar = charvector.begin(); itchar != charvector.end(); itchar++)
			{
				printf("%c%c ", charvector.at(i), charvector.at(i+1));
				i++;
			}
		}
	}*/
	
	return 0;
}

