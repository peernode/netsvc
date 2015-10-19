#pragma once
#include "iocp_handler.h"
#include <string>
#include <fstream>

using namespace std;
/*
*protocol:
*		header + file content
*	header: header size(4B) + file size(8B) + file name(string)
*/
class fts_handler :	public iocp_handler
{
public:
	fts_handler(SOCKET s, struct sockaddr_in* remote_addr, void *arg = NULL);
	virtual ~fts_handler(void);

	virtual int on_open();
	virtual int on_send(int sz_send, void *olptr);
	virtual int on_recv(const char *data, int sz_recv, void *olptr);
	virtual int on_close();
	virtual int on_running(time_t tm);

private:
	//header header transfer finished flag
	bool _header_finished;
	//file name
	string _fname;
	//file size
	int _size;

	//temp buffer for receive header
	string _buff;

	//file write stream
	ofstream _fwriter;
};

