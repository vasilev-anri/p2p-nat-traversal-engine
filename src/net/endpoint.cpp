#include "endpoint.h"

#include <arpa/inet.h>

Endpoint sockaddr_to_endpoint(const sockaddr_in& addr) {
    char buff[INET_ADDRSTRLEN]{};

    inet_ntop(AF_INET, &addr.sin_addr, buff, sizeof(buff));

    return {std::string(buff), ntohs(addr.sin_port)};
}
