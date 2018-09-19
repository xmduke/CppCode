// TracertCmd.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter)
{
	//接收参数IP
	ULONG ipSend = (ULONG)lpParameter;
	//构建mac地址
	UCHAR ucMac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	ULONG ulSize = 6;
	in_addr ip;
	ip.S_un.S_addr = ipSend;
	//发送ARP数据包
	int nRet = SendARP(ipSend, 0, ucMac, &ulSize);
	if (NO_ERROR == nRet)
	{
		printf("发现存活主机：%s\n", inet_ntoa(ip));
	}
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsd = {};
	WSAStartup(MAKEWORD(2, 2), &wsd);
	//检查版本号
	if (LOBYTE(wsd.wVersion != 2) &&
		HIBYTE(wsd.wVersion != 2))
	{
		printf("初始化失败!");
		return 0;
	}

	//定义要ip地址结构
	//IPAddr ipSend;
	in_addr ipStart, ipEnd;
	//开始IP
	ipStart.S_un.S_addr = inet_addr("192.168.1.2");
	//结束IP
	ipEnd.S_un.S_addr = inet_addr("192.168.1.254");
	for (in_addr i = ipStart; i.S_un.S_addr != ipEnd.S_un.S_addr; ++i.S_un.S_un_b.s_b4)
	{
		//采用多线程进行扫描
		CreateThread(NULL, NULL, ThreadProc, (LPVOID)i.S_un.S_addr, 0, 0);
	}
	system("pause");
	return 0;
}

