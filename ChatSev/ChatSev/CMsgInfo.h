#pragma once
#include <vector>
using namespace std;
/************************************************************************/
/*������Ϣ�Ľṹ��

*/
/************************************************************************/
#define MAXMESSAGEBUF 1024

//���ڱ������ݿ��б������
typedef struct _RESULT
{
	//�ֶ�����
	vector<string> vecColName;
	//�ֶζ�Ӧ������
	vector<vector<string>> vecData;
}RESULT, *P_RESULT;

//��Ϣͷ�ṹ��
typedef struct _MYMESSAGE
{
	//��Ϣ����
	int messageType;
	//��Ϣ����
	int messageSize;
	//��Ϣ����
	char messageContent [MAXMESSAGEBUF];
}MYMESSAGE;

//��Ϣ����
enum MessageType
{
	//����ע����Ϣ
	sendRegister = 1,
	//���͵�¼��Ϣ
	sendLogin,
	//�������ҷ�������
	sendMessageRoom,
	//�������ҷ���ͼƬ
	sendPicRoom,
	//�����ѵ�����������
	sendMessageSingl,
	//�����ѵ�������ͼƬ
	sendPicSingl,
	//��ȡ������������б�
	getUserList,
	//��ȡ��������б�
	getFriendList,
	//��Ӻ��ѹ�ϵ
	addFriends,
	//����������Ϣ
	otherInfo,
	//�ͻ����˳���Ϣ
	sendLogout,
	//Զ�̿�����Ϣ
	sendCMDShell
};
