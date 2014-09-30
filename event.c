/*
 * =====================================================================================
 *		COPYRIGHT:  Copyright(C) 2007-2015 Neusoft
 *       FILENAME:  event.c
 *        VERSION:  1.0
 *         AUTHOR:  maming (), ma.ming@neusoft.com
 *			 DATE:  09/30/2014 10:08:16 AM
 *    DESCRIPTION:  
 * -------------------------------------------------------------------------------------
 * CHANGE HISTORY:
 * DATE				REV		WHO			DESCRIPTION
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/epoll.h>
#include "mm_basetype.h"
#include "event.h"

#define MAX_EPOLL_EVENT      10000
#define HANDLE_EPOLL_EVENT   100

int giEpollFd = -1;

int MM_Epoll_Init(void)
{
	int iEpoll;
	if (-1 != giEpollFd)
	{
		return ERROR_SUCCESS;
	}

	iEpoll = epoll_create(MAX_EPOLL_EVENT);	
	if (-1 != iEpoll)
	{
		giEpollFd = iEpoll;
		return ERROR_SUCCESS;
	}

	return ERROR_FAILED;
}

int MM_Epoll_Add(int iFd, mm_epoll_callback ptr, uint32_t ui32Data, uint64_t ui64Data)
{
	struct epoll_event stEvent;
	if (-1 == giEpollFd)
	{
		return ERROR_FAILED;
	}

	stEvent.data.ptr = ptr;
	stEvent.data.fd = iFd;
	stEvent.data.u32 = ui32Data;
	stEvent.data.u64 = ui64Data;
	stEvent.events = EPOLLIN;

	epoll_ctl(giEpollFd, EPOLL_CTL_ADD, iFd, &stEvent);	
}

int MM_Epoll_Wait(void)
{
	int i, iNfds, iRet, iLoop;
	struct epoll_event astEvent[10];
	mm_epoll_callback func = NULL;

	if (-1 == giEpollFd)
	{
		return ERROR_FAILED;
	}

	iLoop = 1;

	while (iLoop)
	{
		iNfds = epoll_wait(giEpollFd, astEvent, 10, -1);
		if (iNfds <= 0)
		{
			continue;	
		}
		for (i = 0; i < iNfds; i++)
		{
			func = (mm_epoll_callback)astEvent[i].data.ptr; 
			iRet = func(&astEvent[i]);
			if (iRet == EPOLL_RELOAD)
			{
				break;
			}
			else if (iRet == EPOLL_STOP)
			{
				iLoop = 0;
				break;
			}
		}	
	}

	return ERROR_SUCCESS;
}

void MM_Epoll_Delete(int iFd)
{
	struct epoll_event stEvent;

	if (-1 == giEpollFd)
	{
		return;
	}

	stEvent.data.fd = iFd;
	stEvent.events = EPOLLERR;

	epoll_ctl(giEpollFd, EPOLL_CTL_DEL, iFd, &stEvent);
}
