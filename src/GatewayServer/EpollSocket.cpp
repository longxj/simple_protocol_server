#include "EpollSocket.hpp"

const int CEpollSocket::MAX_CLIENT_CONNECTION = 1000;

int CEpollSocket::Init()
{
	m_iEpollSocketID = epoll_create(CEpollSocket::MAX_CLIENT_CONNECTION);
	m_iListenSocketID = socket(AF_INET, SOCK_STREAM, 0);

	if(CEpollSocket::SetNonblocking(m_iListenSocketID) < 0)
	{
		return -1;
	}

	m_stListenEvent.data.fd = m_iListenSocketID;
	m_stListenEvent.events = EPOLLIN | EPOLLET;
}

int CEpollSocket::SetNonblocking(int iSock)
{
	int iOpts;
	iOpts=fcntl(iSock,F_GETFL);
	if(iOpts < 0)
	{
		return iOpts;
	}
	iOpts = iOpts|O_NONBLOCK;
	int iRet = 0;
	iRet = fcntl(iSock, F_SETFL, iOpts);
	if(iRet < 0)
	{
		return iRet;
	}

	return 0;   
}
