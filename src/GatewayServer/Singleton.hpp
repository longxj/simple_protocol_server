#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <memory>

using namespace std;

template<class T>
class CSingleton
{
public:
	static inline T* Instance()
	{
		if(0 == m_stInstance.get())
		{
			m_stInstance.reset(new T);
		}

		return m_stInstance.get();
	}

private:
	CSingleton(){}
	~CSingleton(){}
	CSingleton(const CSingleton&);
	CSingleton& operator= (const CSingleton&);

private:
	static auto_ptr<T> m_stInstance;
};

template<class T>
auto_ptr<T> CSingleton<T>::m_stInstance;

#endif
