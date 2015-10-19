#pragma once
#include "udp_service.h"

class echo_handler : public netsvc::udp_handler
{
public:
	echo_handler(void);
	virtual ~echo_handler(void);

	virtual int handle(netsvc::dpacket_t *req, void *arg=NULL);
};
