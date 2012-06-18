#include "Log.hpp"
#include <time.h>
#include <stdarg.h>
#include "StringUtility.hpp"

CLog::CLog()
{
}

int CLog::Init(const char* szLogFilePath, int iLogLevel)
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

	return 0;
}


int CLog::DoLog(int iLogLevel, const char* szFileName, int iLine, const char* szFunction, const char* szLogStr, ...)
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
	
	char* pTimeStr = ctime(&stTime);
	//rm the last newline
	CStringUtility::Chomp(pTimeStr);
	
	fprintf(m_pstFile, "[%s] ", pTimeStr); 
	fprintf(m_pstFile, "[%s<%s:%d>] ", szFunction, szFileName, iLine);
	switch(iLogLevel)
	{
		case LEVEL_DEBUG:
		{
			fprintf(m_pstFile, "Debug: ");
			break;
		}
		case LEVEL_INFO:
		{
			fprintf(m_pstFile, "Info: ");
			break;
		}
		case LEVEL_ERROR:
		{
			fprintf(m_pstFile, "Error: ");
			break;
		}
		default:
		{
			return -3;
		}
	}
	vfprintf(m_pstFile, szLogStr, stArgs);

	va_end(stArgs);

	//flush
	fflush(m_pstFile);

	return 0;
}
