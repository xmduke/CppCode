#include "SevDatabase.h"
#include <tchar.h>

CSevDatabase::CSevDatabase()
{
	//初始化com组件
	::CoInitialize(NULL);
	m_pConn.CreateInstance(_T("ADODB.Connection"));
	m_pRecordSet.CreateInstance(_T("ADODB.Recordset"));
}


CSevDatabase::~CSevDatabase()
{
	if (m_pConn)
	{
		try
		{
			//关闭数据库
			HRESULT hr = m_pConn->Close();
			//关闭记录集
			m_pRecordSet->Close();
			//释放com组件
			::CoUninitialize();
		}
		catch (_com_error e)
		{
			//	AfxMessageBox(e.Description());
		}
	}
}

bool CSevDatabase::LinkDatabase()
{
	//连接数据库
	try
	{
		m_pConn->Open(_bstr_t("FILE Name=sql.udl"),
			_bstr_t(""),
			_bstr_t(""),
			adConnectUnspecified);
	}
	catch (_com_error e)
	{
		MessageBox(0, e.ErrorMessage(), 0, 0);
		return false;
	}
	return true;
}

bool CSevDatabase::ExeSqlByConnect(RESULT &re, string sql)
{
	return true;
}

bool CSevDatabase::ExeSqlByCommand(string sql)
{

	try
	{
		LinkDatabase();
		_variant_t Record;
		m_pConn->Execute(_bstr_t(sql.c_str()),
			&Record, adCmdText);
	}
	catch (_com_error e)
	{
		MessageBox(0, e.Description(),e.ErrorMessage(), 0);
		return false;
	}

	return true;

}

bool CSevDatabase::ExeSqlByReCordSet(RESULT &re, string sql)
{
	try
	{
		//打开记录集
		m_pRecordSet->Open(_bstr_t(sql.c_str()),
			m_pConn.GetInterfacePtr(),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		//取列名
		Fields *pFields = m_pRecordSet->GetFields();
		//获取字段数量
		long lCount = pFields->GetCount();
		//数量为0则返回false
		if (lCount == 0)
		{
			return false;
		}
		for (long i = 0; i < lCount; i++)
		{
			//取出每个字段的名字
			FieldPtr pFieldPtr = pFields->GetItem(i);
			string colName = pFieldPtr->GetName();
			re.vecColName.push_back(colName);
		}
		//读取数据
		while (!m_pRecordSet->GetadoEOF())
		{
			vector <string> itemelem;
			for (long i = 0; i < lCount; i++)
			{
				//通过序号或字段获取当前行中的数据
				_variant_t value = m_pRecordSet->GetCollect(i);
				if (value.vt == VT_NULL)
				{
					itemelem.push_back("");
					continue;
				}
				string str = _bstr_t(value);
				itemelem.push_back(str);
			}

			re.vecData.push_back(itemelem);
			m_pRecordSet->MoveNext();
		}
	}
	catch (_com_error e)
	{
		MessageBox(0, e.ErrorMessage(), 0, 0);
		return false;
	}
	
	return true;
}

bool CSevDatabase::ParseResult(RESULT &re, _RecordsetPtr pRecord)
{
	
	return true;
}
