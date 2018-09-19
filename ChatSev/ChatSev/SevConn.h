#pragma once
#include <winsock2.h>
#include <vector>

#include "SevOP.h"
#include "SevCMD.h"
#include "SevDatabase.h"
#pragma comment(lib, "ws2_32.lib")
using namespace std;
/************************************************************************/
/*��������ʼ��,������ȴ�����״̬
1.��ʼ�����绷�������ݿ�����
2.�����׽���
3.���׽���
4.����
5.�ȴ�����
6.���������̲߳�����������Ϣ

7.�߳̽������˳��߳�
8.�������ر�

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
	//��ʼ���������жϰ汾��
	int SevVersion();
	//�����׽���
	SOCKET SevCreateSock();
	//���׽���
	int SevBindSock(SOCKET sock, char *pIP, unsigned short nPort);
	//����
	int SevListenSock(SOCKET sock);
	//����
	SOCKET SevAcceptSock(SOCKET sockSev);
	//��ʼ��������
	bool init();
	//����������
	bool start(char *pIP, unsigned short nPort);
	//�˳�������
	bool exitSev(SOCKET sock);
	//�̻߳ص�����
	//DWORD WINAPI acceptThread(LPVOID lpParameter);


public:
	//������Ϣ
	WSADATA m_wsd;
	//�������׽���
	SOCKET m_ServerSock;
	//��������ַ
	SOCKADDR_IN m_addrServer;
	//���Կͻ��˵�ַ
	SOCKADDR_IN m_addrClient;
	//���ӳɹ����׽���,��ͻ��˽���������
	SOCKET m_ClientSock;
	//�������Ƿ��ʼ���ɹ�
	bool m_isInit;
	//�������Ƿ������ڹ���
	bool m_isWorking;
	//�����������
	//static vector<CSevOP *> m_vecClient;
	//�߳̾��
	HANDLE m_hAcceptThread;
	//���Ӷ���ָ��
	CSevConn *m_psevConn;

	//���������
	CSevOP *m_sevOP;

	//CMDShell����
	CSevCMD *m_sevCmd;

	//���ݿ����
	CSevDatabase m_sevDatabase;

};

