#include "fts_handler.h"

fts_handler::fts_handler(SOCKET s, struct sockaddr_in* remote_addr, void *arg):
iocp_handler(s, remote_addr, arg),
_fname(""),
_size(0),
_buff(""),
_header_finished(false)
{
}

fts_handler::~fts_handler(void)
{
}

int fts_handler::on_open()
{
	int err = async_recv(2048, NULL);
	if(err < 0)
		return -1;
	return 0;
}

int fts_handler::on_send(int sz_send, void *olptr)
{
	return 0;
}

int fts_handler::on_recv(const char *data, int sz_recv, void *olptr)
{
	if(_header_finished)
	{
		_fwriter.write(data, sz_recv);
		if(_fwriter.fail())
			return -1;
	}
	else
	{
		_buff.append(data, sz_recv);
		if(_buff.size() > 4)
		{
			int head_len = ntohl((*(int*)_buff.c_str()));
			if(_buff.size() < head_len)
				return 0;

			/*header has received*/
			_size = ntohl((*(int*)(_buff.c_str()+4))); //file size
			_fname = string(_buff.c_str()+8, head_len-8);

			/*open the file writer stream*/
			_fwriter.open(_fname.c_str(), ios_base::binary|ios_base::out);
			if(!_fwriter.good())
				return -1;

			/*write the file data*/
			if(_buff.size() > head_len)
			{
				_fwriter.write(_buff.c_str()+head_len, _buff.size()-head_len);
				if(_fwriter.fail())
					return -1;
			}

			_header_finished = true;
		}
	}

	int err = async_recv(2048, NULL);
	if(err < 0)
		return -1;

	return 0;
}

int fts_handler::on_close()
{
	return 0;
}

int fts_handler::on_running(time_t tm)
{
	return 0;
}

