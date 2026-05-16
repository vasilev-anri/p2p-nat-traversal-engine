#include "tcp_connector.h"


TCPConnector::TCPConnector(UniqueFD fd) : fd_(std::move(fd)) { }

void TCPConnector::handle_event(uint32_t events) {

    if (events & EPOLLERR) {
        done();
        return;
    }

    if (events & EPOLLHUP) {
        done();
        return;
    }

    if (events & EPOLLIN) {
        RecvStatus status = drain_tcp_socket(get_fd(), buf);

        if (status == RecvStatus::CLOSED || status == RecvStatus::ERROR) {
            done();
            return;
        }
        std::cout.write(reinterpret_cast<const char*>(buf.data()), buf.size());
        std::cout << std::endl;
        buf.clear();
    }

    if (events & EPOLLRDHUP) {
        done();
        return;
    }






}

int TCPConnector::get_fd() const {
    return fd_.get();
}
