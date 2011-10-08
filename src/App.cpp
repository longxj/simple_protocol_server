#include "App.hpp"
#include "Log.hpp"
#include "Singleton.hpp"

int CApp::Init()
{
	int iRet = 0;
	//init the log
	iRet = CSingleton<CLog>::Instance()->Init("log.txt", CLog::LEVEL_DEBUG);
	if(iRet < 0)
	{
		return -1;
	}

	iRet = CSingleton<CGatewayServer>::Instance()->Init();
	if(iRet < 0)
	{
		LOG_ERROR("Error: Init GatewayServer Fail\n");
		return -2;
	}
}

int CApp::Run()
{
	int iRet = 0;
	iRet = CSingleton<CGatewayServer>::Instance()->Run();
	return iRet;
}
