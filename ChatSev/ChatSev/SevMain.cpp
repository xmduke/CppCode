#pragma once

#include <stdio.h>
#include <tchar.h>
#include "SevConn.h"
int _tmain(int argc, _TCHAR* argv[])
{
	CSevConn sevConn;
	sevConn.init();
	sevConn.start("127.0.0.1", 9999);

	WaitForSingleObject(sevConn.m_hAcceptThread, INFINITE);
	sevConn.exitSev(sevConn.m_ClientSock);
	return 0;
}