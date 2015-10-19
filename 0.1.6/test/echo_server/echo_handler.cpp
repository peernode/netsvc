#include "echo_handler.h"

echo_handler::echo_handler(void)
{
}

echo_handler::~echo_handler(void)
{
}

int echo_handler::handle(netsvc::dpacket_t *req, void *arg)
{
	sendto(req->addr(), req->rptr(), req->dsz());
	return 0;
}
