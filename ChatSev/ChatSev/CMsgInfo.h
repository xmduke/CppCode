#pragma once
#include <vector>
using namespace std;
/************************************************************************/
/*定义消息的结构体

*/
/************************************************************************/
#define MAXMESSAGEBUF 1024

//用于保存数据库中表的数据
typedef struct _RESULT
{
	//字段名称
	vector<string> vecColName;
	//字段对应的数据
	vector<vector<string>> vecData;
}RESULT, *P_RESULT;

//消息头结构体
typedef struct _MYMESSAGE
{
	//消息类型
	int messageType;
	//消息长度
	int messageSize;
	//消息内容
	char messageContent [MAXMESSAGEBUF];
}MYMESSAGE;

//消息类型
enum MessageType
{
	//发送注册信息
	sendRegister = 1,
	//发送登录信息
	sendLogin,
	//给聊天室发送文字
	sendMessageRoom,
	//给聊天室发送图片
	sendPicRoom,
	//给好友单独发送文字
	sendMessageSingl,
	//给好友单独发送图片
	sendPicSingl,
	//获取所有在线玩家列表
	getUserList,
	//获取好友玩家列表
	getFriendList,
	//添加好友关系
	addFriends,
	//其他类型信息
	otherInfo,
	//客户端退出消息
	sendLogout,
	//远程控制消息
	sendCMDShell
};
