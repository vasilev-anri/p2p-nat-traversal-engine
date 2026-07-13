#pragma once

#include <string>
#include <cstdint>

struct Endpoint {
    std::string address;
    uint16_t port = 0;

    Endpoint() = default;
    Endpoint(std::string addr, uint16_t p) : address(std::move(addr)), port(p) {}

    [[nodiscard]] bool is_valid() const {
        return !address.empty() && port != 0;
    }
};
