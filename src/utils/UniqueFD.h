//
// Created by av on 5/6/26.
//

#ifndef P2P_NAT_UNIQUEFD_H
#define P2P_NAT_UNIQUEFD_H

#include <unistd.h>


class UniqueFD {
private:
    int fd_ = -1;
public:
    UniqueFD() = default;
    explicit UniqueFD(int fd) : fd_(fd) {}
    UniqueFD(const UniqueFD&) = delete;
    UniqueFD& operator=(const UniqueFD&) = delete;
    UniqueFD(UniqueFD&& other) noexcept : fd_(other.fd_) {other.fd_ = -1;}
    UniqueFD& operator=(UniqueFD&& other) noexcept {
        if (this != &other) {
            reset();
            fd_ = other.fd_;
            other.fd_ = -1;
        }
        return *this;
    }
    ~UniqueFD() noexcept { reset(); }
    [[nodiscard]] int get() const { return fd_; }
    [[nodiscard]] bool is_valid() const { return fd_ != -1; }
    int release() {
        int tmp = fd_;
        fd_ = -1;
        return tmp;
    }
    void reset(int new_fd = - 1) {
        if (fd_ != -1 && fd_ != new_fd) ::close(fd_);
    }
};

#endif //P2P_NAT_UNIQUEFD_H