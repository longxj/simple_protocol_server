#ifndef __CONNECTIONMANAGER_HPP
#define __CONNECTIONMANAGER_HPP

#include <hash_map>
#include "Connection.hpp"

class CConnectionManager
{
private:
	std::hash_map<int, CConnection> m_stConnectionPool;
	CConnection m_stListenerConnection;
};

#endif
