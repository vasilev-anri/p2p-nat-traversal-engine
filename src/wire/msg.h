#ifndef P2P_NAT_MSG_H
#define P2P_NAT_MSG_H

#include <cstdint>
#include <vector>

#include "msg_header.h"

struct Message {
    MessageHeader header;
    std::vector<uint8_t> payload;
};

#endif //P2P_NAT_MSG_H