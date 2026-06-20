#include "msg_codec.h"

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

uint16_t MessageCodec::read_u16(std::span<const uint8_t> buf, size_t &offset) {
    return read_integral_be<uint16_t>(buf, offset);
}

uint32_t MessageCodec::read_u32(std::span<const uint8_t> buf, size_t& offset) {
    return read_integral_be<uint32_t>(buf, offset);
}

uint64_t MessageCodec::read_u64(std::span<const uint8_t> buf, size_t& offset) {
    return read_integral_be<uint64_t>(buf, offset);
}