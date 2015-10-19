#include "server_handler.h"
#include "tcp_service.h"

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout<<"usage: epollserver <local port> <work number> <local ip1> <local ip2> <...>"<<endl;
		return -1;
	}

	unsigned short port = (unsigned short) atoi(argv[1]);
	int worknum = atoi(argv[2]);
	
	if(argc == 3)
	{
		netsvc::epoll_accepter<server_handler> *acpter = new netsvc::epoll_accepter<server_handler>();
		int err = acpter->start(port, worknum);
		if(err != 0)
		{
			cout<<"start epollserver failed on port: "<<port<<endl;
			return -1;
		}
		cout<<"start epollserver on port: "<<port<<", work number: "<<worknum<<endl;
	}
	else
	{
		for(int i=3; i<argc; i++)
		{
			unsigned int localip = ntohl(inet_addr(argv[i]));
			netsvc::epoll_accepter<server_handler> *acpter = new netsvc::epoll_accepter<server_handler>();
			int err = acpter->start(localip, port, worknum);
			if(err != 0)
			{
				cout<<"start epollserver failed on local: "<<argv[i]<<":"<<port<<endl;
				return -1;
			}
			
			cout<<"start epollserver on local: "<<argv[i]<<":"<<port<<", work number: "<<worknum<<endl;
		}
	}

	while (true)
		sleep(1);

	return 0;
}
