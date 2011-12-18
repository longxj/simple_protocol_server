#include "EpollSocket.hpp"

const int CEpollSocket::MAX_CLIENT_CONNECTION = 1000;

int CEpollSocket::Init(const char* szServerAddr, int iPort)
{
	if(!szServerAddr)
	{
		LOG_ERROR("Error: server addr is null. \n");
		return -1;
	}
	
	m_iEpollSocketID = epoll_create(CEpollSocket::MAX_CLIENT_CONNECTION);
	m_iListenSocketID = socket(AF_INET, SOCK_STREAM, 0);

	if(CEpollSocket::SetNonblocking(m_iListenSocketID) < 0)
	{
		return -1;
	}

		//add the listen socket into epollsocket
	memset(&m_stListenEvent, 0, sizeof(m_stListenEvent));
	m_stListenEvent.data.fd = m_iListenSocketID;
	m_stListenEvent.events = EPOLLIN | EPOLLET;
	epoll_ctl(m_iEpollSocketID, EPOLL_CTL_ADD, m_iListenSocketID, &m_stListenEvent);

	memset(&m_stServerAddr, 0, sizeof(m_stServerAddr));
	m_stServerAddr.sin_family = AF_INET;
	inet_aton(szServerAddr, &m_stServerAddr.sin_addr);
	m_stServerAddr.sin_port = htons(iPort);
	bind(m_iListenSocketID, (sockaddr_in* )&m_stServerAddr, sizeof(m_stServerAddr));
	listen(m_iListenSocketID, CEpollSocket::MAX_CLIENT_CONNECTION);	
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

