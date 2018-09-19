// WinSockDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//Server

//1.����ͷ�ļ�����
//2.��ʼ������
//3.��
//4.����
//5.����
//6.�շ���Ϣ

#include "stdafx.h"
#include <WinSock2.h>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

//���ݽ���
char *XorData(char *pData, int nSize)
{
	for (int i = 0; i < nSize; i++)
	{
		pData[i] = pData[i] ^ 0x97;
	}
	return pData;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//1.��ʼ������
	WSADATA wsd = {};
	if (WSAStartup(MAKEWORD(2, 2), &wsd))
	{
		printf("��ʼ������ʧ��!");
		return 0;
	}
	//�жϰ汾��
	if (!(LOBYTE(wsd.wVersion) == 2 &&
		HIBYTE(wsd.wVersion) == 2))
	{
		printf("�汾�Ų�ƥ��!");
		WSACleanup();
		return 0;
	}
	//2.�����׽���
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockServer == INVALID_SOCKET)
	{
		printf("�����׽���ʧ��!");
		WSACleanup();
		return 0;
	}
	//3.�󶨵�ַ�˿ں�
	SOCKADDR_IN addrServer = {};
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.245");// 192.168.43.110
	addrServer.sin_port = htons(1234);
	int nRet = bind(sockServer, (sockaddr*)&addrServer, sizeof(SOCKADDR_IN));
	if (nRet == SOCKET_ERROR)
	{
		printf("��ʧ��!");
		closesocket(sockServer);
		WSACleanup();
		return 0;
	}
	//4.����
	nRet = listen(sockServer, 5);
	if (nRet == SOCKET_ERROR)
	{
		printf("����ʧ��!");
		closesocket(sockServer);
		WSACleanup();
		return 0;
	}
	//5.��������
	SOCKADDR_IN addrClient = {};
	int nSize = sizeof(SOCKADDR_IN);
	SOCKET sockClient = accept(sockServer, (sockaddr*)&addrClient, &nSize);
	if (nRet == SOCKET_ERROR)
	{
		printf("����ʧ��!");
		closesocket(sockServer);
		WSACleanup();
		return 0;
	}
	//6.����Ϣ
	nRet = send(sockClient, "Server:link success!", strlen("Server:link success!"), 0);
	if (nRet == SOCKET_ERROR)
	{
		closesocket(sockClient);
		closesocket(sockServer);
		WSACleanup();
		return 0;
	}
	//����Ϣ
	CHAR recvBuf[1024] = {};
	nRet = recv(sockClient, recvBuf, 1024, 0);
	if (nRet == SOCKET_ERROR)
	{
		closesocket(sockClient);
		closesocket(sockServer);
		WSACleanup();
		return 0;
	}
	printf("%s", recvBuf);

	//�����ɿͻ��˷��͵�ͼƬ

	//�����ļ�
	CHAR szName[10] = {};
	sprintf_s(szName, "2.jpg");
	ofstream outFile(szName, ios_base::binary);
	//������յ���ͼƬ
	while (true)
	{
		char bufRecv[1024] = {};
		nRet = recv(sockClient, bufRecv, 1024, 0);
		//����
		char *pData = XorData(bufRecv, nRet);
		if (nRet == SOCKET_ERROR)
		{
			break;
		}
		else if (nRet < 1024 && nRet>0)
		{
			//��������
			outFile.write(pData, nRet);
			outFile.close();
			break;
			//continue;
		}
		else if (nRet == 1024)
		{
			//������ȡ
			outFile.write(pData, nRet);
			//Sleep(100);
			//outFile.flush();
		}
	}

	closesocket(sockClient);
	closesocket(sockServer);
	WSACleanup();
	system("pause");
	return 0;
}

