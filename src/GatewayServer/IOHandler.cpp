#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include "ComponentManager.hpp"
#include "IOHandler.hpp"
#include "IOUtility.hpp"
#include "Log.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "EventManager.hpp"
#include "GatewayServer.hpp"

void OnAccept(int iFd, short shEvent, void* pArg)
{
	struct sockaddr_in stInAddr;
    int iNewfd = 0;
    socklen_t iSinSize = sizeof(struct sockaddr_in);

    iNewfd = accept(iFd, (struct sockaddr*)&stInAddr, &iSinSize);
	if (-1 == iNewfd)
	{
		LOG_ERROR("accept fail. ip:%s, errno:%d\n", inet_ntoa(stInAddr.sin_addr), errno);
		return;
	}

	//set nonblocking
	CIOUtility::SetNonblocking(iNewfd);

	//set nonnagle
	CIOUtility::SetNonNagle(iNewfd);

	CEventManager& rEventManager = CComponentManager::GetGatewayServer()->GetEventManager();
	int iRt = rEventManager.AddSocket(iNewfd, CEventManager::EVENT_READ, OnRead, NULL, true);
	if (iRt != 0)
	{
		LOG_ERROR("add fd to eventmanager fail. ip:%s, rt:%d\n", inet_ntoa(stInAddr.sin_addr), iRt);
		return;
	}

	LOG_INFO("client %s connect.\n", inet_ntoa(stInAddr.sin_addr));	
}

void OnRead(int iFd, short shEvent, void* pArg)
{
	int const  MAX_READ_BUFFER_SIZE = 1000000;
	static char szReadBuffer[MAX_READ_BUFFER_SIZE];
	
	int iCount = read(iFd, szReadBuffer, sizeof(szReadBuffer));
	if (iCount != 0)
	{
		szReadBuffer[iCount] = 0;
		printf("recv(%d): %s\n", iCount, szReadBuffer);
	}
}
