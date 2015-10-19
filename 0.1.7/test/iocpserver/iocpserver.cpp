#include "netsvc_init.h"
#include "server_handler.h"
#include "tcp_service.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout<<"usage: iocpserver <local port> <work number> <local ip1> <local ip2> <...>"<<endl;
		return -1;
	}

	unsigned short port = (unsigned short) atoi(argv[1]);
	int worknum = atoi(argv[2]);

	if(argc == 3)
	{
		netsvc::tcp_accepter<server_handler> *acpter = new netsvc::tcp_accepter<server_handler>();
		//int err = acpter->start(port, worknum);
		int err = acpter->start(port, worknum, NULL, 1000);
		if(err != 0)
		{
			cout<<"start iocpserver failed on port: "<<port<<endl;
			return -1;
		}
		cout<<"start iocpserver on port: "<<port<<", work number: "<<worknum<<endl;

		Sleep(10*1000);
		cout<<"Look! I'm going to stop the server!"<<endl;
		acpter->stop();
		cout<<"Look! I have stopped the server!"<<endl;
	}
	else
	{
		for(int i=3; i<argc; i++)
		{
			unsigned int localip = ntohl(inet_addr(argv[i]));
			netsvc::tcp_accepter<server_handler> *acpter = new netsvc::tcp_accepter<server_handler>();
			//int err = acpter->start(localip, port, worknum);
			int err = acpter->start(localip, port, worknum, NULL,1000);
			if(err != 0)
			{
				cout<<"start iocpserver failed on local: "<<argv[i]<<":"<<port<<endl;
				return -1;
			}

			cout<<"start iocpserver on local: "<<argv[i]<<":"<<port<<", work number: "<<worknum<<endl;

			Sleep(10*1000);
			cout<<"Look! I'm going to stop the server!"<<endl;
			acpter->stop();
			cout<<"Look! I have stopped the server!"<<endl;
		}
	}

	while (true)
		Sleep(1000);

	return 0;
}