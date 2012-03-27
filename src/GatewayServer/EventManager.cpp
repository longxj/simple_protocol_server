#include "EventManager.hpp"

const short CEventManager::EVENT_READ = EV_READ;
const short CEventManager::EVENT_WRITE = EV_WRITE;

int CEventManager::Init()
{
	//init the event_base 
	m_pEventBase = event_base_new();
	if (m_pEventBase)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


int CEventManager::AddTimer(const struct timeval& rTimeval, Event_Function pFunction, void* pArg, const bool bIsPersistent)
{
	struct event* pEvent = NULL;
	if (bIsPersistent)
	{
		pEvent = event_new(m_pEventBase, -1, EV_PERSIST, pFunction, pArg);
	}
	else
	{
		pEvent = event_new(m_pEventBase, -1, 0, pFunction, pArg);
	}

	if (!pEvent)
	{
		return -1;
	}

	int iRt = event_add(pEvent, &rTimeval);
	if (iRt != 0)
	{
		return -6;
	}

	return 0;
}

int CEventManager::AddSignal(const int iSignal, Event_Function pFunction, void* pArg, const bool bIsPersistent)
{
	struct event* pEvent = NULL;
	if (bIsPersistent)
	{
		pEvent = event_new(m_pEventBase, iSignal, EV_SIGNAL | EV_PERSIST, pFunction, pArg);
	}
	else
	{
		pEvent = event_new(m_pEventBase, iSignal, EV_SIGNAL, pFunction, pArg);
	}

	if (!pEvent)
	{
		return -1;
	}

	int iRt = event_add(pEvent, NULL);
	if (iRt != 0)
	{
		return -6;
	}

	return 0;
}

int CEventManager::AddSocket(const int iSockID, const short shEvent, Event_Function pFunction, void* pArg, const bool bIsPersistent)
{
	struct event* pEvent = NULL;
	if (bIsPersistent)
	{
		pEvent = event_new(m_pEventBase, iSockID, shEvent | EV_PERSIST, pFunction, pArg);
	}
	else
	{
		pEvent = event_new(m_pEventBase, iSockID, shEvent, pFunction, pArg);
	}

	if (!pEvent)
	{
		return -1;
	}

	int iRt = event_add(pEvent, NULL);
	if (iRt != 0)
	{
		return -6;
	}

	return 0;
}

int CEventManager::Dispatch()
{
	return event_base_dispatch(m_pEventBase);
}
	



