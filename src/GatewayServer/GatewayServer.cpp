#include "GatewayServer.hpp"

CGatewayServer::CGatewayServer()
{
}


int CGatewayServer::Init(const char* pszIpAddr, const unsigned short usPort)
{
	int iRet;
	iRet = m_stListenSocket.Init(pszIpAddr, usPort, false);
	if(iRet != 0)
	{
		LOG_ERROR("Error: init listen socket fail. en:%d\n", iRet);
		return -1;
	}

	return iRet;
}

int CGatewayServer::Run()
{
	int iRet;

	return iRet;
}
