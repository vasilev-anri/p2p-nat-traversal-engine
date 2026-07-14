//
// Created by av on 7/12/26.
//

#ifndef P2P_NAT_MSG_PARSER_H
#define P2P_NAT_MSG_PARSER_H
#include <cstdint>
#include <vector>

#include <span>

#include "msg_codec.h"

#include "msg.h"

class MsgParser {
public:
    void feed(std::span<const uint8_t> data);
    bool next(Message& out);

private:
    std::vector<uint8_t> buffer_;
};


#endif //P2P_NAT_MSG_PARSER_H
