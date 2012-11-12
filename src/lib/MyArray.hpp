#ifndef __MYARRAY_HPP
#define __MYARRAY_HPP

#include <assert.h>

template<class T, unsigned int MAXARRAYSIZE>
class CMyArray
{
public:
	T& operator[](int i)
	{
		assert(i >= 0 && i < GetCapacity() && i < GetSize());
		return m_astData[i];
	}

	int GetCapacity() const {return MAXARRAYSIZE;}
	int GetSize() const {return m_iSize;}
	void SetSize(unsigned int iSize)
	{
		assert(iSize <= MAXARRAYSIZE);
		m_iSize = iSize;
	}

	int Append(const T& stValue)
	{
		if (m_iSize >= GetCapacity())
		{
			return -1;
		}

		m_astData[m_iSize++] = stValue;
	}
			
private:
	unsigned int m_iSize;	
	T m_astData[MAXARRAYSIZE];
};

#endif
