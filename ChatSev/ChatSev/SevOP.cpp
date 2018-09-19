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

bool CSevOP::recvMessageFrom(CSevConn csc)
{
	MYMESSAGE mymsg;
	ZeroMemory(mymsg.messageContent, 1024);
	int nRet = recv(m_socket, (char*)&mymsg, sizeof(MYMESSAGE), 0);
	if (nRet == SOCKET_ERROR)
	{
		sendMessageTo(otherInfo, "服务器消息接收失败，请重新发送！\n", strlen("服务器消息接收失败，请重新发送！\n"));
		return false;
	}
	else if (mymsg.messageType == sendLogout)
	{
		//客户端退出
		m_isClose = false;
		printf(">>客户端下线\n");
		sendMessageTo(sendLogout, "已和服务器断开连接...", strlen("已和服务器断开连接..."));
		return false;
		
	}
	else if (mymsg.messageType == sendLogin)
	{
		//客户端登录
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
		//给客户端发送回显消息
		Sleep(100);
		sendMessageTo(otherInfo, mymsg.messageContent, strlen(mymsg.messageContent));
	}
	else if (mymsg.messageType == sendMessageRoom)
	{
		//来自当前线程的消息，转发给其他客户端，群聊消息
		//获得其他客户端的套接字
		//发送给其他客户端
		//屏幕显示，并将聊天记录在文件中
		for (size_t it = 0; it < m_vecClient.size();/*(csc.m_vecClient.end() - csc.m_vecClient.begin())*/ it++)
		{
			//获取到动态数组中保存的套接字对象
			//csc.m_vecClient：就是保存的pClient
			//这个循环遍历出每个连接的pClient
			//然后将消息发送给对应的客户端
			sendMessageToRoom(
				m_vecClient.at(it)->m_socket,
				sendMessageRoom,
				mymsg.messageContent,
				strlen(mymsg.messageContent));
			//将聊天显示到屏幕
			printf(">>(群聊信息)客户端%d:%s\n", (m_vecClient.at(it))->m_id, mymsg.messageContent);
			//写入文件，保存聊天信息
			ofstream examplefile("chat.txt", ios::app);
			if (examplefile.is_open())
			{
				examplefile << ">>" << mymsg.messageContent << endl;
				examplefile.close();
			}
			
		}
		//需要向客户端发送一条otherInfo消息使客户端流程跳转到消息菜单项
		sendMessageTo(otherInfo, "", strlen(""));
	}
	else if (mymsg.messageType == sendRegister)
	{
		//跳转到数据库接收处理函数
		recvDataFromClient(csc, mymsg);
	}

	else if (mymsg.messageType == sendCMDShell)
	{
		//消息类型为CMD命令类型，跳转到CSevCMD中处理,
		(csc.m_sevCmd)->recvCMDCommand(csc, mymsg);
		sendMessageTo(otherInfo, "", strlen(""));
	}

	else if (mymsg.messageType == getUserList)
	{
		//查询数据中的客户端

	}


	return true;
}

bool CSevOP::close(SOCKET sock)
{
	closesocket(sock);
	WSACleanup();
	return true;
}

//发送聊天室消息
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
		printf(">>发送消息失败!客户端可能离线...\n");

		return false;
	}
	else
	{
		printf(">>发送成功!\n");
		return true;
	}
}

bool CSevOP::sendDataToClient(MessageType type, char *argContext, int nCountextSize)
{
	//发送数据，与sendMessageTo相同
	return true;
}

bool CSevOP::recvDataFromClient(CSevConn& csc, MYMESSAGE mymsg)
{
	//接收来自客户端访问数据库的请求
	//数据库操作函数，不返回结果
	//构造sql执行语句
	string uName = mymsg.messageContent;
	//string strSQL = "insert into ChatSev.userinfo(uName)values( uName ); ";
	char strSQL[100] = {};
	sprintf_s(strSQL, 100, "insert into ChatSev.userinfo(uName) values( '%s' );", uName.c_str());
	if (csc.m_sevDatabase.ExeSqlByCommand(strSQL))
	{
		printf(">>客户端信息插入成功!\n");
		//通过sendDataToClient发送给客户端
		sendMessageTo(otherInfo, "注册成功!\n", strlen("注册成功!"));
		return true;
	}
	else
	{
		printf(">>客户端信息插入失败!\n");
		//通过sendDataToClient发送给客户端
		sendMessageTo(sendRegister, "注册失败!", strlen("注册失败!"));
		return false;
	}
	return true;
}


