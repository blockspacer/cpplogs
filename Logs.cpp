// Logs.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Logs.h"
#include <time.h>
using namespace std;


string WORD2string(WORD w)
{
	char tmpbuff[16];
	sprintf(tmpbuff,"%d",w);
	string res=tmpbuff;
	return res;
}

YTLog::YTLog(){
	m_logname = L"";
	m_log_handle = nullptr;
	cout << "��־��ʼ������" << endl;
}

YTLog::~YTLog()
{
	cout << "��־ָ������" << endl;
}

YTLog* YTLog::m_ytl = nullptr; //����Ϊ��

bool YTLog::InitLog(std::wstring& log_file_name)
{
	m_logname = log_file_name;
	if (::PathFileExistsW(log_file_name.c_str()))
	{
		cout << "log�ļ��Ѵ���" << endl;
		return false; //�ļ��Ѵ���
	}
	HANDLE p_Handle = CreateFile(log_file_name.c_str(),GENERIC_READ|GENERIC_WRITE,
		0,0,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);
	if (p_Handle)
	{
		m_log_handle = p_Handle;
	}
	return false;
}

//��¼Log
bool YTLog::WriteLog(std::string& logs)
{
	logs.append("\n"); //��ӷֺ�
	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 
	std::string timeStr=""; //��¼����
	timeStr.append(WORD2string(sys.wYear));
	timeStr.append("��");
	timeStr.append(WORD2string(sys.wMonth));
	timeStr.append("��");
	timeStr.append(WORD2string(sys.wDay));
	timeStr.append("��");
	timeStr.append(WORD2string(sys.wHour));
	timeStr.append("ʱ");
	timeStr.append(WORD2string(sys.wMinute));
	timeStr.append("��");
	timeStr.append(WORD2string(sys.wSecond));
	timeStr.append("��");
	timeStr.append(WORD2string(sys.wMilliseconds));
	timeStr.append("���룺");
	timeStr.append(logs);
	if (!m_log_handle)
	{
		cout << "log�ļ�Ϊ�գ�" << endl;
		return false;
	}
	DWORD dwWrite = 0;
	WriteFile(m_log_handle,timeStr.c_str(),strlen(timeStr.c_str()),&dwWrite,NULL);
	return true;
}

YTLog* YTLog::GetInstance()
{
	if(m_ytl == nullptr)
	{
		m_ytl = new YTLog();
	}
	return m_ytl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	YTLog * ytl = YTLog::GetInstance();
	std::wstring path_name = L"demo.log";
	ytl->InitLog(path_name);
	std::string log_info = "����һ�����ݿ���";
	ytl->WriteLog(log_info);
	std::string log_info11 = "������һ��";
	ytl->WriteLog(log_info11);
	system("pause");
	return 0;
}

