// TracertCmd.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <WinSock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter)
{
	//���ղ���IP
	ULONG ipSend = (ULONG)lpParameter;
	//����mac��ַ
	UCHAR ucMac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	ULONG ulSize = 6;
	in_addr ip;
	ip.S_un.S_addr = ipSend;
	//����ARP���ݰ�
	int nRet = SendARP(ipSend, 0, ucMac, &ulSize);
	if (NO_ERROR == nRet)
	{
		printf("���ִ��������%s\n", inet_ntoa(ip));
	}
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsd = {};
	WSAStartup(MAKEWORD(2, 2), &wsd);
	//���汾��
	if (LOBYTE(wsd.wVersion != 2) &&
		HIBYTE(wsd.wVersion != 2))
	{
		printf("��ʼ��ʧ��!");
		return 0;
	}

	//����Ҫip��ַ�ṹ
	//IPAddr ipSend;
	in_addr ipStart, ipEnd;
	//��ʼIP
	ipStart.S_un.S_addr = inet_addr("192.168.1.2");
	//����IP
	ipEnd.S_un.S_addr = inet_addr("192.168.1.254");
	for (in_addr i = ipStart; i.S_un.S_addr != ipEnd.S_un.S_addr; ++i.S_un.S_un_b.s_b4)
	{
		//���ö��߳̽���ɨ��
		CreateThread(NULL, NULL, ThreadProc, (LPVOID)i.S_un.S_addr, 0, 0);
	}
	system("pause");
	return 0;
}

