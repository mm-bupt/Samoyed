/*
 * =====================================================================================
 *		COPYRIGHT:  Copyright(C) 2007-2015 Neusoft
 *       FILENAME:  message.c
 *        VERSION:  1.0
 *         AUTHOR:  maming (), ma.ming@neusoft.com
 *			 DATE:  09/30/2014 03:11:20 PM
 *    DESCRIPTION:  
 * -------------------------------------------------------------------------------------
 * CHANGE HISTORY:
 * DATE				REV		WHO			DESCRIPTION
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <errno.h>
#include <netinet/in.h>
#include "mm_basetype.h"
#include "event.h"
#include "message.h"

static int giListenSock;

int MM_MSG_RecvMsg(struct epoll_event *pstEvent)
{
	char acBuf[4096];
	int iRecvNum;

	if (EPOLLIN & pstEvent->events)
	{
		while ((iRecvNum = recv(pstEvent->data.fd, acBuf, sizeof(acBuf), MSG_DONTWAIT)) > 0)
		{
			printf("%s\r\n", acBuf);	
		}
		printf("ReadOver %d, %d\r\n", iRecvNum, errno);
		if (iRecvNum < 0)
		{
			if (errno == ECONNRESET || errno == ETIMEDOUT)
			{
				MM_Epoll_Delete(pstEvent->data.fd);
				close(pstEvent->data.fd);
			}
		}
		else if (iRecvNum == 0)
		{
			MM_Epoll_Delete(pstEvent->data.fd);
			close(pstEvent->data.fd);
		}

	}

	return EPOLL_CONTINUE;
}

int MM_MSG_Accept(struct epoll_event *pstEvent)
{
	int iNewSock = -1;
	struct sockaddr_in client_addr;  
	socklen_t clilen = sizeof(struct sockaddr);   

	if (EPOLLIN & pstEvent->events)
	{
		memset(&client_addr, 0, sizeof(client_addr));  

		iNewSock = accept(pstEvent->data.fd, (struct sockaddr*)&client_addr, &clilen);  
		if (-1 == iNewSock)
		{
			return EPOLL_CONTINUE;
		}
	
		if (ERROR_SUCCESS != MM_Epoll_Add(iNewSock, MM_MSG_RecvMsg, 0, 0))
		{
			close(iNewSock);
		}
	}

	return EPOLL_CONTINUE;
}

int MM_MSG_Init(void)
{
	int iSocket;
	unsigned long ulRet;
	struct sockaddr_in server_addr; 
    
	ulRet = ERROR_FAILED;
	iSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(iSocket != -1) 
    {
		memset(&server_addr, 0, sizeof(&server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(10005); 
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		if(bind(giListenSock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != -1)
		{
			if(listen(giListenSock, 5) != -1)
			{
				ulRet = MM_Epoll_Add(giListenSock, MM_MSG_Accept, 0, 0);
			}
		}
	}
    
	return ulRet;
}



