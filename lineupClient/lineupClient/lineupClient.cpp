// lineupClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Winsock2.h"
#include <string>
#include <memory.h>
#pragma comment(lib, "Ws2_32.lib")
#define CLIENT_SOCKET_DLL_ERROR -1
#define CLIENT_API_ERROR 0
#define MAX_NUM_BUF 256
//�˿�
#define SERVERPORT 5555
//IP��ַ
#define SERVERIP "10.11.117.48"

CHAR *bufdata;//���������������Է���˵�����
CHAR* bufRecv = NULL;//
char bufSend[256];
SOCKET sServer;
SOCKET sClient;
BOOL bConning;//һ����־���ж��Ƿ�����


/************************************************************************/
/* ���ܣ���ʼ��ȫ�ֳ�Ա����
   ��������
   ���أ���
/************************************************************************/
void InitMember()
{
	//memset(bufRecv, 0, sizeof(bufRecv));
	memset(bufSend, 0, sizeof(bufSend));

	sServer = INVALID_SOCKET;
	sClient = INVALID_SOCKET;
	bConning = FALSE;
}

/************************************************************************/
/* ���ܣ���ʼ���׽��ֵĿ⣬�汾�жϵ�
   ��������
   ���أ�int ���ش������
/************************************************************************/
int InitSocketDll()
{
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(1, 1);
	int err = WSAStartup(wVersionRequested, (LPWSADATA)&wsaData);
	if (0 != err)
	{
		MessageBox(NULL, L"Can not find a windows socket dll!", L"error", MB_OK);
		return CLIENT_SOCKET_DLL_ERROR;
	}
	return err;
}

/************************************************************************/
/* ���ܣ��˳��ͻ��ˣ��ر��׽��ֵ�
   ������int �˳�ֵ��������Ϣ�궨�� CLIENT_SOCKET_DLL_ERROR
   ���أ��˳�ֵ
/************************************************************************/
int ExitClient(int nEixt)
{
	closesocket(sServer);
	closesocket(sClient);
	WSACleanup();
	return nEixt;
}

/************************************************************************/
/* ���ܣ���ʾ������Ϣ
   ��������
   ���أ���
/************************************************************************/
void ShowErrorMsg()
{
	int nErrCode = WSAGetLastError();
	HLOCAL hlocal = NULL;

	BOOL fOk = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		nErrCode,
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		(PTSTR)&hlocal,
		0,
		NULL);

	if (hlocal != NULL)
	{
		MessageBox(NULL, (LPCWSTR)LocalLock(hlocal), L"CLIENT ERROR", MB_OK);
		LocalFree(hlocal);
	}
}


/************************************************************************/
/* ���ܣ������׽���
   ��������
   ���أ�SOCKET
/************************************************************************/
SOCKET CreateSocket()
{
	SOCKET sHost;
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		ShowErrorMsg();
		WSACleanup();
		return CLIENT_API_ERROR;
	}
	return sHost;
}

/************************************************************************/
/* ���ܣ����ӷ�����
   ������sHost �����������׽���
   ���أ�int �����󷵻ص�ֵ
/************************************************************************/
int ConnectServer(SOCKET sHost)
{
	//LPHOSTENT hostEntry;
	/*char hostname[MAX_NUM_BUF];
	gethostname(hostname, MAX_NUM_BUF);
	hostEntry = gethostbyname(hostname);
	if (!hostEntry)
	{
		ShowErrorMsg();
		return ExitClient(CLIENT_API_ERROR);

	}*/
	SOCKADDR_IN addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_addr.S_un.S_addr = inet_addr(SERVERIP);;//*((LPIN_ADDR)*hostEntry->h_addr_list);
	addrServ.sin_port = htons(SERVERPORT);

	int retVal = connect(sHost, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{
		ShowErrorMsg();
		return ExitClient(CLIENT_API_ERROR);
	}
	else
	{
		bConning = TRUE;
	}
	return retVal;
}

/************************************************************************/
/* ���ܣ�������Ϣ�������
   ������SOCKET sHost �������׽���
        char* bufSend ������Ϣ������
   ���أ�int ʵ�ʷ��͵��ֽ�
/************************************************************************/
int SendMsg(SOCKET sHost, char* bufSend)
{
	//strcpy(bufSend, "Hello, Server!\n");
	int retVal = send(sHost, bufSend, strlen(bufSend), 0);
	if (SOCKET_ERROR == retVal)
	{
		ShowErrorMsg();
		return ExitClient(CLIENT_API_ERROR);
	}
	return retVal;
}

/************************************************************************/
/* ���ܣ����շ������Ϣ
   ������SOCKET sClient,�����׽���
        CHAR *buf,�������ݱ���Ļ�����
		int size��һ�ν��ն����ֽ�
   ���أ�ʵ�ʽ��յ��ֽ�
/************************************************************************/
int RecvLine(SOCKET sClient, CHAR *buf, int size)
{
	BOOL retVal = TRUE;
	BOOL bLineEnd = FALSE;
	int nReadLen = 0;
	int nDataLen = 0;

	nReadLen = recv(sClient, buf, size, 0);
	int n = GetLastError();
	if (SOCKET_ERROR == nReadLen)
	{
		retVal = FALSE;
		return 0;
	}

	if (0 == nReadLen)
	{
		retVal = FALSE;
		return 0;
	}

	if ('\n' == *(buf + nDataLen))
	{
		bLineEnd = TRUE;
	}
	return nReadLen;
}


int _tmain(int argc, _TCHAR* argv[])
{
	//1.��ʼ���׽���
	printf("[*] ��ʼ���׽���...\n");
	InitMember();

	if (0 == InitSocketDll())
	{
		printf("[*] InitSocket finish!\n");
	}
	else
	{
		ShowErrorMsg();
	};

	//2.�����ͻ����׽���
	printf("[*] �����ͻ����׽���...\n");
	sClient = CreateSocket();
	
	//3.���ӷ����
	printf("[*] ���ӷ����...\n");
	ConnectServer(sClient);

	//4.����Start����
	printf("[*] ����Start����...\n");
	strcpy(bufSend, "ps -a");
	SendMsg(sClient, bufSend);

	//5.׼�����շ���˷��͵�ps -a����
	printf("[*] ���շ���˷��͵�pa -a����...\n");

	//6.����һ�����ݵĳ��ȣ�����Ϊps -a������

	//ps -a�����ܳ���
	CHAR *bufdatalen;
	//����һ��8�ֽڵĶѿռ��ų���ֵ
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	//��0
	memset(bufdatalen, 0, sizeof(bufdatalen));
	//��ʼ���ճ���ֵ
	int bufLenRecv = RecvLine(sClient, bufdatalen, 128);
	//������תlong
	long bufLen = atoi(bufdatalen);
	//�ͷŻ�����
	free(bufdatalen);

	//����֮�������˷���һ��okָ���ʾ��������
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);
	
	//7.��ʼ��������
	//���ݵĳ���
	int bufRecvLen = 0;
	//����һ��256�Ķѿռ䱣��ps -a������
	bufdata = (CHAR *)malloc(256 * sizeof(CHAR));
	//��0
	memset(bufdata, 0, sizeof(bufdata));
	printf("pa -a����:\n");
	while (bufLen > 0)
	{
		//��ʼ����
		bufRecvLen = RecvLine(sClient, bufdata + bufRecvLen, 1);
		printf("%s", bufdata +bufRecvLen);
		bufLen--;
	}
	//�ͷŻ�����
	free(bufdata);

	//8.����PIDֵ�������
	int pid = 0;
	CHAR str_pid[5] = {0};
	printf("����pid��");
	scanf("%d", &pid);
	memset(bufSend, 0, sizeof(bufSend));
	itoa(pid, str_pid, 10);
	strcpy(bufSend, str_pid);
	SendMsg(sClient, bufSend);

	//9.�����ڴ沼�ֳ���
	printf("[*] �����ڴ沼�ֳ���...\n");

	//���ճ���ֵ
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	//��ʼ����
	bufLenRecv = RecvLine(sClient, bufdatalen, 128);
	bufLen = atoi(bufdatalen);
	//�ͷ�
	free(bufdatalen);
	//���������ok����
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	//ʵ�ʽ��յ����ڴ沼�����ݵĳ���
	int bufRecvMemLen = 0;
	bufdata = (CHAR *)malloc(256 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	printf("�ڴ沼��:\n");
	while (bufLen > 0)
	{
		//��ʼ�����ڴ沼�ֵ�����
		bufRecvMemLen = RecvLine(sClient, bufdata + bufRecvMemLen, 1);
		printf("%s", bufdata + bufRecvMemLen);
		bufLen--;
	}
	free(bufdata);

	//10.����Sleep����
	printf("[*] ����Sleep������15��...\n");
	strcpy(bufSend, "15");
	SendMsg(sClient, bufSend);

	//11.���Ͷγ���
	printf("[*] ���Ͷγ���...\n");
	strcpy(bufSend, "16");
	SendMsg(sClient, bufSend);

	
	// ���շ����ok��Ϣ
	char okbuf[2] = { 0 };
	long ok = RecvLine(sClient, okbuf, 3);

	//������Ҫˢ�������뻺��������Ȼ�´ν������ݻ����\n�����ݲ���
	fflush(stdin);

	//����һ��32�ֽڳ��ȵ��ַ���0-15��ʾ��ʼ��ַ��16-31��ʾ����
	char starAddr[33] = {0};
	printf("����32�ֽڳ��ȵ��ַ���0-15��ʾ��ʼ��ַ��16-31��ʾ���ȣ�");
	for (int i = 0; i < 33; i++)
	{
		scanf("%c", &starAddr[i]);
	}
	//���͸������
	strcpy(bufSend, starAddr);
	SendMsg(sClient, bufSend);
	//����Ҳ��Ҫ�ٷ���һ��ok��־
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	printf("[*] ���ڽ������ݲ�ת����txt�ļ�...\n");
	//12.��һ�ν���log�ļ�
	//����dump_ca.log
	freopen("dump_ca.log", "w", stdout);
	printf("[*] ����dump_ca.log...\n");
	//�Ƚ���һ��log�ļ�����
	int bufRecvdump_caLen = 0;
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	bufLenRecv = RecvLine(sClient, bufdatalen, 8);
	bufLen = atoi(bufdatalen);
	free(bufdatalen);
	//���Ƚ����귢��ok
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);
	
	//��ʼ��������
	printf("dump_ca.log:\n");
	bufdata = (CHAR *)malloc(1024 * 1000 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	while (bufLen > 0)
	{
		//����
		bufRecvdump_caLen = RecvLine(sClient, bufdata + bufRecvdump_caLen, 1);
		printf("%s", bufdata + bufRecvdump_caLen);
		bufLen--;
	}
	//�ͷ�
	free(bufdata);

	//13.����dump_data.log
	freopen("dump_data.log", "w", stdout);
	printf("[*] ����dump_data.log...\n");
	//�Ƚ��ճ���
	int bufRecvdump_dataLen = 0;
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	bufLenRecv = RecvLine(sClient, bufdatalen, 8);
	bufLen = atoi(bufdatalen);
	free(bufdatalen);
	//����ok
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	//��ʼ����log����
	printf("dump_data.log:\n");
	bufdata = (CHAR *)malloc(1024 * 1000 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	while (bufLen > 0)
	{
		//����
		bufRecvdump_dataLen = RecvLine(sClient, bufdata + bufRecvdump_dataLen, 1);
		printf("%s", bufdata + bufRecvdump_dataLen);
		bufLen--;
	}
	free(bufdata);
	//����ok
	//strcpy(bufSend, "ok");
	//SendMsg(sClient, bufSend);

	/////�ٽ���һ�Σ�������һ��
	//14.����dump_ca2.log
	freopen("dump_ca2.log", "w", stdout);
	printf("[*] ����dump_ca2.log...\n");
	bufRecvdump_caLen = 0;
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	bufLenRecv = RecvLine(sClient, bufdatalen, 8);
	bufLen = atoi(bufdatalen);
	free(bufdatalen);
	//����ok
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	//��������
	printf("dump_ca2.log:\n");
	bufdata = (CHAR *)malloc(1024 * 1000 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	while (bufLen > 0)
	{
		bufRecvdump_caLen = RecvLine(sClient, bufdata + bufRecvdump_caLen, 1);
		printf("%s", bufdata + bufRecvdump_caLen);

		bufLen--;
	}
	free(bufdata);


	//15.����dump_data.log
	freopen("dump_data2.log", "w", stdout);
	printf("[*] ����dump_data2.log...\n");
	bufRecvdump_dataLen = 0;
	bufdatalen = (CHAR *)malloc(8 * sizeof(CHAR));
	memset(bufdatalen, 0, sizeof(bufdatalen));
	bufLenRecv = RecvLine(sClient, bufdatalen, 8);
	bufLen = atoi(bufdatalen);
	free(bufdatalen);
	//����ok
	strcpy(bufSend, "ok");
	SendMsg(sClient, bufSend);

	//��������
	printf("dump_data2.log:\n");
	bufdata = (CHAR *)malloc(1024 * 1000 * sizeof(CHAR));
	memset(bufdata, 0, sizeof(bufdata));
	while (bufLen > 0)
	{
		bufRecvdump_dataLen = RecvLine(sClient, bufdata + bufRecvdump_dataLen, 1);
		printf("%s", bufdata + bufRecvdump_dataLen);
		bufLen--;
	}
	free(bufdata);
	
	//16.����Stop����
	printf("[*] ����Stop����...\n");
	strcpy(bufSend, "stop");
	SendMsg(sClient, bufSend);

	//17.�ر��׽���
	printf("[*] �˳�...\n");

	ExitClient(0);
	return 0;
}

