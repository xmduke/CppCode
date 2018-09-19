// WinSockDemoClient.cpp : 定义控制台应用程序的入口点。
//Client
//0.包含头文件及库
//1.初始化编程环境
//2.创建套接字
//3.连接
//4.收发消息

#include "stdafx.h"
#include <fstream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

//获取图片到缓冲区
char* ReadJpgFile(int &nSize)
{
	//打开文件
	ifstream inFile("1.jpg", ios_base::binary);
	//获取文件大小
	inFile.seekg(0, ios::end);
	nSize = (int)inFile.tellg();
	inFile.seekg(0, ios::beg);
	//读取文件
	char* pRead = new char[nSize]{};
	inFile.read(pRead, nSize);
	return pRead;
}

//数据加密
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
	//1.初始化编程环境
	WSADATA wsd = {};
	if (WSAStartup(MAKEWORD(2, 2), &wsd))
	{
		printf("初始化环境失败!");
		return 0;
	}
	//判断版本
	if (!(LOBYTE(wsd.wVersion) == 2 &&
		HIBYTE(wsd.wVersion) == 2))
	{
		printf("版本号检测失败!");
		WSACleanup();
		return 0;
	}
	//2.创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockClient == INVALID_SOCKET)
	{
		printf("创建套接字失败!");
		WSACleanup();
		return 0;
	}
	//3.连接服务器
	SOCKADDR_IN addrServer = {};
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.245");// 192.168.43.110
	addrServer.sin_port = htons(1234);
	int nRet = connect(sockClient, (sockaddr*)&addrServer, sizeof(sockaddr));
	if (sockClient == SOCKET_ERROR)
	{
		printf("连接失败!");
		closesocket(sockClient);
		WSACleanup();
		return 0;
	}
	//4.收消息
	CHAR recvBuf[1024] = {};
	nRet = recv(sockClient, recvBuf, 1024, 0);
	if (nRet == SOCKET_ERROR)
	{
		closesocket(sockClient);
		WSACleanup();
		return 0;
	}
	printf("%s", recvBuf);
	//发消息
	nRet = send(sockClient, "Client:link success!", strlen("Client:link success!"), 0);
	if (nRet == SOCKET_ERROR)
	{
		closesocket(sockClient);
		WSACleanup();
		return 0;
	}

	//发送图片
	//1.读取文件到缓冲区
	int nSize = 0;
	char *pRead = ReadJpgFile(nSize);
	//数据加密
	char *pData = XorData(pRead, nSize);
	//2.发送图片
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
			printf("发送图片完成!");
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

