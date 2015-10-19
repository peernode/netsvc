#pragma once
#include "tcp_service.h"
#include <string>
using namespace std;
class client_handler :	public netsvc::iocp_handler
{
public:
	client_handler();
	virtual ~client_handler(void);

	virtual int on_open(void *arg);
	virtual int on_send(int sz_send, void *olptr);
	virtual int on_recv(const char *data, int sz_recv, void *olptr);
	virtual int on_close();

	virtual int on_running(time_t tm);

private:
	string _req;
};

