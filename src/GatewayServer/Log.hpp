#ifndef __LOG_HPP
#define __LOG_HPP

#include "Singleton.hpp"
#include <stdio.h>

class CLog
{
public:
	CLog();

	int Init(const char* szLogFilePath, int iLogLevel = 0);//default is debug level
	int DoLog(int iLogLevel, const char* szFileName, int iLine, const char* szFunction, const char* szLogStr, ...);

public:
	static const int LEVEL_DEBUG = 0;
	static const int LEVEL_INFO = 1;
	static const int LEVEL_ERROR = 2;

private:
	int m_iLogLevel;
	FILE* m_pstFile;
};


#define LOG_DEBUG(szLogStr, ...) {CSingleton<CLog>::Instance()->DoLog(CLog::LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, szLogStr, ##__VA_ARGS__);}

#define LOG_INFO(szLogStr, ...) {CSingleton<CLog>::Instance()->DoLog(CLog::LEVEL_INFO, __FILE__, __LINE__, __FUNCTION__, szLogStr, ##__VA_ARGS__);}

#define LOG_ERROR(szLogStr, ...) {CSingleton<CLog>::Instance()->DoLog(CLog::LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, szLogStr, ##__VA_ARGS__);}

#endif
