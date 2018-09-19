// PingCmd.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//ip头部
typedef struct IPHeader
{
	u_char vilen;			//版本+长度
	u_char ser;				//服务类型
	u_char totalLen;		//总长度
	u_short id;				//表示符
	u_short flag;			//标记+片偏移
	u_char ttl;				//ttl
	u_char protocol;	    //协议
	u_short checkSum;	    //校验和
	in_addr srcIP;			//源IP
	in_addr dstIP;			//源IP
}IPHEADER;

//icmp头部
typedef struct ICMPHeader
{
	u_char type;		//类型
	u_char code;		//代码
	u_short checkSum;	//校验和
	u_short id;			//标示
	u_short seq;		//序列号
	ULONG timestamp;	//用于计算时间
}ICMPHEADER;

//求校验和,固定算法
u_short checkSumFun(u_short *buffer, int len)
{
	register int nLeft = len;
	register u_short *w = buffer;
	register u_short answer;
	register int sum = 0;
	//使用32位累加器，进行16位反馈计算
	while (nLeft > 1)
	{
		sum += *w++;
		nLeft -= 2;
	}
	//补全奇数位
	if (nLeft == 1)
	{
		u_short u = 0;
		*(u_char *)(&u) = *(u_char *)w;
		sum += u;
	}
	//将反馈的16位从高位移至低位
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}

//发送ICMP报文
void SendICMP(SOCKET sk, in_addr ip)
{
	static DWORD dwId = 0;
	static DWORD dwSeq = 1;
	//udp可以直接向对方发送
	//构造ICMP请求报文
	ICMPHEADER icSend = {};
	icSend.type = 8;
	icSend.code = 0;
	icSend.id = dwId++;
	icSend.seq = dwSeq++;
	icSend.timestamp = GetTickCount();
	icSend.checkSum = checkSumFun((u_short*)&icSend, sizeof(icSend));

	//发送报文
	sockaddr_in sAddrSend = {};
	sAddrSend.sin_family = AF_INET;
	sAddrSend.sin_addr = ip;
	int i = sendto(sk, (char*)&icSend, sizeof(icSend), 0, (sockaddr*)&sAddrSend, sizeof(sAddrSend));

}

//接收ICMP报文
void RecvICMP(SOCKET sk, char *bufRecv, sockaddr_in &sAddrRecv)
{
	int nSize = sizeof(sockaddr_in);
	recvfrom(sk, bufRecv, 1024, 0, (sockaddr*)&sAddrRecv, &nSize);
}

//Ping命令
void Ping(char *pSite)
{
	//1.创建IP命令
	in_addr ip;
	HOSTENT *pRet = gethostbyname(pSite);
	ip.S_un.S_addr = *(u_long*)pRet->h_addr;

	//2.创建套接字
	SOCKET sk = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	for (int i = 0; i < 4; i++)
	{
		//发送ICMP报文
		SendICMP(sk, ip);
		//接收ICMP报文
		CHAR bufRecv[1024] = {};
		sockaddr_in sAddrRecv;
		RecvICMP(sk, bufRecv, sAddrRecv);
		//接收到的数据
		ICMPHEADER *pIcmpRecv = (ICMPHEADER*)(bufRecv + sizeof(IPHEADER));
		IPHEADER *pIpHeader = (IPHEADER *)bufRecv;
		printf("来自%s的回复：字节 = %d, time = %dms, ttl = %d\n",
			inet_ntoa(sAddrRecv.sin_addr),
			sizeof(ICMPHEADER),
			GetTickCount() - pIcmpRecv->timestamp,
			pIpHeader->ttl);
	}
	closesocket(sk);
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

	Ping("www.baidu.com");
	system("pause");
	return 0;
}

