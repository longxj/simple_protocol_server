#ifndef __EPOLLSOCKET_HPP
#define __EPOLLSOCKET_HPP

typedef int (*EpollInputFuction)(int iFd) EpollInputCallBackFunction;

class CEpollSocket
{
public:
	int Init(const char* szServerAddr, int iPort);
	int Wait(int iTimeout = 0);
	int RegisterEpollEventFunction(void* pFunction, const int iEventType);
	
private:
	int m_iEpollSocketID;
	int m_iListenSocketID;
	struct sockaddr_in m_stServerAddr;
	struct epoll_event m_stListenEvent;
	EpollInputCallBackFunction m_fpEpollInputCallBackFunc;
	
public:
	static const int MAX_CLIENT_CONNECTION;

public:
	static int SetNonblocking(int iSock);
	
};

#endif
