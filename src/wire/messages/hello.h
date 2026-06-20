#ifndef P2P_NAT_HELLO_H
#define P2P_NAT_HELLO_H
#include <cstdint>

struct Hello {

    uint8_t version;
    uint64_t node_id;
    uint16_t flags;
};

#endif //P2P_NAT_HELLO_H