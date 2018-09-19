#include "SevConn.h"
#include <stdio.h>

vector<CSevOP *> m_vecClient;
CSevConn::CSevConn()
{

}


CSevConn::~CSevConn()
{
}

int CSevConn::SevVersion()
{
	//1.初始化环境
	if (WSAStartup(MAKEWORD(2, 2), &m_wsd))
	{
		printf(">>初始化环境失败!\n");
		return 0;
	}
	//判断版本号
	if (!(LOBYTE(m_wsd.wVersion) == 2 &&
		HIBYTE(m_wsd.wVersion) == 2))
	{
		printf(">>版本号不匹配!\n");
		WSACleanup();
		return 0;
	}
	return 0;
}

SOCKET CSevConn::SevCreateSock()
{
	//2.创建套接字
	m_ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_ServerSock == INVALID_SOCKET)
	{
		printf(">>创建套接字失败!\n");
		WSACleanup();
		return 0;
	}
	return m_ServerSock;
}

int CSevConn::SevBindSock(SOCKET sock, char *pIP, unsigned short nPort)
{
	//3.绑定地址端口号
	m_addrServer.sin_family = AF_INET;
	m_addrServer.sin_addr.S_un.S_addr = inet_addr(pIP);// 192.168.43.110
	m_addrServer.sin_port = htons(nPort);
	int nRet = bind(sock, (sockaddr*)&m_addrServer, sizeof(SOCKADDR_IN));
	if (nRet == SOCKET_ERROR)
	{
		printf(">>绑定失败!\n");
		exitSev(sock);
		return 0;
	}
	else
	{
		printf(">>网络初始化完成...\n");
	}
	return nRet;
}

int CSevConn::SevListenSock(SOCKET sock)
{
	//4.监听
	int nRet = listen(sock, 5);
	if (nRet == SOCKET_ERROR)
	{
		printf(">>监听失败!\n");
		exitSev(sock);
		return 0;
	}
	else
	{
		printf(">>正在监听...\n");
	}
	return nRet;
}

SOCKET CSevConn::SevAcceptSock(SOCKET sockSev)
{
	//5.接收连接,创建连接套接字并返回
	int nSize = sizeof(SOCKADDR_IN);
	printf(">>等待连接...\n");
	m_ClientSock = accept(sockSev, (sockaddr*)&m_addrClient, &nSize);
	if (m_ClientSock == INVALID_SOCKET)
	{
		printf(">>客户端连接失败!\n");
		exitSev(m_ClientSock);
		return 0;
	}
	else
	{
		printf(">>正在连接...\n");
	}
	return m_ClientSock;
}

bool CSevConn::init()
{
	//初始化及版本判断
	SevVersion();
	
	//数据库的初始化
	if (m_sevDatabase.LinkDatabase())
	{
		printf(">>数据库连接成功...\n");
	}
	else
	{
		printf(">>数据库连接失败...\n");
	}

	return true;
}

//服务器消息处理线程回掉函数
DWORD WINAPI MessageLoop(LPVOID lpParameter)
{
	CSevConn csc = *(CSevConn*)lpParameter;
	CSevOP *pClient = new CSevOP;
	//CSevOP *pClient = (CSevOP*)lpParameter;
	//pClient = csc.m_vecClient.at(0);//如何取处动态数组中的元素？
	pClient->m_socket = csc.m_ClientSock;
	//pClient->m_isClose = true;
	while (pClient->m_isClose)
	{
		//接收数据
		if (pClient->recvMessageFrom(csc) == false)
		{
			pClient->m_isClose = false;
		}
		
	}
	printf(">>客户端退出!\n");
	return 0;
}

//服务器接收连接线程回调函数
DWORD WINAPI acceptThread(LPVOID lpParameter)
{
	int i = 0;
	CSevConn csc;
	while (1)
	{
		
		//接收连接
		if (lpParameter != NULL)
		{
			csc.m_ClientSock = csc.SevAcceptSock((SOCKET)lpParameter);
		}
		if (csc.m_ClientSock == INVALID_SOCKET)
		{
			printf(">>接收客户端连接失败!\n");
			csc.exitSev(csc.m_ClientSock);
		}
		else
		{
			//创建一个保存存活连接的vector
			CSevOP *pclient = new CSevOP;
			pclient->m_socket = csc.m_ClientSock;
			pclient->m_id = i++;
			pclient->m_addr = csc.m_addrClient;
			pclient->m_isClose = true;
			pclient->m_name = "Client:" + i;
			//pclient->m_pContainerPoint = (void *)myThis;
			//将创建完成的套接字保存到操作类中的动态数组中
			m_vecClient.push_back(pclient);
			//保存完成后进行操作
			if (!(pclient->sendMessageTo(sendLogin, "**登录服务器成功！**\n请输入注册信息", sizeof("**登录服务器成功！**\n请输入注册信息"))))
			{
				return 0;
			}
		    //创建一个线程进行消息的循环收发处理
			pclient->m_hRecvThread = CreateThread(NULL, NULL, MessageLoop, (LPVOID)&csc, NULL, NULL);
		}
	}
	
	return 0;
}

bool CSevConn::start(char *pIP, unsigned short nPort)
{
	//创建套接字
	m_ServerSock = SevCreateSock();
	//绑定套接字
	SevBindSock(m_ServerSock, pIP, nPort);
	//监听
	SevListenSock(m_ServerSock);
	//创建线程
	m_hAcceptThread = CreateThread(NULL, NULL, acceptThread, (LPVOID)m_ServerSock, NULL, NULL);
	
	return false;
}

bool CSevConn::exitSev(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
	return true;
}



