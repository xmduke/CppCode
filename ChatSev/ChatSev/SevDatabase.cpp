#include "SevDatabase.h"
#include <tchar.h>

CSevDatabase::CSevDatabase()
{
	//��ʼ��com���
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
			//�ر����ݿ�
			HRESULT hr = m_pConn->Close();
			//�رռ�¼��
			m_pRecordSet->Close();
			//�ͷ�com���
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
	//�������ݿ�
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
		//�򿪼�¼��
		m_pRecordSet->Open(_bstr_t(sql.c_str()),
			m_pConn.GetInterfacePtr(),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		//ȡ����
		Fields *pFields = m_pRecordSet->GetFields();
		//��ȡ�ֶ�����
		long lCount = pFields->GetCount();
		//����Ϊ0�򷵻�false
		if (lCount == 0)
		{
			return false;
		}
		for (long i = 0; i < lCount; i++)
		{
			//ȡ��ÿ���ֶε�����
			FieldPtr pFieldPtr = pFields->GetItem(i);
			string colName = pFieldPtr->GetName();
			re.vecColName.push_back(colName);
		}
		//��ȡ����
		while (!m_pRecordSet->GetadoEOF())
		{
			vector <string> itemelem;
			for (long i = 0; i < lCount; i++)
			{
				//ͨ����Ż��ֶλ�ȡ��ǰ���е�����
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
