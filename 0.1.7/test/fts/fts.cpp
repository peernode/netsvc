#include <iostream>
#include "netsvc_init.h"
#include "fts_handler.h"
#include "iocp_accepter.h"

using namespace std;
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout<<"Usage: fts <listen port>"<<endl;
		return -1;
	}

	unsigned short port = atoi(argv[1]);

	iocp_accepter<fts_handler> fts_accepter;
	int err = fts_accepter.start(port, 8);
	if(err != 0)
	{
		cout<<"start fts service failed."<<endl;
		return -1;
	}

	cout<<"start fts service success, listening on port: "<<port<<endl;
	while(true)
		Sleep(100000);

	return 0;
}
