#include <iostream>
#include <stdio.h>
#include <time.h>
#include <WinSock2.h>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		cout<<"Usage: ftc <ip> <port> <file>"<<endl;
		return -1;
	}

	/*start up windows socket environment*/
	WORD wsaversion;
	WSADATA wsadata;

	wsaversion = MAKEWORD( 2, 2 );

	int err = WSAStartup(wsaversion, &wsadata);
	if ( err != 0 ) 
		return -1; //startup windows socket environment failed.

	/*create socket*/
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET)
	{
		cout<<"create socket failed."<<endl;
		return -1;
	}

	/*bind remote address*/
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));

	/*connect to remote server*/
	err = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if(err != 0)
	{
		cout<<"connect to remote server failed."<<endl;
		return -1;
	}

	/*get file path & name*/
	string fpath(argv[3]);
	string fname("");
	size_t pos = fpath.find_last_of("\\/");
	if(pos == string::npos)
		fname = fpath;
	else
		fname = fpath.substr(pos+1);

	/*open the file and get the file size*/
	FILE *f = fopen(fpath.c_str(), "rb");
	if(f == NULL)
	{
		cout<<"open file for read failed."<<endl;
		return -1;
	}

	err = fseek(f, 0,SEEK_END);
	if(err != 0)
	{
		cout<<"seek to end of the file failed."<<endl;
		return -1;
	}

	long file_sz = ftell(f);
	if(file_sz == -1L)
	{
		cout<<"get file file size failed."<<endl;
		return -1;
	}

	err = fseek(f, 0, SEEK_SET);
	if(err != 0)
	{
		cout<<"seek to head of the file failed."<<endl;
		return -1;
	}


	/*send buffer*/
	const int buf_sz = 16*1024;
	char buf[buf_sz] = {0};

	/*send header*/
	int head_sz = 8+fname.size();
	*(int*)buf = htonl(head_sz);
	*(int*)(buf+4) = htonl(file_sz);
	memcpy(buf+8, fname.c_str(), fname.size());

	int total_snd = 0;
	int snd_sz = send(sock, buf, head_sz, 0);
	if(snd_sz != head_sz)
	{
		cout<<"send failed."<<endl;
		return -1;
	}
	total_snd += snd_sz;

	time_t start_time = time(NULL);
	while(!feof(f))
	{
		int rd_sz = fread(buf, 1, buf_sz, f);
		snd_sz = send(sock, buf, rd_sz, 0);
		if(snd_sz <= 0)
		{
			cout<<"send failed."<<endl;
			break;
		}

		total_snd += snd_sz;
	}

	closesocket(sock);
	fclose(f);
	time_t end_time = time(NULL);
	cout<<"send finished. total time: "<<end_time-start_time<<" s, avg speed: "
		<<total_snd/1024/(end_time-start_time)<<" KB/s"<<endl;

	WSACleanup();
	return 0;
}
