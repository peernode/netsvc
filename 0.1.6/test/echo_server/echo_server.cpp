#include <iostream>
#include "netsvc_init.h"
#include "udp_service.h"
#include "echo_handler.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 5){
		cout<<"Usage: \n"
		    <<"\techo_server <port> <thread number> <buffer size> <queue size> <ip1> <ip...>"<<endl;
		return -1;
	}

	unsigned short port = atoi(argv[1]);
	int thread_num = atoi(argv[2]);
	int buff_sz = atoi(argv[3]);
	int qsize = atoi(argv[4]);

	


	if(argc==5)
	{
		netsvc::udp_service<echo_handler> *service = new netsvc::udp_service<echo_handler>();
		service->set_max_psz(buff_sz);
		service->set_max_qsz(qsize);
		int err = service->start(port, thread_num);
	
		if(err != 0){
			cout<<"start service failed on: "<<"0.0.0.0:"<<port<<", thread number: "<<thread_num<<", buffer: "<<buff_sz<<", queue size: "<<qsize<<endl;
			return -1;
		}
		else{
			cout<<"start service success on: "<<"0.0.0.0:"<<port<<", thread number: "<<thread_num<<", buffer: "<<buff_sz<<", queue size: "<<qsize<<endl;
		}
	}
	else
	{
		for(int i=5; i<argc; i++)
		{
			unsigned int ip = ntohl(inet_addr(argv[i]));
			netsvc::udp_service<echo_handler> *service = new netsvc::udp_service<echo_handler>();
			service->set_max_psz(buff_sz);
			service->set_max_qsz(qsize);
			int err = service->start(ip, port, thread_num);
	
			if(err != 0){
				cout<<"start service failed on: "<<argv[i]<<":"<<port<<", thread number: "<<thread_num<<", buffer: "<<buff_sz<<", queue size: "<<qsize<<endl;
				return -1;
			}
			else{
				cout<<"start service success on: "<<argv[i]<<":"<<port<<", thread number: "<<thread_num<<", buffer: "<<buff_sz<<", queue size: "<<qsize<<endl;
			}
		}
	}



	while(true){
#ifdef _WIN32
		Sleep(10000);
#else
		sleep(10);
#endif	
	}

	return 0;
}

