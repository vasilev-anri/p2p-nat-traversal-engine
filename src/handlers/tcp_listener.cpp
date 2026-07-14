#include "tcp_listener.h"


TCPListener::TCPListener(int port, AcceptCallback on_accept) : port_(port), on_accept_(std::move(on_accept)) {
    fd_ = UniqueFD(socket(AF_INET, SOCK_STREAM, 0));
    setup();
}


void TCPListener::handle_event(uint32_t events) {
    if (events & EPOLLERR) {
        done();
        return;
    }
    if (events & EPOLLIN) {
        accept_all(
            get_fd(),
            [&](ConnectionInfo connection) {
                on_accept_(std::move(connection));
            }
        );
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
