#pragma once
#include "CMsgInfo.h"
//0.引入库
#import "C:\\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll"no_namespace rename("EOF", "adoEOF")
/************************************************************************/
/* 封装数据库操作
1.连接
2.增加
3.删除
4.修改
5.查询
*/
/************************************************************************/
class CSevDatabase
{
public:
	//1.初始化COM组件
	CSevDatabase();
	//释放CCM组件
	~CSevDatabase();

public:
	//2.连接数据库
	bool LinkDatabase();
	//3.发送SQL语句
	bool ExeSqlByConnect(RESULT &re, string sql);
	//4.发送SQL命令
	bool ExeSqlByCommand(string sql);
	//5.接收结果集
	bool ExeSqlByReCordSet(RESULT &re, string sql);
	//6.处理返回的结果集
	bool ParseResult(RESULT &re, _RecordsetPtr pRecord);
public:
	_ConnectionPtr m_pConn;
	_RecordsetPtr m_pRecordSet;
};

