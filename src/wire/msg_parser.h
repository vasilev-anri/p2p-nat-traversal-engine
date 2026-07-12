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

bool try_parse_message(std::vector<uint8_t>& buf, Message& out);

#endif //P2P_NAT_MSG_PARSER_H