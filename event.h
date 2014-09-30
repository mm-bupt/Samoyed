/*
 * =====================================================================================
 *		COPYRIGHT:  Copyright(C) 2007-2015 Neusoft
 *       FILENAME:  event.h
 *        VERSION:  1.0
 *         AUTHOR:  maming (), ma.ming@neusoft.com
 *			 DATE:  09/30/2014 03:04:53 PM
 *    DESCRIPTION:  
 * -------------------------------------------------------------------------------------
 * CHANGE HISTORY:
 * DATE				REV		WHO			DESCRIPTION
 *
 * =====================================================================================
 */

#ifndef _EVENT_H_
#define _EVENT_H_


#define EPOLL_CONTINUE		0
#define EPOLL_RELOAD		1
#define EPOLL_STOP			2

typedef int (*mm_epoll_callback)(struct epoll_event *pstEvent);

extern int MM_Epoll_Init(void);

extern int MM_Epoll_Add(int iFd, mm_epoll_callback ptr, uint32_t ui32Data, uint64_t ui64Data);
extern int MM_Epoll_Wait(void);
extern void MM_Epoll_Delete(int iFd);

#endif
