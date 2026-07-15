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
#include <arpa/inet.h>


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





#endif //P2P_NAT_SOCKET_UTILS_H
