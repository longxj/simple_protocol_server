#include "GatewayServer.hpp"

int main()
{
	int iRet = 0;
	CGatewayServer stGatewayServer;
	iRet = stGatewayServer.Init();
	if(iRet < 0)
	{
		return iRet;
	}

	return iRet;
}
