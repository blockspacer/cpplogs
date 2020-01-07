#include "stdafx.h"

//Log日志
class YTLog
{
public:
	YTLog();
	~YTLog();

	bool InitLog(std::wstring& log_file_name); //初始化Log
	bool WriteLog(std::string& logs); //记录Log
	static YTLog* m_ytl ;
	static YTLog* GetInstance();    //获取YTLog的实例
public:
	std::wstring m_logname; //记录Log名称
	HANDLE m_log_handle;//文件句柄
};