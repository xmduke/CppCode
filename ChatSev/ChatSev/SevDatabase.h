#pragma once
#include "CMsgInfo.h"
//0.�����
#import "C:\\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll"no_namespace rename("EOF", "adoEOF")
/************************************************************************/
/* ��װ���ݿ����
1.����
2.����
3.ɾ��
4.�޸�
5.��ѯ
*/
/************************************************************************/
class CSevDatabase
{
public:
	//1.��ʼ��COM���
	CSevDatabase();
	//�ͷ�CCM���
	~CSevDatabase();

public:
	//2.�������ݿ�
	bool LinkDatabase();
	//3.����SQL���
	bool ExeSqlByConnect(RESULT &re, string sql);
	//4.����SQL����
	bool ExeSqlByCommand(string sql);
	//5.���ս����
	bool ExeSqlByReCordSet(RESULT &re, string sql);
	//6.�����صĽ����
	bool ParseResult(RESULT &re, _RecordsetPtr pRecord);
public:
	_ConnectionPtr m_pConn;
	_RecordsetPtr m_pRecordSet;
};

