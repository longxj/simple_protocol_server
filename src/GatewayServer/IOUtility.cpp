#include "IOUtility.hpp"
#include <stdio.h>

void CIOUtility::PrintBin(const char* pBuffer, size_t uiSize)
{
	if (!pBuffer)
	{
		return;
	}

	for (int i = 0; i < uiSize; i++)
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

	for (int i = 0; i < uiSize; i++)
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
