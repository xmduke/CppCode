#pragma once
#include "CMsgInfo.h"
#include "SevConn.h"
#include "SevCMD.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <map>
/************************************************************************/
/*�������ľ������
1.��ȡ�Ӵ������׽�������
2.�Ը��߳̽��з�����Ϣ
3.�Ը��߳̽��н�����Ϣ
4.�����ݿ���в���
*/
/************************************************************************/
class CSevConn;
class CSevCMD;
class CSevOP
{
public:
	CSevOP();
	~CSevOP();

public:
	//������Ϣ����
	bool sendMessageTo(MessageType type, char *argContext, int nCountextSize);
	//������Ϣ����
	bool recvMessageFrom(CSevConn csc);
	//�ر��׽���
	bool close(SOCKET sock);
	//�������ҷ�����Ϣ�����������ͻ���ת����Ϣ
	bool sendMessageToRoom(SOCKET sock, MessageType type, char *argContext, int nCountextSize);
	//ͨ���������ݿ�����ݽ��ж�ȡȻ����ͻ��˽���ת��
	bool sendDataToClient(MessageType type, char *argContext, int nCountextSize);
	//�������Կͻ��˵����ݷ�������
	bool recvDataFromClient(CSevConn& csc, MYMESSAGE mymsg);

public:
	//����ָ��
	//���׽����ڷ�������ʱ����ֵΪ����˶���ָ��
	//���׽����ڿͻ���ʱ����ֵΪ�ͻ��˶���ָ��
	void *m_pContainerPoint;

	//ÿ�����ӵĿͻ��˵���Ϣ
	//��ǰ��socket
	SOCKET m_socket;
	//socket��id��ʶ
	int m_id;
	//����
	string m_name;
	//��ַ���˿�
	sockaddr_in m_addr;
	//�Ƿ�رգ��Ͽ�
	bool m_isClose;
	//�߳̾��
	HANDLE m_hRecvThread;

	//�����Ҽ�¼
	vector<string> m_roomMessage;
	//��ͬ����������Ϣ��¼
	map<int, vector<string>> m_friendMessage;
	//���ߺ���
	map<int, string> m_friendNames;

	

public:
	//������Ϣ������
};

