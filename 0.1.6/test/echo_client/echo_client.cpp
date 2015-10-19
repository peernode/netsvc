#ifdef WIN32
#include <WinSock2.h>
#else
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cout<<"Usage: echo_client <server ip> <server port> <echo string>"<<endl;
		return -1;
	}

	unsigned int sip = ntohl(inet_addr(argv[1]));
	unsigned short sport = atoi(argv[2]);
	char *str = argv[3];

#ifdef WIN32
	/*start up windows socket environment*/
	WORD wsaversion;
	WSADATA wsadata;
	wsaversion = MAKEWORD( 2, 2 );

	int err = WSAStartup(wsaversion, &wsadata);
	if ( err != 0 ) 
	{ //startup windows socket environment failed.
		std::cerr<<"windows socket startup failed, error: "<<WSAGetLastError()<<std::endl;
		exit(1);
	}

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock == INVALID_SOCKET)
		return -1;

	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(sip);
	saddr.sin_port = htons(sport);

	err = sendto(sock, str, strlen(str), 0, (struct sockaddr*)&saddr, sizeof(saddr));
	if(err == SOCKET_ERROR)
	{
		cout<<"send data to "<<argv[1]<<":"<<sport<<" failed. error:"<<WSAGetLastError()<<endl;
		return -1;
	}
	cout<<"echo send: "<<str<<endl;

	char buf[2048] = {0};
	struct sockaddr_in raddr;
	memset(&raddr, 0, sizeof(raddr));
	int raddr_len = sizeof(raddr);
	int rcvsz = recvfrom(sock, buf, 2048, 0, (struct sockaddr*)&raddr, &raddr_len);
	if(rcvsz < 0)
	{
		cout<<"recv data from "<<argv[1]<<":"<<sport<<" failed. error:"<<WSAGetLastError()<<endl;
		return -1;
	}

	cout<<"echo recv: "<<buf<<endl;

	WSACleanup();
#else
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock == -1)
		return -1;

	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(sip);
	saddr.sin_port = htons(sport);
	int err = sendto(sock, str, strlen(str), 0, (struct sockaddr*)&saddr, sizeof(saddr));
	if(err == -1)
	{
		cout<<"send data to "<<argv[1]<<":"<<sport<<" failed. error:"<<errno<<endl;
		return -1;
	}
	cout<<"echo send: "<<str<<endl;

	char buf[2048] = {0};
	struct sockaddr_in raddr;
	memset(&raddr, 0, sizeof(raddr));
	int raddr_len = sizeof(raddr);
	int rcvsz = recvfrom(sock, buf, 2048, 0, (struct sockaddr*)&raddr, &raddr_len);
	if(rcvsz < 0)
	{
		cout<<"recv data from "<<argv[1]<<":"<<sport<<" failed. error:"<<errno<<endl;
		return -1;
	}

	cout<<"echo recv: "<<buf<<endl;
#endif

	return 0;
}