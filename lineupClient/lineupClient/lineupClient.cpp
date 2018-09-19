// lineupClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Winsock2.h"
#include <string>
#include <memory.h>
#pragma comment(lib, "Ws2_32.lib")
#define CLIENT_SOCKET_DLL_ERROR -1
#define CLIENT_API_ERROR 0
#define MAX_NUM_BUF 256
//端口
#define SERVERPORT 5555
//IP地址
#define SERVERIP "10.11.117.48"

CHAR *bufdata;//缓冲区，接收来自服务端的数据
CHAR* bufRecv = NULL;//
char bufSend[256];
SOCKET sServer;
SOCKET sClient;
BOOL bConning;//一个标志，判断是否连接


/************************************************************************/
/* 功能：初始化全局成员变量
   参数：无
   返回：无
/************************************************************************/
void InitMember()
{
	//memset(bufRecv, 0, sizeof(bufRecv));
	memset(bufSend, 0, sizeof(bufSend));

	sServer = INVALID_SOCKET;
	sClient = INVALID_SOCKET;
	bConning = FALSE;
}

/************************************************************************/
/* 功能：初始化套接字的库，版本判断等
   参数：无
   返回：int 返回错误代码
/************************************************************************/
int InitSocketDll()
{
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(1, 1);
	int err = WSAStartup(wVersionRequested, (LPWSADATA)&wsaData);
	if (0 != err)
	{
		MessageBox(NULL, L"Can not find a windows socket dll!", L"error", MB_OK);
		return CLIENT_SOCKET_DLL_ERROR;
	}
	return err;
}

/************************************************************************/
/* 功能：退出客户端，关闭套接字等
   参数：int 退出值，错误信息宏定义 CLIENT_SOCKET_DLL_ERROR
   返回：退出值
/************************************************************************/
int ExitClient(int nEixt)
{
	closesocket(sServer);
	closesocket(sClient);
	WSACleanup();
	return nEixt;
}

/************************************************************************/
/* 功能：显示错误消息
   参数：无
   返回：无
/************************************************************************/
void ShowErrorMsg()
{
	int nErrCode = WSAGetLastError();
	HLOCAL hlocal = NULL;

	BOOL fOk = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		nErrCode,
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		(PTSTR)&hlocal,
		0,
		NULL);

	if (hlocal != NULL)
	{
		MessageBox(NULL, (LPCWSTR)LocalLock(hlocal), L"CLIENT ERROR", MB_OK);
		LocalFree(hlocal);
	}
}


/************************************************************************/
/* 功能：创建套接字
   参数：无
   返回：SOCKET
/************************************************************************/
SOCKET CreateSocket()
{
	SOCKET sHost;
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		ShowErrorMsg();
		WSACleanup();
		return CLIENT_API_ERROR;
	}
	return sHost;
}

/************************************************************************/
/* 功能：连接服务器
   参数：sHost 创建出来的套接字
   返回：int 创建后返回的值
/************************************************************************/
int ConnectServer(SOCKET sHost)
{
	//LPHOSTENT hostEntry;
	/*char hostname[MAX_NUM_BUF];
	gethostname(hostname, MAX_NUM_BUF);
	hostEntry = gethostbyname(hostname);
	if (!hostEntry)
	{
		ShowErrorMsg();
		return ExitClient(CLIENT_API_ERROR);

	}*/
	SOCKADDR_IN addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_addr.S_un.S_addr = inet_addr(SERVERIP);;//*((LPIN_ADDR)*hostEntry->h_addr_list);
	addrServ.sin_port = htons(SERVERPORT);

	int retVal = connect(sHost, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{
		ShowErrorMsg();
		return ExitClient(CLIENT_API_ERROR);
	}
	else
	{
		bConning = TRUE;
	}
	return retVal;
}

/************************************************************************/
/* 功能：发送消息给服务端
   参数：SOCKET sHost 创建的套接字
        char* bufSend 发送消息的内容
   返回：int 实际发送的字节
/************************************************************************/
int SendMsg(SOCKET sHost, char* bufSend)
{
	//strcpy(bufSend, "Hello, Server!\n");
	int retVal = send(sHost, bufSend, strlen(bufSend), 0);
	if (SOCKET_ERROR == retVal)
	{
		ShowErrorMsg();
		return ExitClient(CLIENT_API_ERROR);
	}
	return retVal;
}

/************************************************************************/
/* 功能：接收服务端消息
   参数：SOCKET sClient,本地套接字
        CHAR *buf,接收数据保存的缓冲区
		int size，一次接收多少字节
   返回：实际接收的字节
/************************************************************************/
int RecvLine(SOCKET sClient, CHAR *buf, int size)
{
	BOOL retVal = TRUE;
	BOOL bLineEnd = FALSE;
	int nReadLen = 0;
	int nDataLen = 0;

	nReadLen = recv(sClient, buf, size, 0);
	int n = GetLastError();
	if (SOCKET_ERROR == nReadLen)
	{
		retVal = FALSE;
		return 0;
	}

	if (0 == nReadLen)
	{
		retVal = FALSE;
		return 0;
	}

	if ('\n' == *(buf + nDataLen))
	{
		bLineEnd = TRUE;
	}
	return nReadLen;
}


int _tmain(int argc, _TCHAR* argv[])
{
	//1.初始化套接字
	printf("[*] 初始化套接字...\n");
	InitMember();

	if (0 == InitSocketDll())
	{
		printf("[*] InitSocket finish!\n");
	}
	else
	{
		ShowErrorMsg();
	};

	//2.创建客户端套接字
	printf("[*] 创建客户端套接字...\n");
	sClient = CreateSocket();
	
	//3.连接服务端
	printf("[*] 连接服务端...\n");
	ConnectServer(sClient);

	//4.发送Start命令
	printf("[*] 发送Start命令...\n");
	strcpy(bufSend, "ps -a");
	SendMsg(sClient, bufSend);

	//5.准备接收服务端发送的ps -a数据
	printf("[*] 接收服务端发送的pa -a数据...\n");

	//6.接收一次数据的长度，数据为ps -a的数据

	//ps -a数据总长度
	CHAR *bufdatalen;
	//创建一个8字节的堆空间存放长度值
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	//清0
	memset(bufdatalen, 0, sizeof(bufdatalen));
	//开始接收长度值
	int bufLenRecv = RecvLine(sClient, bufdatalen, 128);
	//将长度转long
	long bufLen = atoi(bufdatalen);
	//释放缓冲区
	free(bufdatalen);

	//接受之后给服务端发送一个ok指令，表示接收完了
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);
	
	//7.开始接收数据
	//数据的长度
	int bufRecvLen = 0;
	//创建一个256的堆空间保存ps -a的数据
	bufdata = (CHAR *)malloc(256 * sizeof(CHAR));
	//清0
	memset(bufdata, 0, sizeof(bufdata));
	printf("pa -a数据:\n");
	while (bufLen > 0)
	{
		//开始接收
		bufRecvLen = RecvLine(sClient, bufdata + bufRecvLen, 1);
		printf("%s", bufdata +bufRecvLen);
		bufLen--;
	}
	//释放缓冲区
	free(bufdata);

	//8.发送PID值给服务端
	int pid = 0;
	CHAR str_pid[5] = {0};
	printf("输入pid：");
	scanf("%d", &pid);
	memset(bufSend, 0, sizeof(bufSend));
	itoa(pid, str_pid, 10);
	strcpy(bufSend, str_pid);
	SendMsg(sClient, bufSend);

	//9.接收内存布局长度
	printf("[*] 接收内存布局长度...\n");

	//接收长度值
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	//开始接收
	bufLenRecv = RecvLine(sClient, bufdatalen, 128);
	bufLen = atoi(bufdatalen);
	//释放
	free(bufdatalen);
	//接收完后发送ok命令
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	//实际接收到的内存布局数据的长度
	int bufRecvMemLen = 0;
	bufdata = (CHAR *)malloc(256 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	printf("内存布局:\n");
	while (bufLen > 0)
	{
		//开始接收内存布局的数据
		bufRecvMemLen = RecvLine(sClient, bufdata + bufRecvMemLen, 1);
		printf("%s", bufdata + bufRecvMemLen);
		bufLen--;
	}
	free(bufdata);

	//10.发送Sleep命令
	printf("[*] 发送Sleep命令，间隔15秒...\n");
	strcpy(bufSend, "15");
	SendMsg(sClient, bufSend);

	//11.发送段长度
	printf("[*] 发送段长度...\n");
	strcpy(bufSend, "16");
	SendMsg(sClient, bufSend);

	
	// 接收服务端ok信息
	char okbuf[2] = { 0 };
	long ok = RecvLine(sClient, okbuf, 3);

	//这里需要刷新下输入缓冲区，不然下次接收数据会出现\n，数据不对
	fflush(stdin);

	//发送一个32字节长度的字符，0-15表示开始地址，16-31表示长度
	char starAddr[33] = {0};
	printf("输入32字节长度的字符，0-15表示开始地址，16-31表示长度：");
	for (int i = 0; i < 33; i++)
	{
		scanf("%c", &starAddr[i]);
	}
	//发送给服务端
	strcpy(bufSend, starAddr);
	SendMsg(sClient, bufSend);
	//这里也需要再发送一个ok标志
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	printf("[*] 正在接收数据并转储到txt文件...\n");
	//12.第一次接收log文件
	//接收dump_ca.log
	freopen("dump_ca.log", "w", stdout);
	printf("[*] 接收dump_ca.log...\n");
	//先接收一个log文件长度
	int bufRecvdump_caLen = 0;
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	bufLenRecv = RecvLine(sClient, bufdatalen, 8);
	bufLen = atoi(bufdatalen);
	free(bufdatalen);
	//长度接收完发送ok
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);
	
	//开始接收数据
	printf("dump_ca.log:\n");
	bufdata = (CHAR *)malloc(1024 * 1000 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	while (bufLen > 0)
	{
		//接收
		bufRecvdump_caLen = RecvLine(sClient, bufdata + bufRecvdump_caLen, 1);
		printf("%s", bufdata + bufRecvdump_caLen);
		bufLen--;
	}
	//释放
	free(bufdata);

	//13.接收dump_data.log
	freopen("dump_data.log", "w", stdout);
	printf("[*] 接收dump_data.log...\n");
	//先接收长度
	int bufRecvdump_dataLen = 0;
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	bufLenRecv = RecvLine(sClient, bufdatalen, 8);
	bufLen = atoi(bufdatalen);
	free(bufdatalen);
	//发送ok
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	//开始接收log数据
	printf("dump_data.log:\n");
	bufdata = (CHAR *)malloc(1024 * 1000 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	while (bufLen > 0)
	{
		//接收
		bufRecvdump_dataLen = RecvLine(sClient, bufdata + bufRecvdump_dataLen, 1);
		printf("%s", bufdata + bufRecvdump_dataLen);
		bufLen--;
	}
	free(bufdata);
	//发送ok
	//strcpy(bufSend, "ok");
	//SendMsg(sClient, bufSend);

	/////再接收一次，和上面一样
	//14.接收dump_ca2.log
	freopen("dump_ca2.log", "w", stdout);
	printf("[*] 接收dump_ca2.log...\n");
	bufRecvdump_caLen = 0;
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	bufLenRecv = RecvLine(sClient, bufdatalen, 8);
	bufLen = atoi(bufdatalen);
	free(bufdatalen);
	//发送ok
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	//接收数据
	printf("dump_ca2.log:\n");
	bufdata = (CHAR *)malloc(1024 * 1000 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	while (bufLen > 0)
	{
		bufRecvdump_caLen = RecvLine(sClient, bufdata + bufRecvdump_caLen, 1);
		printf("%s", bufdata + bufRecvdump_caLen);

		bufLen--;
	}
	free(bufdata);


	//15.接收dump_data.log
	freopen("dump_data2.log", "w", stdout);
	printf("[*] 接收dump_data2.log...\n");
	bufRecvdump_dataLen = 0;
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	bufLenRecv = RecvLine(sClient, bufdatalen, 8);
	bufLen = atoi(bufdatalen);
	free(bufdatalen);
	//发送ok
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	//接收数据
	printf("dump_data2.log:\n");
	bufdata = (CHAR *)malloc(1024 * 1000 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	while (bufLen > 0)
	{
		bufRecvdump_dataLen = RecvLine(sClient, bufdata + bufRecvdump_dataLen, 1);
		printf("%s", bufdata + bufRecvdump_dataLen);
		bufLen--;
	}
	free(bufdata);
	
	//16.发送Stop命令
	printf("[*] 发送Stop命令...\n");
	strcpy(bufSend, "stop");
	SendMsg(sClient, bufSend);

	//17.关闭套接字
	printf("[*] 退出...\n");

	ExitClient(0);
	return 0;
}

