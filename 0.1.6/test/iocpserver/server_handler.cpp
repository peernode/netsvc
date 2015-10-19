#include "server_handler.h"
#include <iostream>


server_handler::server_handler():_resp("")
{
}

server_handler::~server_handler(void)
{
}

int server_handler::on_open(void *arg)
{
	int err = async_recv(2048);
	if(err < 0)
		return -1;
	return 0;
}

int server_handler::on_send(int sz_send)
{
	return -1;
}

int server_handler::on_recv(const char *data, int sz_recv)
{
	int err = async_send(data, sz_recv);
	if(err < 0)
		return -1;
	return 0;
}

int server_handler::on_error(int err)
{
	return -1;
}

int server_handler::on_close()
{
	return -1;
}

int server_handler::on_running(time_t tm)
{
	return 0;
}
