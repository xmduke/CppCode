// PingCmd.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//ipͷ��
typedef struct IPHeader
{
	u_char vilen;			//�汾+����
	u_char ser;				//��������
	u_char totalLen;		//�ܳ���
	u_short id;				//��ʾ��
	u_short flag;			//���+Ƭƫ��
	u_char ttl;				//ttl
	u_char protocol;	    //Э��
	u_short checkSum;	    //У���
	in_addr srcIP;			//ԴIP
	in_addr dstIP;			//ԴIP
}IPHEADER;

//icmpͷ��
typedef struct ICMPHeader
{
	u_char type;		//����
	u_char code;		//����
	u_short checkSum;	//У���
	u_short id;			//��ʾ
	u_short seq;		//���к�
	ULONG timestamp;	//���ڼ���ʱ��
}ICMPHEADER;

//��У���,�̶��㷨
u_short checkSumFun(u_short *buffer, int len)
{
	register int nLeft = len;
	register u_short *w = buffer;
	register u_short answer;
	register int sum = 0;
	//ʹ��32λ�ۼ���������16λ��������
	while (nLeft > 1)
	{
		sum += *w++;
		nLeft -= 2;
	}
	//��ȫ����λ
	if (nLeft == 1)
	{
		u_short u = 0;
		*(u_char *)(&u) = *(u_char *)w;
		sum += u;
	}
	//��������16λ�Ӹ�λ������λ
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}

//����ICMP����
void SendICMP(SOCKET sk, in_addr ip)
{
	static DWORD dwId = 0;
	static DWORD dwSeq = 1;
	//udp����ֱ����Է�����
	//����ICMP������
	ICMPHEADER icSend = {};
	icSend.type = 8;
	icSend.code = 0;
	icSend.id = dwId++;
	icSend.seq = dwSeq++;
	icSend.timestamp = GetTickCount();
	icSend.checkSum = checkSumFun((u_short*)&icSend, sizeof(icSend));

	//���ͱ���
	sockaddr_in sAddrSend = {};
	sAddrSend.sin_family = AF_INET;
	sAddrSend.sin_addr = ip;
	int i = sendto(sk, (char*)&icSend, sizeof(icSend), 0, (sockaddr*)&sAddrSend, sizeof(sAddrSend));

}

//����ICMP����
void RecvICMP(SOCKET sk, char *bufRecv, sockaddr_in &sAddrRecv)
{
	int nSize = sizeof(sockaddr_in);
	recvfrom(sk, bufRecv, 1024, 0, (sockaddr*)&sAddrRecv, &nSize);
}

//Ping����
void Ping(char *pSite)
{
	//1.����IP����
	in_addr ip;
	HOSTENT *pRet = gethostbyname(pSite);
	ip.S_un.S_addr = *(u_long*)pRet->h_addr;

	//2.�����׽���
	SOCKET sk = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	for (int i = 0; i < 4; i++)
	{
		//����ICMP����
		SendICMP(sk, ip);
		//����ICMP����
		CHAR bufRecv[1024] = {};
		sockaddr_in sAddrRecv;
		RecvICMP(sk, bufRecv, sAddrRecv);
		//���յ�������
		ICMPHEADER *pIcmpRecv = (ICMPHEADER*)(bufRecv + sizeof(IPHEADER));
		IPHEADER *pIpHeader = (IPHEADER *)bufRecv;
		printf("����%s�Ļظ����ֽ� = %d, time = %dms, ttl = %d\n",
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
	//���汾��
	if (LOBYTE(wsd.wVersion != 2) &&
		HIBYTE(wsd.wVersion != 2))
	{
		printf("��ʼ��ʧ��!");
		return 0;
	}

	Ping("www.baidu.com");
	system("pause");
	return 0;
}

