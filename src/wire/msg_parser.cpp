//
// Created by av on 7/12/26.
//

#include "msg_parser.h"


bool try_parse_message(std::vector<uint8_t>& buf, Message& out) {
    if (buf.size() < MessageHeader::HEADER_SIZE) return false;

    std::span<const uint8_t> header_span(buf.data(), MessageHeader::HEADER_SIZE);
    MessageHeader header = MessageCodec::decode_header(header_span);

    size_t total = MessageHeader::HEADER_SIZE + header.length;
    if (buf.size() < total) return false;

    out.header = header;
    out.payload.assign(buf.begin() + MessageHeader::HEADER_SIZE, buf.begin() + total);

    buf.erase(buf.begin(), buf.begin() + total);

    return true;
}
