#ifndef __GATEWAYSERVER_HPP
#define __GATEWAYSERVER_HPP

#include "EventManager.hpp"
#include "ConnectionManager.hpp"

class CGatewayServer
{
private:
	CEventManager m_stEventManager;
	CConnectionManager m_stConnectionManager;

public:
	int Init();
	int Run();
};

#endif
