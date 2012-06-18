#include <string.h>
#include "StringUtility.hpp"

void CStringUtility::Chomp(char* pStr)
{
	if (!pStr)
	{
		return;
	}
	
	int iLen = strlen(pStr);
	if ('\n' == pStr[iLen - 1])
	{
		pStr[iLen - 1] = 0;
	}
}
	
