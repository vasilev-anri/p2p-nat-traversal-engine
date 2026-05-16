#include "tcp_connector.h"


TCPConnector::TCPConnector(UniqueFD fd, Reactor& reactor) : fd_(std::move(fd)), reactor_(reactor) { }

void TCPConnector::handle_event(uint32_t events) {

    if (events & EPOLLERR) {
        reactor_.unregister_handler(get_fd());
        return;
    }

    if (events & EPOLLHUP) {
        reactor_.unregister_handler(get_fd());
        return;
    }

    if (events & EPOLLIN) {
        RecvStatus status = drain_tcp_socket(get_fd(), buf);

        if (status == RecvStatus::CLOSED || status == RecvStatus::ERROR) {
            reactor_.unregister_handler(get_fd());
            return;
        }
        std::cout.write(reinterpret_cast<const char*>(buf.data()), buf.size());
        std::cout << std::endl;
        buf.clear();
    }

    if (events & EPOLLRDHUP) {
        reactor_.unregister_handler(get_fd());
        return;
    }






}

int TCPConnector::get_fd() const {
    return fd_.get();
}
