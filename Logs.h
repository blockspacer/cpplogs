#include "stdafx.h"

//Log��־
class YTLog
{
public:
	YTLog();
	~YTLog();

	bool InitLog(std::wstring& log_file_name); //��ʼ��Log
	bool WriteLog(std::string& logs); //��¼Log
	static YTLog* m_ytl ;
	static YTLog* GetInstance();    //��ȡYTLog��ʵ��
public:
	std::wstring m_logname; //��¼Log����
	HANDLE m_log_handle;//�ļ����
};