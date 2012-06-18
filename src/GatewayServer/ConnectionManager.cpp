#include "ConnectionManager.hpp"
#include <sys/types.h> 
#include <sys/socket.h>
#include "Log.hpp"
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <stdio.h>


int CConnectionManager::Init(const char* pAddr, const unsigned short ushPort)
{
	//clear pool
	m_stConnectionPool.clear();

	int iRt = 0;
	
	int iSockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (iSockFd == -1)
	{
		LOG_ERROR("create socket fail. errno:%d %s\n", errno, strerror(errno));
		return -1;
	}

	/* Init sockaddr_in */
	struct sockaddr_in stMyAddr;
	memset(&stMyAddr, 0, sizeof(stMyAddr));
	
	stMyAddr.sin_family = AF_INET;   
	stMyAddr.sin_port = htons(ushPort); 
	stMyAddr.sin_addr.s_addr = inet_addr(pAddr);
	
	iRt = bind(iSockFd, (struct sockaddr*)&stMyAddr, sizeof(struct sockaddr));
	if (iRt == -1)
	{
		LOG_ERROR("bind socket fail. errno:%d %s\n", errno, strerror(errno));
		return -3;
	}

	iRt = listen(iSockFd, MAXCONNECTIONNUM);
	if (iRt == -1)
	{
		LOG_ERROR("listen socket fail. errno:%d %s\n", errno, strerror(errno));
		return -5;
	}

	//set the listening connection
	m_stListenerConnection.SetSocketID(iSockFd);

	return 0;
}
