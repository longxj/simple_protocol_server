#ifndef __EPOLLSOCKET_HPP
#define __EPOLLSOCKET_HPP

class CEpollSocket
{
public:
	int Init(const int iSocketSize);
	
private:
	int m_iEpollSocketID;
	int m_iListenSocketID;
	int m_iSocketSize;
	
};

#endif
