#include "EpollSocket.hpp"
#include <sys/socket.h>
#include <fcntl.h>
#include <stdio.h>

const int CEpollSocket::MAX_CLIENT_CONNECTION = 1000;

int CEpollSocket::Init(const char* szServerAddr, int iPort)
{
	if(!szServerAddr)
	{
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
	bind(m_iListenSocketID, (struct sockaddr* )&m_stServerAddr, sizeof(m_stServerAddr));
	listen(m_iListenSocketID, CEpollSocket::MAX_CLIENT_CONNECTION);	
}

int CEpollSocket::SetNonblocking(int iSock)
{
	int iOpts;
	iOpts = fcntl(iSock, F_GETFL);
	if(iOpts < 0)
	{
		return iOpts;
	}
	iOpts = iOpts | O_NONBLOCK;
	int iRet = 0;
	iRet = fcntl(iSock, F_SETFL, iOpts);
	if(iRet < 0)
	{
		return iRet;
	}

	return 0;   
}

//@return: negetive when error occurs, 0 when no error occurs
int CEpollSocket::Wait(int iTimeout)
{
	struct epoll_event astEvent[CEpollSocket::MAX_CLIENT_CONNECTION];
	memset(astEvent, 0, sizeof(astEvent));
	int iFds = epoll_wait(m_iEpollSocketID, astEvent, CEpollSocket::MAX_CLIENT_CONNECTION, iTimeout);
	if( iFds < 0)
	{
		perror("Error: epoll_wait fail.");
		return iFds;
	}

	for(int i = 0; i < iFds; i++)
	{
			//accept event
		if(astEvent[i].data.fd == m_iListenSocketID)
		{
			struct sockaddr_in stClientAddr;
			int iClientAddrLen = sizeof(stClientAddr);
			memset(&stClientAddr, 0, iClientAddrLen);
			int iConnFd = accept(m_iListenSocketID, (sockaddr* )&stClientAddr, (socklen_t*)&iClientAddrLen);
			if(iConnFd < 0)
			{
				perror("Error: accept fail.");
				continue;
			}

			CEpollSocket::SetNonblocking(iConnFd);
			struct epoll_event stEvent;
			memset(&stEvent, 0 ,sizeof(stEvent));

			stEvent.data.fd = iConnFd;
			stEvent.events = EPOLLIN | EPOLLET;

				//register event
			epoll_ctl(m_iEpollSocketID, EPOLL_CTL_ADD, iConnFd, &stEvent);
		}
			//data in event
		else if(astEvent[i].events & EPOLLIN)
		{
			int iSocketFd = -1;
			iSocketFd = astEvent[i].data.fd;
			if(iSocketFd < 0)
			{
				continue;
			}
				//to deal with the input data
		}
			//data output event
		else if(astEvent[i].events & EPOLLOUT)
		{
				//do nothing
			continue;
		}
	}
		
	return 0;
}
	
int CEpollSocket::RegisterEpollEventFunction(void* pFunction, const int iEventType)
{
	if(!pFunction)
	{
		return -1;
	}
	
	switch(iEventType)
	{
		case EPOLLIN:
		{
			m_fpEpollInputCallBackFunc = (EpollInputCallBackFunction)pFunction;
			break;
		}
	}

	return 0;
}				
		
