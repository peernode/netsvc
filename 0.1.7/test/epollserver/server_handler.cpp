#include "server_handler.h"


server_handler::server_handler():_resp("")
{
}

server_handler::~server_handler(void)
{
}

int server_handler::handle_open(void *arg)
{
	return 0;
}

int server_handler::handle_send()
{
	if(_resp.empty())
		return 0;

	int sz = send(_resp.c_str(), _resp.length(), 0);
	return -1;
}

int server_handler::handle_recv()
{
	const int bufsz = 2048;
	char buf[bufsz] = {0};
	
	int sz = recv(buf, bufsz, 0);
	
	while(sz > 0)
	{
		_resp.append(buf,sz);
		sz = recv(buf, bufsz, 0);

	}

	return 0;
}

int server_handler::handle_close()
{
	return -1;
}

int server_handler::handle_run(time_t tm)
{
	return 0;
}
