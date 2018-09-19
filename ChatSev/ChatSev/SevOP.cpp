#include "SevOP.h"
#include <fstream>
#include <iostream>
using namespace std;

extern vector<CSevOP *> m_vecClient;
CSevOP::CSevOP()
{

}


CSevOP::~CSevOP()
{
}



bool CSevOP::sendMessageTo(MessageType type, char *argContext, int nCountextSize)
{
	MYMESSAGE mymsg;
	mymsg.messageType = type;
	mymsg.messageSize = nCountextSize;
	ZeroMemory(mymsg.messageContent, 1024);
	memcpy((char *)mymsg.messageContent, (char*)argContext, strlen(argContext));
	int nRet = send(m_socket, (char*)&mymsg, sizeof(MYMESSAGE), 0);
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

bool CSevOP::recvMessageFrom(CSevConn csc)
{
	MYMESSAGE mymsg;
	ZeroMemory(mymsg.messageContent, 1024);
	int nRet = recv(m_socket, (char*)&mymsg, sizeof(MYMESSAGE), 0);
	if (nRet == SOCKET_ERROR)
	{
		sendMessageTo(otherInfo, "��������Ϣ����ʧ�ܣ������·��ͣ�\n", strlen("��������Ϣ����ʧ�ܣ������·��ͣ�\n"));
		return false;
	}
	else if (mymsg.messageType == sendLogout)
	{
		//�ͻ����˳�
		m_isClose = false;
		printf(">>�ͻ�������\n");
		sendMessageTo(sendLogout, "�Ѻͷ������Ͽ�����...", strlen("�Ѻͷ������Ͽ�����..."));
		return false;
		
	}
	else if (mymsg.messageType == sendLogin)
	{
		//�ͻ��˵�¼
		//sendMessageTo(otherInfo, "");
	}
	else if (mymsg.messageType == otherInfo)
	{

		printf(">>%s\n", mymsg.messageContent);
		ofstream examplefile("chat.txt", ios::app);
		if (examplefile.is_open())
		{
			examplefile << ">>" << mymsg.messageContent << endl;
			examplefile.close();
		}
		//���ͻ��˷��ͻ�����Ϣ
		Sleep(100);
		sendMessageTo(otherInfo, mymsg.messageContent, strlen(mymsg.messageContent));
	}
	else if (mymsg.messageType == sendMessageRoom)
	{
		//���Ե�ǰ�̵߳���Ϣ��ת���������ͻ��ˣ�Ⱥ����Ϣ
		//��������ͻ��˵��׽���
		//���͸������ͻ���
		//��Ļ��ʾ�����������¼���ļ���
		for (size_t it = 0; it < m_vecClient.size();/*(csc.m_vecClient.end() - csc.m_vecClient.begin())*/ it++)
		{
			//��ȡ����̬�����б�����׽��ֶ���
			//csc.m_vecClient�����Ǳ����pClient
			//���ѭ��������ÿ�����ӵ�pClient
			//Ȼ����Ϣ���͸���Ӧ�Ŀͻ���
			sendMessageToRoom(
				m_vecClient.at(it)->m_socket,
				sendMessageRoom,
				mymsg.messageContent,
				strlen(mymsg.messageContent));
			//��������ʾ����Ļ
			printf(">>(Ⱥ����Ϣ)�ͻ���%d:%s\n", (m_vecClient.at(it))->m_id, mymsg.messageContent);
			//д���ļ�������������Ϣ
			ofstream examplefile("chat.txt", ios::app);
			if (examplefile.is_open())
			{
				examplefile << ">>" << mymsg.messageContent << endl;
				examplefile.close();
			}
			
		}
		//��Ҫ��ͻ��˷���һ��otherInfo��Ϣʹ�ͻ���������ת����Ϣ�˵���
		sendMessageTo(otherInfo, "", strlen(""));
	}
	else if (mymsg.messageType == sendRegister)
	{
		//��ת�����ݿ���մ�����
		recvDataFromClient(csc, mymsg);
	}

	else if (mymsg.messageType == sendCMDShell)
	{
		//��Ϣ����ΪCMD�������ͣ���ת��CSevCMD�д���,
		(csc.m_sevCmd)->recvCMDCommand(csc, mymsg);
		sendMessageTo(otherInfo, "", strlen(""));
	}

	else if (mymsg.messageType == getUserList)
	{
		//��ѯ�����еĿͻ���

	}


	return true;
}

bool CSevOP::close(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
	return true;
}

//������������Ϣ
bool CSevOP::sendMessageToRoom(SOCKET sock, MessageType type, char *argContext, int nCountextSize)
{
	MYMESSAGE mymsg;
	mymsg.messageType = type;
	mymsg.messageSize = nCountextSize;
	ZeroMemory(mymsg.messageContent, 1024);
	memcpy((char *)mymsg.messageContent, (char*)argContext, strlen(argContext));
	int nRet = send(sock, (char*)&mymsg, sizeof(MYMESSAGE), 0);
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
}

bool CSevOP::sendDataToClient(MessageType type, char *argContext, int nCountextSize)
{
	//�������ݣ���sendMessageTo��ͬ
	return true;
}

bool CSevOP::recvDataFromClient(CSevConn& csc, MYMESSAGE mymsg)
{
	//�������Կͻ��˷������ݿ������
	//���ݿ���������������ؽ��
	//����sqlִ�����
	string uName = mymsg.messageContent;
	//string strSQL = "insert into ChatSev.userinfo(uName)values( uName ); ";
	char strSQL[100] = {};
	sprintf_s(strSQL, 100, "insert into ChatSev.userinfo(uName) values( '%s' );", uName.c_str());
	if (csc.m_sevDatabase.ExeSqlByCommand(strSQL))
	{
		printf(">>�ͻ�����Ϣ����ɹ�!\n");
		//ͨ��sendDataToClient���͸��ͻ���
		sendMessageTo(otherInfo, "ע��ɹ�!\n", strlen("ע��ɹ�!"));
		return true;
	}
	else
	{
		printf(">>�ͻ�����Ϣ����ʧ��!\n");
		//ͨ��sendDataToClient���͸��ͻ���
		sendMessageTo(sendRegister, "ע��ʧ��!", strlen("ע��ʧ��!"));
		return false;
	}
	return true;
}


