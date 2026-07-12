#include "msg_codec.h"

#include "msg_types.h"
#include "msg_header.h"


std::vector<uint8_t> MessageCodec::encode_header(const MessageHeader& header) {
    std::vector<uint8_t> res;
    res.reserve(MessageHeader::HEADER_SIZE);

    write_u32(MessageHeader::MAGIC, res);
    write_u8(header.version, res);
    write_u8(header.type, res);
    write_u32(header.length, res);
    write_u32(header.session_id, res);
    write_u32(header.request_id, res);

    return res;
}

MessageHeader MessageCodec::decode_header(std::span<const uint8_t> buf) {
    if (buf.size() != MessageHeader::HEADER_SIZE) throw std::runtime_error("Invalid Header size");

    size_t offset = 0;
    MessageHeader header{};

    auto magic = read_u32(buf, offset);
    if (magic != MessageHeader::MAGIC) throw std::runtime_error("Invalid Header magic");

    auto version = read_u8(buf, offset);

    auto type = read_u8(buf, offset);

    switch (static_cast<MsgType>(type)) {
        case MsgType::hello:
        case MsgType::hello_ack:
        case MsgType::bye:
        case MsgType::ping:
        case MsgType::pong:
        case MsgType::offer:
        case MsgType::answer:
        case MsgType::candidate:
        case MsgType::error:
        case MsgType::ext:
            break;
        default:
            throw std::runtime_error("Invalid Header type");
    }

    auto length = read_u32(buf, offset);
    if (length > MessageHeader::MAX_PAYLOAD) throw std::runtime_error("Invalid Header length");

    auto session_id = read_u32(buf, offset);
    auto request_id = read_u32(buf, offset);

    header.magic = magic;
    header.version = version;
    header.type = type;
    header.length = length;
    header.session_id = session_id;
    header.request_id = request_id;

    return header;
}

std::vector<uint8_t> MessageCodec::encode_hello(const Hello& hello) {
    std::vector<uint8_t> res;
    res.reserve(Hello::MIN_SIZE);

    write_u64(hello.node_id, res);
    write_u16(hello.tcp_port, res);
    write_u16(hello.udp_port, res);

    return res;
}

Hello MessageCodec::decode_hello(std::span<const uint8_t> buf) {
    if (buf.size() < Hello::MIN_SIZE) throw std::runtime_error("Invalid Hello size");

    size_t offset = 0;
    Hello hello{};

    auto node_id = read_u64(buf, offset);
    auto tcp_port = read_u16(buf, offset);
    auto udp_port = read_u16(buf, offset);

    hello.node_id = node_id;
    hello.tcp_port = tcp_port;
    hello.udp_port = udp_port;

    return hello;
}

void MessageCodec::write_u8(uint8_t val, std::vector<uint8_t>& out) {
    write_integral_be(val, out);
}

void MessageCodec::write_u16(uint16_t val, std::vector<uint8_t>& out) {
    write_integral_be(val, out);
}

void MessageCodec::write_u32(uint32_t val, std::vector<uint8_t>& out) {
    write_integral_be(val, out);
}

void MessageCodec::write_u64(uint64_t val, std::vector<uint8_t>& out) {
    write_integral_be(val, out);
}

uint8_t MessageCodec::read_u8(std::span<const uint8_t> buf, size_t& offset) {
    return read_integral_be<uint8_t>(buf, offset);
}

uint16_t MessageCodec::read_u16(std::span<const uint8_t> buf, size_t& offset) {
    return read_integral_be<uint16_t>(buf, offset);
}

uint32_t MessageCodec::read_u32(std::span<const uint8_t> buf, size_t& offset) {
    return read_integral_be<uint32_t>(buf, offset);
}

uint64_t MessageCodec::read_u64(std::span<const uint8_t> buf, size_t& offset) {
    return read_integral_be<uint64_t>(buf, offset);
}
