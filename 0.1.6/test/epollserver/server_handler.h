#pragma once
#include "tcp_service.h"
#include <string>
#include <iostream>
using namespace std;

class server_handler : public netsvc::epoll_handler
{
public:
	server_handler();
	virtual ~server_handler(void);

	virtual int handle_open(void *arg);
	virtual int handle_send();
	virtual int handle_recv();
	virtual int handle_close();
	virtual int handle_run(time_t tm);

private:
	string _resp;
};

