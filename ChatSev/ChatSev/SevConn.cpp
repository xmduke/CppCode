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
	//1.��ʼ������
	if (WSAStartup(MAKEWORD(2, 2), &m_wsd))
	{
		printf(">>��ʼ������ʧ��!\n");
		return 0;
	}
	//�жϰ汾��
	if (!(LOBYTE(m_wsd.wVersion) == 2 &&
		HIBYTE(m_wsd.wVersion) == 2))
	{
		printf(">>�汾�Ų�ƥ��!\n");
		WSACleanup();
		return 0;
	}
	return 0;
}

SOCKET CSevConn::SevCreateSock()
{
	//2.�����׽���
	m_ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_ServerSock == INVALID_SOCKET)
	{
		printf(">>�����׽���ʧ��!\n");
		WSACleanup();
		return 0;
	}
	return m_ServerSock;
}

int CSevConn::SevBindSock(SOCKET sock, char *pIP, unsigned short nPort)
{
	//3.�󶨵�ַ�˿ں�
	m_addrServer.sin_family = AF_INET;
	m_addrServer.sin_addr.S_un.S_addr = inet_addr(pIP);// 192.168.43.110
	m_addrServer.sin_port = htons(nPort);
	int nRet = bind(sock, (sockaddr*)&m_addrServer, sizeof(SOCKADDR_IN));
	if (nRet == SOCKET_ERROR)
	{
		printf(">>��ʧ��!\n");
		exitSev(sock);
		return 0;
	}
	else
	{
		printf(">>�����ʼ�����...\n");
	}
	return nRet;
}

int CSevConn::SevListenSock(SOCKET sock)
{
	//4.����
	int nRet = listen(sock, 5);
	if (nRet == SOCKET_ERROR)
	{
		printf(">>����ʧ��!\n");
		exitSev(sock);
		return 0;
	}
	else
	{
		printf(">>���ڼ���...\n");
	}
	return nRet;
}

SOCKET CSevConn::SevAcceptSock(SOCKET sockSev)
{
	//5.��������,���������׽��ֲ�����
	int nSize = sizeof(SOCKADDR_IN);
	printf(">>�ȴ�����...\n");
	m_ClientSock = accept(sockSev, (sockaddr*)&m_addrClient, &nSize);
	if (m_ClientSock == INVALID_SOCKET)
	{
		printf(">>�ͻ�������ʧ��!\n");
		exitSev(m_ClientSock);
		return 0;
	}
	else
	{
		printf(">>��������...\n");
	}
	return m_ClientSock;
}

bool CSevConn::init()
{
	//��ʼ�����汾�ж�
	SevVersion();
	
	//���ݿ�ĳ�ʼ��
	if (m_sevDatabase.LinkDatabase())
	{
		printf(">>���ݿ����ӳɹ�...\n");
	}
	else
	{
		printf(">>���ݿ�����ʧ��...\n");
	}

	return true;
}

//��������Ϣ�����̻߳ص�����
DWORD WINAPI MessageLoop(LPVOID lpParameter)
{
	CSevConn csc = *(CSevConn*)lpParameter;
	CSevOP *pClient = new CSevOP;
	//CSevOP *pClient = (CSevOP*)lpParameter;
	//pClient = csc.m_vecClient.at(0);//���ȡ����̬�����е�Ԫ�أ�
	pClient->m_socket = csc.m_ClientSock;
	//pClient->m_isClose = true;
	while (pClient->m_isClose)
	{
		//��������
		if (pClient->recvMessageFrom(csc) == false)
		{
			pClient->m_isClose = false;
		}
		
	}
	printf(">>�ͻ����˳�!\n");
	return 0;
}

//���������������̻߳ص�����
DWORD WINAPI acceptThread(LPVOID lpParameter)
{
	int i = 0;
	CSevConn csc;
	while (1)
	{
		
		//��������
		if (lpParameter != NULL)
		{
			csc.m_ClientSock = csc.SevAcceptSock((SOCKET)lpParameter);
		}
		if (csc.m_ClientSock == INVALID_SOCKET)
		{
			printf(">>���տͻ�������ʧ��!\n");
			csc.exitSev(csc.m_ClientSock);
		}
		else
		{
			//����һ�����������ӵ�vector
			CSevOP *pclient = new CSevOP;
			pclient->m_socket = csc.m_ClientSock;
			pclient->m_id = i++;
			pclient->m_addr = csc.m_addrClient;
			pclient->m_isClose = true;
			pclient->m_name = "Client:" + i;
			//pclient->m_pContainerPoint = (void *)myThis;
			//��������ɵ��׽��ֱ��浽�������еĶ�̬������
			m_vecClient.push_back(pclient);
			//������ɺ���в���
			if (!(pclient->sendMessageTo(sendLogin, "**��¼�������ɹ���**\n������ע����Ϣ", sizeof("**��¼�������ɹ���**\n������ע����Ϣ"))))
			{
				return 0;
			}
		    //����һ���߳̽�����Ϣ��ѭ���շ�����
			pclient->m_hRecvThread = CreateThread(NULL, NULL, MessageLoop, (LPVOID)&csc, NULL, NULL);
		}
	}
	
	return 0;
}

bool CSevConn::start(char *pIP, unsigned short nPort)
{
	//�����׽���
	m_ServerSock = SevCreateSock();
	//���׽���
	SevBindSock(m_ServerSock, pIP, nPort);
	//����
	SevListenSock(m_ServerSock);
	//�����߳�
	m_hAcceptThread = CreateThread(NULL, NULL, acceptThread, (LPVOID)m_ServerSock, NULL, NULL);
	
	return false;
}

bool CSevConn::exitSev(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
	return true;
}



