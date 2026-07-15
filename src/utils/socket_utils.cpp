#include "socket_utils.h"


int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) return -1;
    return 0;
}

RecvStatus drain_tcp_socket(int fd, std::vector<uint8_t>& out) {
    while (true) {
        uint8_t buffer[4096];
        ssize_t n = recv(fd, buffer, sizeof(buffer), 0);

        if (n > 0) {
            out.insert(out.end(), buffer, buffer + n);
            continue;
        }

        if (n == 0) return RecvStatus::CLOSED;

        if (errno == EINTR) continue;

        if (errno == EAGAIN || errno == EWOULDBLOCK) return RecvStatus::OK;

        return RecvStatus::ERROR;
    }
}

RecvStatus drain_udp_socket(int fd, std::vector<UDPPacket>& out) {
    while (true) {
        UDPPacket packet;
        packet.data.resize(4096);

        socklen_t addr_len = sizeof(packet.sender);

        ssize_t n = recvfrom(fd, packet.data.data(), packet.data.size(), 0, reinterpret_cast<struct sockaddr*>(&packet.sender), &addr_len);

        if (n > 0) {
            packet.data.resize(n);
            out.push_back(std::move(packet));
            continue;
        }

        if (n == -1 && errno == EINTR) continue;

        if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            return RecvStatus::OK;
        }

        return RecvStatus::ERROR;
    }
}





