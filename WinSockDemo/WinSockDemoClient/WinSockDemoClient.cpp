// WinSockDemoClient.cpp : �������̨Ӧ�ó������ڵ㡣
//Client
//0.����ͷ�ļ�����
//1.��ʼ����̻���
//2.�����׽���
//3.����
//4.�շ���Ϣ

#include "stdafx.h"
#include <fstream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

//��ȡͼƬ��������
char* ReadJpgFile(int &nSize)
{
	//���ļ�
	ifstream inFile("1.jpg", ios_base::binary);
	//��ȡ�ļ���С
	inFile.seekg(0, ios::end);
	nSize = (int)inFile.tellg();
	inFile.seekg(0, ios::beg);
	//��ȡ�ļ�
	char* pRead = new char[nSize]{};
	inFile.read(pRead, nSize);
	return pRead;
}

//���ݼ���
char *XorData(char *pData, int &nSize)
{
	for (int i = 0; i < nSize; i++)
	{
		pData[i] = pData[i] ^ 0x97;
	}
	return pData;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//1.��ʼ����̻���
	WSADATA wsd = {};
	if (WSAStartup(MAKEWORD(2, 2), &wsd))
	{
		printf("��ʼ������ʧ��!");
		return 0;
	}
	//�жϰ汾
	if (!(LOBYTE(wsd.wVersion) == 2 &&
		HIBYTE(wsd.wVersion) == 2))
	{
		printf("�汾�ż��ʧ��!");
		WSACleanup();
		return 0;
	}
	//2.�����׽���
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockClient == INVALID_SOCKET)
	{
		printf("�����׽���ʧ��!");
		WSACleanup();
		return 0;
	}
	//3.���ӷ�����
	SOCKADDR_IN addrServer = {};
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.245");// 192.168.43.110
	addrServer.sin_port = htons(1234);
	int nRet = connect(sockClient, (sockaddr*)&addrServer, sizeof(sockaddr));
	if (sockClient == SOCKET_ERROR)
	{
		printf("����ʧ��!");
		closesocket(sockClient);
		WSACleanup();
		return 0;
	}
	//4.����Ϣ
	CHAR recvBuf[1024] = {};
	nRet = recv(sockClient, recvBuf, 1024, 0);
	if (nRet == SOCKET_ERROR)
	{
		closesocket(sockClient);
		WSACleanup();
		return 0;
	}
	printf("%s", recvBuf);
	//����Ϣ
	nRet = send(sockClient, "Client:link success!", strlen("Client:link success!"), 0);
	if (nRet == SOCKET_ERROR)
	{
		closesocket(sockClient);
		WSACleanup();
		return 0;
	}

	//����ͼƬ
	//1.��ȡ�ļ���������
	int nSize = 0;
	char *pRead = ReadJpgFile(nSize);
	//���ݼ���
	char *pData = XorData(pRead, nSize);
	//2.����ͼƬ
	while (true)
	{
		char p[1024] = {};
		memcpy(p, pData, 1024);
		nRet = send(sockClient, p, 1024, 0);
		pData += 1024;
		nSize -= 1024;
		if (nSize < 1024)
		{
			memcpy(p, pData, nSize);
			nRet = send(sockClient, p, nSize, 0);
			printf("����ͼƬ���!");
			delete[] pRead;
			delete[] pData;
			pRead = nullptr;
			pData = nullptr;

			closesocket(sockClient);
			WSACleanup();
			system("pause");
			return 0;
		}
	}
	closesocket(sockClient);
	WSACleanup();
	system("pause");
	return 0;
}

