#ifndef P2P_NAT_HELLO_H
#define P2P_NAT_HELLO_H
#include <cstdint>

struct Hello {

    static constexpr size_t MIN_SIZE = 12;

    uint64_t node_id;
    uint16_t tcp_port;
    uint16_t udp_port;

};

#endif //P2P_NAT_HELLO_H