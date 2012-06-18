#ifndef __GATEWAYSERVER_HPP
#define __GATEWAYSERVER_HPP

#include "EventManager.hpp"
#include "ConnectionManager.hpp"

class CGatewayServer
{
public:
	CEventManager& GetEventManager() {return m_stEventManager;}
	CConnectionManager& GetConnectionManager() {return m_stConnectionManager;}
	
private:
	CEventManager m_stEventManager;
	CConnectionManager m_stConnectionManager;

public:
	int Init();
	int Run();
};

#endif
