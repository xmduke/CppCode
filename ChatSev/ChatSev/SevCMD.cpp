#include "SevCMD.h"
#include <iostream>
#include <fstream>


CSevCMD::CSevCMD()
{
	
}


CSevCMD::~CSevCMD()
{

}

int nSize = 0;

char * CSevCMD::dealWithCmd(string strCmd)
{
	if (strCmd == "dir")
	{
		//��ִ����ɵ��������ض����ı���
		system("dir >> 1");
		//1.��ȡ�ļ���������
		
		char *pRead = ReadFile(nSize);
		return pRead;
	}
	else
	{
		return NULL;
	}
	return NULL;
}

bool CSevCMD::recvCMDCommand(CSevConn csc, MYMESSAGE mymsg)
{
	//�������Կͻ��˵�cmd����
	string strCmd = mymsg.messageContent;
	//ͨ�����Ӷ����ò������ӵĶ���
	char *result = (csc.m_sevCmd)->dealWithCmd(strCmd);
	//ͨ��sendCMDShell���͸��ͻ���
	while (true)
	{
		char p[1024] = {};
		memcpy(p, result, 1024);
		sendCMDShellToClient(csc.m_ClientSock, sendCMDShell, p, 1024);
		result += 1024;
		nSize -= 1024;
		if (nSize < 1024)
		{
			memcpy(p, result, nSize);
			sendCMDShellToClient(csc.m_ClientSock, sendCMDShell, p, nSize);
			printf(">>CMD����������!\n");
			//delete[] result;
			//result = nullptr;
			return true;
		}
	}
	return false;
	
}

bool CSevCMD::sendCMDShellToClient(SOCKET m_socket, MessageType type, char *argContext, int nCountextSize)
{
	int a = sizeof(int);
	int v = sizeof(MYMESSAGE);
	MYMESSAGE mymsg;
	mymsg.messageType = type;
	mymsg.messageSize = nCountextSize;
	ZeroMemory(mymsg.messageContent, 1024);
	memcpy((char *)mymsg.messageContent, (char*)argContext, strlen(argContext));
	int nRet = send(m_socket, (char*)&mymsg, sizeof(mymsg), 0);
	if (nRet == SOCKET_ERROR)
	{
		printf(">>������Ϣʧ��!�ͻ��˿�������...\n");

		return false;
	}
	else
	{
		printf(">>���ͳɹ�!\n");
		return true;
	}
	//return true;
}

char* CSevCMD::ReadFile(int &nSize)
{
	//���ļ�
	ifstream inFile("1", ios_base::binary);
	//��ȡ�ļ���С
	inFile.seekg(0, ios::end);
	nSize = (int)inFile.tellg();
	inFile.seekg(0, ios::beg);
	//��ȡ�ļ�
	char* pRead = new char[nSize]{};
	inFile.read(pRead, nSize);
	inFile.close();
	remove("1");
	return pRead;
}
