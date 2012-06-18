#include "ComponentManager.hpp"

CGatewayServer* CComponentManager::m_pGatewayServer  = 0;

CGatewayServer* CComponentManager::GetGatewayServer()
{
	return m_pGatewayServer;
}


void CComponentManager::SetGatewayServer(CGatewayServer* pGatewayServer)
{
	m_pGatewayServer = pGatewayServer;
}
