#ifndef P2P_NAT_MSG_TYPES_H
#define P2P_NAT_MSG_TYPES_H

#include <cstdint>

enum class MsgType : uint8_t {
    hello       = 0x01,
    hello_ack   = 0x02,
    bye         = 0x03,

    ping        = 0x10,
    pong        = 0x11,

    offer       = 0x20,
    answer      = 0x21,
    candidate   = 0x22,

    error       = 0x7E,
    ext         = 0x7F,
};

#endif //P2P_NAT_MSG_TYPES_H
