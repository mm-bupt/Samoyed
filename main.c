/*
 * =====================================================================================
 *		COPYRIGHT:  Copyright(C) 2007-2015 Neusoft
 *       FILENAME:  main.c
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
#include "message.h"

int main(int argc, char *argv[])
{
	MM_Epoll_Init();
	MM_MSG_Init();	
	MM_Epoll_Wait();
}
