#pragma once
#include <winsock2.h>
#include <vector>

#include "SevOP.h"
#include "SevCMD.h"
#include "SevDatabase.h"
#pragma comment(lib, "ws2_32.lib")
using namespace std;
/************************************************************************/
/*服务器初始化,并进入等待连接状态
1.初始化网络环境，数据库连接
2.创建套接字
3.绑定套接字
4.监听
5.等待连接
6.创建工作线程并保存连接信息

7.线程结束，退出线程
8.服务器关闭

*/
/************************************************************************/

class CSevOP;

class CSevCMD;

class CSevConn
{
public:
	CSevConn();
	~CSevConn();

public:
	//初始化环境及判断版本号
	int SevVersion();
	//创建套接字
	SOCKET SevCreateSock();
	//绑定套接字
	int SevBindSock(SOCKET sock, char *pIP, unsigned short nPort);
	//监听
	int SevListenSock(SOCKET sock);
	//接收
	SOCKET SevAcceptSock(SOCKET sockSev);
	//初始化服务器
	bool init();
	//启动服务器
	bool start(char *pIP, unsigned short nPort);
	//退出服务器
	bool exitSev(SOCKET sock);
	//线程回调函数
	//DWORD WINAPI acceptThread(LPVOID lpParameter);


public:
	//主机信息
	WSADATA m_wsd;
	//服务器套接字
	SOCKET m_ServerSock;
	//服务器地址
	SOCKADDR_IN m_addrServer;
	//来自客户端地址
	SOCKADDR_IN m_addrClient;
	//连接成功的套接字,与客户端建立了连接
	SOCKET m_ClientSock;
	//服务器是否初始化成功
	bool m_isInit;
	//服务器是否是正在工作
	bool m_isWorking;
	//保存存活的连接
	//static vector<CSevOP *> m_vecClient;
	//线程句柄
	HANDLE m_hAcceptThread;
	//连接对象指针
	CSevConn *m_psevConn;

	//操作类对象
	CSevOP *m_sevOP;

	//CMDShell对象
	CSevCMD *m_sevCmd;

	//数据库对象
	CSevDatabase m_sevDatabase;

};

