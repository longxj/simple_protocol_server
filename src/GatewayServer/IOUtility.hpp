#ifndef __IOUTILITY_HPP
#define __IOUTILITY_HPP

#include <stddef.h>

class CIOUtility
{
public:
	static void PrintBin(char* pBuffer, size_t uiSize);
	static void PrintHex(char* pBuffer, size_t uiSize);
};

#endif
