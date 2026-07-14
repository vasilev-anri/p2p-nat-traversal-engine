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
#include "../peer/endpoint.h"
#include "../transport/connection_info.h"


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

Endpoint sockaddr_to_endpoint(const sockaddr_in& addr);

template <typename Callback>
void accept_all(int fd, Callback cb) {
    while (true) {
        sockaddr_in remote_addr{};
        socklen_t remote_len = sizeof(remote_addr);


        int cfd = accept(
            fd,
            reinterpret_cast<sockaddr*>(&remote_addr),
            &remote_len
        );


        if (cfd == -1) {
            if (errno == EINTR)
                continue;

            if (errno == EAGAIN ||
                errno == EWOULDBLOCK)
                break;

            perror("accept");
            break;
        }


        set_nonblocking(cfd);


        sockaddr_in local_addr{};
        socklen_t local_len = sizeof(local_addr);


        getsockname(
            cfd,
            reinterpret_cast<sockaddr*>(&local_addr),
            &local_len
        );


        ConnectionInfo connection{
            UniqueFD(cfd),
            sockaddr_to_endpoint(local_addr),
            sockaddr_to_endpoint(remote_addr)
        };


        cb(std::move(connection));
    }
}

#endif //P2P_NAT_SOCKET_UTILS_H
