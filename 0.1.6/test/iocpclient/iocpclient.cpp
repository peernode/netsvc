#include "netsvc_init.h"
#include "client_handler.h"
#include "tcp_service.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout<<"usage: iocpclient <remote ip> <remote port>"<<endl;
		return -1;
	}

	unsigned int ip =ntohl(inet_addr(argv[1]));
	unsigned short port = (unsigned short) atoi(argv[2]);

	netsvc::iocp_connector<client_handler> _connector;
	int err = _connector.start(1);
	if(err != 0)
	{
		cout<<"start connector failed."<<endl;
		return -1;
	}
	int i=0;
	while(i++<10)
	{
		err = _connector.connect(ip, port, 0);
		if(err != 0)
		{
			cout<<"connect failed."<<endl;
			return -1;
		}
	}
	while (true)
		Sleep(1000);

	return 0;
}