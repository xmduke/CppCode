#pragma once
#include "CMsgInfo.h"
#include "SevConn.h"
class CSevConn;
class CSevCMD
{
public:
	CSevCMD();
	~CSevCMD();
public:
	//������յ���CMD����
	bool recvCMDCommand(CSevConn csc, MYMESSAGE mymsg);
	//����CMD����
	char* dealWithCmd(string strCmd);
	//��ȡ�ļ�
	char* ReadFile(int &nSize);
	//����CMD����ִ����֮��Ľ��
	bool sendCMDShellToClient(SOCKET m_socket, MessageType type, char *argContext, int nCountextSize);

public:
	
};

