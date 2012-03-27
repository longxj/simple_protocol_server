#include "GatewayServer.hpp"

int CGatewayServer::Init()
{
	int iRt = 0;
	iRt = m_stEventManager.Init();
	if (iRt != 0)
	{
		return -1;
	}

	return 0;
}

int CGatewayServer::Run()
{
	while (true)
	{
		m_stEventManager.Dispatch();
	}

	return 0;
}
