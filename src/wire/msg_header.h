#ifndef P2P_NAT_MSG_HEADER_H
#define P2P_NAT_MSG_HEADER_H

#include <cstdint>
#include <cstddef>

#pragma pack(push, 1)
struct MessageHeader {
    static constexpr uint32_t MAGIC = 0x50325050;
    static constexpr uint32_t MAX_PAYLOAD = 1 << 20;

    uint32_t magic;
    uint8_t  version;
    uint8_t  type;
    uint16_t flags;

    uint32_t length;
    uint32_t session_id;
    uint32_t request_id;

    static constexpr size_t HEADER_SIZE = sizeof(MessageHeader);
};
#pragma pack(pop)


#endif //P2P_NAT_MSG_HEADER_H