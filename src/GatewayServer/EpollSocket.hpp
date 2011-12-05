#ifndef __EPOLLSOCKET_HPP
#define __EPOLLSOCKET_HPP

class CEpollSocket
{
public:
	int Init();
	
private:
	int m_iEpollSocketID;
	int m_iListenSocketID;
	struct epoll_event m_stListenEvent;
	struct epoll_event m_astEvent[CEpollSocket::MAX_CLIENT_CONNECTION];

public:
	static const int MAX_CLIENT_CONNECTION;

public:
	static int SetNonblocking(int iSock);
	
};

#endif
