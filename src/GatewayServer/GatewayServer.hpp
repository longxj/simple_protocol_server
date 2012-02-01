#ifndef __GATEWAYSERVER_HPP
#define __GATEWAYSERVER_HPP

class CGatewayServer
{
public:
	CGatewayServer();

	int Init(const char* szServerAddr, const unsigned short usPort);
	int Run();

private:
	EpollSocket m_stListenSocket;
};
#endif
