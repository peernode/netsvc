#pragma once
#include "tcp_service.h"
#include <string>
using namespace std;
class server_handler :	public netsvc::iocp_handler
{
public:
	server_handler();
	virtual ~server_handler(void);

	virtual int on_open(void *arg);
	virtual int on_send(int sz_send);
	virtual int on_recv(const char *data, int sz_recv);
	virtual int on_error(int err);
	virtual int on_close();

	virtual int on_running(time_t tm);

private:
	string _resp;
};