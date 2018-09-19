#pragma once
#include "CMsgInfo.h"
#include "SevConn.h"
#include "SevCMD.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <map>
/************************************************************************/
/*服务器的具体操作
1.获取接创建的套接字连接
2.对该线程进行发送消息
3.对该线程进行接收消息
4.对数据库进行操作
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
	//基础消息发送
	bool sendMessageTo(MessageType type, char *argContext, int nCountextSize);
	//基础消息接收
	bool recvMessageFrom(CSevConn csc);
	//关闭套接字
	bool close(SOCKET sock);
	//向聊天室发送消息，即向其他客户端转发消息
	bool sendMessageToRoom(SOCKET sock, MessageType type, char *argContext, int nCountextSize);
	//通过访问数据库对数据进行读取然后向客户端进行转发
	bool sendDataToClient(MessageType type, char *argContext, int nCountextSize);
	//接收来自客户端的数据访问请求
	bool recvDataFromClient(CSevConn& csc, MYMESSAGE mymsg);

public:
	//容器指针
	//当套接字在服务器中时，赋值为服务端对象指针
	//当套接字在客户端时，赋值为客户端对象指针
	void *m_pContainerPoint;

	//每个连接的客户端的信息
	//当前的socket
	SOCKET m_socket;
	//socket的id标识
	int m_id;
	//名字
	string m_name;
	//地址，端口
	sockaddr_in m_addr;
	//是否关闭，断开
	bool m_isClose;
	//线程句柄
	HANDLE m_hRecvThread;

	//聊天室记录
	vector<string> m_roomMessage;
	//不同好友聊天消息记录
	map<int, vector<string>> m_friendMessage;
	//在线好友
	map<int, string> m_friendNames;

	

public:
	//复杂消息处理函数
};

