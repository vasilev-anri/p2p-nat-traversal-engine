#include "tcp_listener.h"

#include "tcp_connector.h"

#include <iostream>

TCPListener::TCPListener(int port, SpawnCallback spawn) : port_(port), spawn_(std::move(spawn)) {
    fd_ = UniqueFD(socket(AF_INET, SOCK_STREAM, 0));
    setup();
}


void TCPListener::handle_event(uint32_t events) {
    if (events & EPOLLERR) {
        done();
        return;
    }
    if (events & EPOLLIN) {
        accept_all(get_fd(), [&](UniqueFD cfd) {
            auto conn = std::make_unique<TCPConnector>(std::move(cfd));
            spawn_(std::move(conn));
        });
    }
}


int TCPListener::get_fd() const {
    return fd_.get();
}

void TCPListener::setup() {
    sockaddr_in addr{};

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(get_fd(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    listen(get_fd(), 10);
}
