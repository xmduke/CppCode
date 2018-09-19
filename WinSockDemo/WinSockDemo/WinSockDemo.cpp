// WinSockDemo.cpp : 定义控制台应用程序的入口点。
//Server

//1.包含头文件及库
//2.初始化环境
//3.绑定
//4.监听
//5.接收
//6.收发消息

#include "stdafx.h"
#include <WinSock2.h>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

//数据解密
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
	//1.初始化环境
	WSADATA wsd = {};
	if (WSAStartup(MAKEWORD(2, 2), &wsd))
	{
		printf("初始化环境失败!");
		return 0;
	}
	//判断版本号
	if (!(LOBYTE(wsd.wVersion) == 2 &&
		HIBYTE(wsd.wVersion) == 2))
	{
		printf("版本号不匹配!");
		WSACleanup();
		return 0;
	}
	//2.创建套接字
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockServer == INVALID_SOCKET)
	{
		printf("创建套接字失败!");
		WSACleanup();
		return 0;
	}
	//3.绑定地址端口号
	SOCKADDR_IN addrServer = {};
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.245");// 192.168.43.110
	addrServer.sin_port = htons(1234);
	int nRet = bind(sockServer, (sockaddr*)&addrServer, sizeof(SOCKADDR_IN));
	if (nRet == SOCKET_ERROR)
	{
		printf("绑定失败!");
		closesocket(sockServer);
		WSACleanup();
		return 0;
	}
	//4.监听
	nRet = listen(sockServer, 5);
	if (nRet == SOCKET_ERROR)
	{
		printf("监听失败!");
		closesocket(sockServer);
		WSACleanup();
		return 0;
	}
	//5.接收连接
	SOCKADDR_IN addrClient = {};
	int nSize = sizeof(SOCKADDR_IN);
	SOCKET sockClient = accept(sockServer, (sockaddr*)&addrClient, &nSize);
	if (nRet == SOCKET_ERROR)
	{
		printf("连接失败!");
		closesocket(sockServer);
		WSACleanup();
		return 0;
	}
	//6.收消息
	nRet = send(sockClient, "Server:link success!", strlen("Server:link success!"), 0);
	if (nRet == SOCKET_ERROR)
	{
		closesocket(sockClient);
		closesocket(sockServer);
		WSACleanup();
		return 0;
	}
	//收消息
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

	//接收由客户端发送的图片

	//创建文件
	CHAR szName[10] = {};
	sprintf_s(szName, "2.jpg");
	ofstream outFile(szName, ios_base::binary);
	//保存接收到的图片
	while (true)
	{
		char bufRecv[1024] = {};
		nRet = recv(sockClient, bufRecv, 1024, 0);
		//解密
		char *pData = XorData(bufRecv, nRet);
		if (nRet == SOCKET_ERROR)
		{
			break;
		}
		else if (nRet < 1024 && nRet>0)
		{
			//最后的数据
			outFile.write(pData, nRet);
			outFile.close();
			break;
			//continue;
		}
		else if (nRet == 1024)
		{
			//正常读取
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

