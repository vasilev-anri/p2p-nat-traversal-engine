#ifndef P2P_NAT_SOCKET_UTILS_H
#define P2P_NAT_SOCKET_UTILS_H

#include <cstdint>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <iterator>
#include <netinet/in.h>
#include <sys/socket.h>
#include "UniqueFD.h"


enum class RecvStatus {
    OK,
    CLOSED,
    ERROR
};

struct UDPPacket {
    std::vector<uint8_t> data;
    sockaddr_in sender;
};

int set_nonblocking(int fd);

RecvStatus drain_tcp_socket(int fd, std::vector<uint8_t>& out);

RecvStatus drain_udp_socket(int fd, std::vector<UDPPacket>& out);

template <typename Callback>
void accept_all(int fd, Callback cb) {
    while (true) {
        int cfd = accept(fd, nullptr, nullptr);
        if (cfd == -1) {
            if (errno == EINTR) continue;
            if (errno == EAGAIN || errno == EWOULDBLOCK) break;
            perror("accept");
            break;
        }
        set_nonblocking(cfd);
        cb(UniqueFD(cfd));
    }
}


#endif //P2P_NAT_SOCKET_UTILS_H