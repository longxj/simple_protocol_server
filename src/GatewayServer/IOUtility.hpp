#ifndef __IOUTILITY_HPP
#define __IOUTILITY_HPP

#include <stddef.h>

class CIOUtility
{
public:
	static void PrintBin(const char* pBuffer, size_t uiSize);
	static void PrintHex(const char* pBuffer, size_t uiSize);
};

#endif
