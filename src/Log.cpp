#include "Log.hpp"
#include <time.h>

int CLog::Init(char* szLogFilePath, int iLogLevel)
{
	if(!szLogFilePath)
	{
		return -1;
	}

	m_pstFile = fopen(szLogFilePath, "a+");
	if(m_pstFile == NULL)
	{
		return -2;
	}

	//loglevel has to be a positive value
	if(iLogLevel < 0)
	{
		return -3;
	}
	
	m_iLogLevel = iLogLevel;
}


int CLog::DoLog(int iLogLevel, char* szLogStr, ...)
{
	if(iLogLevel < m_iLogLevel)
	{
		return 0;
	}

	//print the date and time first
	va_list stArgs;
	va_start(stArgs, szLogStr);

	time_t stTime;
	time (&stTime);
	fprintf(m_pstFile, "[%s]", ctime(&stTime));
	vfprintf(m_pstFile, szLogStr, stArgs);

	va_end(stArgs);
}
