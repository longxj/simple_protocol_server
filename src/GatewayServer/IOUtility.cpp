#include "IOUtility.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

void CIOUtility::PrintBin(const char* pBuffer, size_t uiSize)
{
	if (!pBuffer)
	{
		return;
	}

	for (unsigned int i = 0; i < uiSize; i++)
	{
		unsigned char ucTemp = (unsigned char)pBuffer[i];
		for (int iBit = 0; iBit < 8; iBit++)
		{
			if (ucTemp & 0x80)
			{
				printf("%c", '1');
			}
			else
			{
				printf("%c", '0');
			}

			ucTemp = ucTemp << 1;
		}
	}
}

void CIOUtility::PrintHex(const char* pBuffer, size_t uiSize)
{
	if (!pBuffer)
	{
		return;
	}

	for (unsigned int i = 0; i < uiSize; i++)
	{
		unsigned char ucTemp = (unsigned char)pBuffer[i];
		if (ucTemp < 16)
		{
			printf("0%x", ucTemp);
		}
		else
		{
			printf("%x", ucTemp);
		}
	}
}

int CIOUtility::SetNonblocking(const int iSock)
{
	int iOpts;
	iOpts = fcntl(iSock, F_GETFL);
	if(iOpts < 0)
	{
		return iOpts;
	}
	iOpts = iOpts | O_NONBLOCK;
	int iRet = 0;
	iRet = fcntl(iSock, F_SETFL, iOpts);
	if(iRet < 0)
	{
		return iRet;
	}

	return 0;
}

int CIOUtility::SetNonNagle(const int iSock)
{
	int iFlag = 1;
	return setsockopt(iSock, IPPROTO_TCP, TCP_NODELAY, (char *)&iFlag, sizeof(iFlag));
}
