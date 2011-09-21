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
		if(0 == m_stInstance)
		{
			m_stInstance.reset(new T);
		}

		return m_stInstance.get();
	}

private:
	Singleton(){}
	~Singleton(){}
	Singleton(const Singleton&);
	Singleton& operator= (const& Singleton&);

private:
	static auto_ptr<T> m_stInstance;
};			

#endif
