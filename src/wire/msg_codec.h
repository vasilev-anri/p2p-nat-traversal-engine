#ifndef P2P_NAT_MSG_CODEC_H
#define P2P_NAT_MSG_CODEC_H

#include <cstdint>
#include <span>
#include <stdexcept>
#include <vector>

#include "msg_header.h"
#include "messages/hello.h"

class MessageCodec {
public:
    static std::vector<uint8_t> encode_header(const MessageHeader&);
    static MessageHeader decode_header(std::span<const uint8_t>);

    static std::vector<uint8_t> encode_hello(const Hello&);
    static Hello decode_hello(std::span<const uint8_t>);

private:
    template <class T>
    static void write_integral_be(T val, std::vector<uint8_t>& out) {
        static_assert(std::is_unsigned_v<T>, "Unsigned type required");
        static_assert(
            sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8,
            "Only fixed-width in size (1, 2, 4, 8) bytes supported"
        );
        const size_t n = sizeof(T);
        const size_t start = out.size();
        out.resize(start + n);
        for (size_t i = 0; i < n; ++i) {
            out[start + i] = static_cast<uint8_t>(val >> (n - i - 1) * 8);
        }
    }

    template <class T>
    static T read_integral_be(std::span<const uint8_t> buf, size_t& offset) {
        static_assert(std::is_unsigned_v<T>, "Unsigned type required");
        static_assert(
            sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8,
            "Only fixed-width in size (1, 2, 4, 8) bytes supported"
        );
        const size_t n = sizeof(T);
        if (offset + n > buf.size()) {
            throw std::runtime_error("Buffer overflow");
        }
        T res = 0;
        for (size_t i = 0; i < n; ++i) {
            res <<= 8;
            res |= static_cast<T>(buf[offset + i]);
        }
        offset += n;
        return res;
    }

    static void write_u8(uint8_t val, std::vector<uint8_t>& out);
    static void write_u16(uint16_t val, std::vector<uint8_t>& out);
    static void write_u32(uint32_t val, std::vector<uint8_t>& out);
    static void write_u64(uint64_t val, std::vector<uint8_t>& out);

    static uint8_t read_u8(std::span<const uint8_t> buf, size_t& offset);
    static uint16_t read_u16(std::span<const uint8_t> buf, size_t& offset);
    static uint32_t read_u32(std::span<const uint8_t> buf, size_t& offset);
    static uint64_t read_u64(std::span<const uint8_t> buf, size_t& offset);
};

#endif //P2P_NAT_MSG_CODEC_H
