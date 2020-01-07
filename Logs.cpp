// Logs.cpp : 定义控制台应用程序的入口点。
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
	cout << "日志初始化创建" << endl;
}

YTLog::~YTLog()
{
	cout << "日志指针销毁" << endl;
}

YTLog* YTLog::m_ytl = nullptr; //申明为空

bool YTLog::InitLog(std::wstring& log_file_name)
{
	m_logname = log_file_name;
	if (::PathFileExistsW(log_file_name.c_str()))
	{
		cout << "log文件已存在" << endl;
		return false; //文件已存在
	}
	HANDLE p_Handle = CreateFile(log_file_name.c_str(),GENERIC_READ|GENERIC_WRITE,
		0,0,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);
	if (p_Handle)
	{
		m_log_handle = p_Handle;
	}
	return false;
}

//记录Log
bool YTLog::WriteLog(std::string& logs)
{
	logs.append("\n"); //添加分号
	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 
	std::string timeStr=""; //记录日期
	timeStr.append(WORD2string(sys.wYear));
	timeStr.append("年");
	timeStr.append(WORD2string(sys.wMonth));
	timeStr.append("月");
	timeStr.append(WORD2string(sys.wDay));
	timeStr.append("日");
	timeStr.append(WORD2string(sys.wHour));
	timeStr.append("时");
	timeStr.append(WORD2string(sys.wMinute));
	timeStr.append("分");
	timeStr.append(WORD2string(sys.wSecond));
	timeStr.append("秒");
	timeStr.append(WORD2string(sys.wMilliseconds));
	timeStr.append("毫秒：");
	timeStr.append(logs);
	if (!m_log_handle)
	{
		cout << "log文件为空！" << endl;
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
	std::string log_info = "测试一下数据可以";
	ytl->WriteLog(log_info);
	std::string log_info11 = "测试另一卒";
	ytl->WriteLog(log_info11);
	system("pause");
	return 0;
}

