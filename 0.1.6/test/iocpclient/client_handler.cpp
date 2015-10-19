#include "client_handler.h"
#include <iostream>


client_handler::client_handler()
{
	_req = "hello";
}

client_handler::~client_handler(void)
{
}

int client_handler::on_open(void *arg)
{
	cout<<"open."<<endl;
	int err = async_send(_req.c_str(), _req.length());
	if(err < 0)
		return -1;

	return 0;
}

int client_handler::on_send(int sz_send, void *olptr)
{
	cout<<"send bytes: "<<sz_send<<endl;
	int err = async_recv(512);
	if(err < 0)
		return -1;
	return 0;
}

int client_handler::on_recv(const char *data, int sz_recv, void *olptr)
{
	cout<<"recv bytes:"<<sz_recv<<endl;
	return -1;
}

int client_handler::on_close()
{
	cout<<"close"<<endl;
	return -1;
}

int client_handler::on_running(time_t tm)
{
	return 0;
}
