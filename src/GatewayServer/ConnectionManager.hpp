#ifndef __CONNECTIONMANAGER_HPP
#define __CONNECTIONMANAGER_HPP

#include <map>
#include "Connection.hpp"

class CConnectionManager
{
private:
	std::map<int, CConnection> m_stConnectionPool;
	CConnection m_stListenerConnection;

public:
	static const int MAXCONNECTIONNUM = 100;
	
public:
	int Init(const char* pAddr, const unsigned short ushPort);
};

#endif
