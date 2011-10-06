#include "GatewayServer.hpp"

int main()
{
	int iRet = 0;
	GatewayServer stGatewayServer;
	iRet = stGatewayServer.Init();
	if(iRet < 0)
	{
		return iRet;
	}

	return iRet;
}
