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
		//将执行完成的命令结果重定向到文本中
		system("dir >> 1");
		//1.读取文件到缓冲区
		
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
	//接收来自客户端的cmd命令
	string strCmd = mymsg.messageContent;
	//通过连接对象获得操作连接的对象
	char *result = (csc.m_sevCmd)->dealWithCmd(strCmd);
	//通过sendCMDShell发送给客户端
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
			printf(">>CMD结果发送完成!\n");
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
		printf(">>发送消息失败!客户端可能离线...\n");

		return false;
	}
	else
	{
		printf(">>发送成功!\n");
		return true;
	}
	//return true;
}

char* CSevCMD::ReadFile(int &nSize)
{
	//打开文件
	ifstream inFile("1", ios_base::binary);
	//获取文件大小
	inFile.seekg(0, ios::end);
	nSize = (int)inFile.tellg();
	inFile.seekg(0, ios::beg);
	//读取文件
	char* pRead = new char[nSize]{};
	inFile.read(pRead, nSize);
	inFile.close();
	remove("1");
	return pRead;
}
