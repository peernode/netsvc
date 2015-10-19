#include "client_handler.h"


client_handler::client_handler()
{
	_req = string("hello");
}

client_handler::~client_handler(void)
{
}

int client_handler::handle_open(void *arg)
{
	cout<<"open."<<endl;
	return 0;
}

int client_handler::handle_send()
{
	int sz = send(_req.c_str(), _req.length(), 0);
	cout<<"send bytes:"<<sz<<endl;
//	sz = send(_req.c_str(), _req.length(), 0);
//	cout<<"send bytes2:"<<sz<<endl;
	return 0;
}

int client_handler::handle_recv()
{
	char buf[256] = {0};

	int sz = recv(buf, 256, 0);
	cout<<"recv bytes: "<<sz<<endl;

	return 0;
}

int client_handler::handle_close()
{
	cout<<"close."<<endl;
	return -1;
}

int client_handler::handle_run(time_t tm)
{
	return 0;
}

