#include "Connection.hpp"
#include "GatewayServer.hpp"
#include "Log.hpp"
#include "IOHandler.hpp"

int CGatewayServer::Init()
{
	int iRt = 0;

	//init log first
	iRt = CSingleton<CLog>::Instance()->Init("GatewayServer.log");
	if (iRt != 0)
	{
		return -1;
	}
	
	iRt = m_stEventManager.Init();
	if (iRt != 0)
	{
		LOG_ERROR("init eventmanager fail. rt:%d\n", iRt);
		return -3;
	}

	iRt = m_stConnectionManager.Init("127.0.0.1", 8888);
	if (iRt != 0)
	{
		LOG_ERROR("init connectionmanager fail. rt:%d\n", iRt);
		return -5;
	}

	//add listener connection to event
	const CConnection& rListenerConnection = m_stConnectionManager.GetListenerConnection();
	iRt = m_stEventManager.AddSocket(rListenerConnection.GetSocketID(), CEventManager::EVENT_READ, OnAccept, NULL, true);
	if (iRt != 0)
	{
		LOG_ERROR("eventmanager add socket fail. rt:%d\n", iRt);
		return -7;
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
