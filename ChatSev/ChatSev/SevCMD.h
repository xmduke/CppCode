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
	//处理接收到的CMD命令
	bool recvCMDCommand(CSevConn csc, MYMESSAGE mymsg);
	//处理CMD命令
	char* dealWithCmd(string strCmd);
	//读取文件
	char* ReadFile(int &nSize);
	//发送CMD命令执行完之后的结果
	bool sendCMDShellToClient(SOCKET m_socket, MessageType type, char *argContext, int nCountextSize);

public:
	
};

