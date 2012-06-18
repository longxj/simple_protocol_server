#ifndef __COMPONENTMANAGER_HPP
#define __COMPONENTMANAGER_HPP

class CGatewayServer;

class CComponentManager
{
public:
	static CGatewayServer* GetGatewayServer();
	static void SetGatewayServer(CGatewayServer* pGatewayServer);
	
public:
	static CGatewayServer*  m_pGatewayServer;
};
	
#endif
