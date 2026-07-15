#ifndef P2P_NAT_CONNECTION_INFO_H
#define P2P_NAT_CONNECTION_INFO_H

#include "../net/endpoint.h"
#include "../utils/UniqueFD.h"

struct ConnectionInfo {
    UniqueFD fd;
    Endpoint local_endpoint;
    Endpoint remote_endpoint;
};

#endif //P2P_NAT_CONNECTION_INFO_H