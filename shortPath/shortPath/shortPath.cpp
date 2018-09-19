// shortPath.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	float data[5][5] = {
		{ 0, 4.47, 3.61, 2.24, 1.41 },
		{ 4.47, 0, 4.12, 2.24, 4.20 },
		{ 3.61, 4.12, 0, 3.16, 2.24 },
		{ 2.24, 2.24, 3.16, 0, 2.24 },
		{ 1.41, 4.20, 2.24, 2.24, 0 }
	};
	int CityA, CityB, CityC, CityD, CityE;
	printf("请输入5个城市的编号（0-4）空格分开");
	scanf("%d %d %d %d %d", &CityA, &CityB, &CityC, &CityD, &CityE);
	float totalS = data[CityA][CityB] + data[CityB][CityC] + data[CityC][CityD] + data[CityD][CityE];
	printf("总距离：", totalS);
	return 0;
}

