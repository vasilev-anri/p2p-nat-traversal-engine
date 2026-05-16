//
// Created by av on 5/16/26.
//

#include "udp_handler.h"



UDPHandler::UDPHandler(int port, Reactor& reactor) : port_(port), reactor_(reactor) {
    fd_ = UniqueFD(socket(AF_INET, SOCK_DGRAM, 0));
    setup();
}

void UDPHandler::handle_event(uint32_t events) {
    if (events & (EPOLLERR | EPOLLHUP)) {
        reactor_.unregister_handler(get_fd());
        return;
    }

    std::vector<UDPPacket> packets;

    RecvStatus status = drain_udp_socket(get_fd(), packets);

    if (status == RecvStatus::ERROR) {
        reactor_.unregister_handler(get_fd());
        return;
    }

    for (auto& packet : packets) {
        std::string msg(packet.data.begin(), packet.data.end());

        std::cout << "UDP from: " << inet_ntoa(packet.sender.sin_addr) << ":" << ntohs(packet.sender.sin_port) << " => " << msg << std::endl;
    }
}

int UDPHandler::get_fd() const {
    return fd_.get();
}

void UDPHandler::setup() {

    sockaddr_in addr{};

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(get_fd(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

}
