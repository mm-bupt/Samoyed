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

int main()
{
	int iRet;
	int iSocket;
	char *buf = "11111111";
	struct sockaddr_in server_addr;
	struct addr *addr;

	iSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (iSocket != -1)
	{
		memset(&server_addr, 0, sizeof(&server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(10005); 
		server_addr.sin_addr.s_addr = htonl(2130706433);
		iRet = connect(iSocket, (struct sockaddr *)&server_addr, sizeof(server_addr));
	printf("1");	
		sendto(iSocket, buf, strlen(buf) + 1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
	printf("1");	
		return 0;
	}

	return 0;
}
