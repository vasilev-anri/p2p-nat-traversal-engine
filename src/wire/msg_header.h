#ifndef P2P_NAT_MSG_HEADER_H
#define P2P_NAT_MSG_HEADER_H

#include <cstdint>
#include <cstddef>

struct MessageHeader {
    static constexpr uint32_t MAGIC = 0x50325050;
    static constexpr uint32_t MAX_PAYLOAD = 1 << 20;
    static constexpr size_t HEADER_SIZE = 18;

    uint32_t magic;
    uint8_t version;
    uint8_t type;

    uint32_t length;
    uint32_t session_id;
    uint32_t request_id;
};




#endif //P2P_NAT_MSG_HEADER_H
