/*
 *@file EventManager.hpp
 *@brief manager all the event that a application need
 *@author seanlong
 *@date 2012年 03月 27日 星期二 16:32:40 CST
 *@version 1.0
 *add, remove event handler
 */

#ifndef __EVENTMANAGER_HPP
#define __EVENTMANAGER_HPP

#include <event2/event.h>

typedef void (*Event_Function)(int, short, void*);

/*
 *@class
 *@brief mananger all the event
 *@author seanlong
 */
class CEventManager
{
public:
	static const short EVENT_READ;
	static const short EVENT_WRITE;
	
private:
	struct event_base* m_pEventBase;

public:
	/*
	 *@brief init eventmanager
	 *@author seanlong
	 *@return 0 if success or negative
	 */
	int Init();

	/*
	 *@brief add a timer
	 *@author seanlong
	 *@param[in] rTimeval time when timer is up
	 *@param[in] pFunction function to call when timer is up
	 *@param[in] pArg argument to pass to pFucntion
	 *@param[in] bIsPersistent whether the timer will persist
	 *@return 0 if success or negative
	 */
	int AddTimer(const struct timeval& rTimeval, Event_Function pFunction, void* pArg, const bool bIsPersistent = false);

	/*
	 *@brief add a signal
	 *@author seanlong
	 *@param[in] shSignal signal id to add
	 *@param[in] pFunction function to call when signal occurs
	 *@param[in] pArg argument to pass to pFucntion
	 *@param[in] bIsPersistent whether the signal event will persist
	 *@return 0 if success or negative
	 */
	int AddSignal(const int iSignal, Event_Function pFunction, void* pArg, const bool bIsPersistent = false);

	/*
	 *@brief add a socket
	 *@author seanlong
	 *@param[in] iSockID socket id to add
	 *@param[in] shEvent event interested
	 *@param[in] pFunction function to call when event occurs
	 *@param[in] pArg argument to pass to pFucntion
	 *@param[in] bIsPersistent whether the event will persist
	 *return 0 if success or negative
	 */
	int AddSocket(const int iSockID, const short shEvent, Event_Function pFunction, void* pArg, const bool bIsPersistent = false);

	/*
	 *@brief dispatch msg
	 *@author seanlong
	 *@return 0 if success or negative
	 */
	int Dispatch();
};

#endif
