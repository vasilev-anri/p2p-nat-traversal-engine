//
// Created by av on 7/12/26.
//

#include "msg_parser.h"

void MsgParser::feed(std::span<const uint8_t> data) {
    buffer_.insert(buffer_.end(), data.begin(), data.end());
}

bool MsgParser::next(Message& out) {
    if (buffer_.size() < MessageHeader::HEADER_SIZE) return false;

    std::span<const uint8_t> header_span(buffer_.data(), MessageHeader::HEADER_SIZE);
    MessageHeader header = MessageCodec::decode_header(header_span);

    size_t total = MessageHeader::HEADER_SIZE + header.length;
    if (buffer_.size() < total) return false;

    out.header = header;
    out.payload.assign(buffer_.begin() + MessageHeader::HEADER_SIZE, buffer_.begin() + total);

    buffer_.erase(buffer_.begin(), buffer_.begin() + total);

    return true;
}


