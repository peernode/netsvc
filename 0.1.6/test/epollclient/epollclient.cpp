#include "client_handler.h"
#include "tcp_service.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		cout<<"usage: epollclient <remote ip> <remote port> <concurrence>"<<endl;
		return -1;
	}

	unsigned int ip =ntohl(inet_addr(argv[1]));
	unsigned short port = (unsigned short) atoi(argv[2]);
	int num = atoi(argv[3]);	

	netsvc::epoll_connector<client_handler> _connector;
	int err = _connector.start(1);
	if(err != 0)
	{
		cout<<"start connector failed."<<endl;
		return -1;
	}
	int i=0;
	while(i++<num)
	{
		err = _connector.connect(ip, port, 0);
		if(err != 0)
		{
			cout<<"connect failed."<<endl;
			return -1;
		}
	}
	while (true)
		sleep(1);

	return 0;
}

