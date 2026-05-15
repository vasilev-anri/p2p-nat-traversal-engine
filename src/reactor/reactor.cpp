#include "reactor.h"


Reactor::Reactor() {
    epfd_ = epoll_create1(0);
}


void Reactor::register_handler(std::unique_ptr<EventHandler> handler) {
    int fd = handler->get_fd();
    handlers[fd] = std::move(handler);

    epoll_event ev{};

    set_nonblocking(fd);

    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = fd;

    epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev);
}

void Reactor::unregister_handler(int fd) {
    epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, nullptr);
    handlers.erase(fd);
}

void Reactor::handle_events() {
    epoll_event events[64];

    int nfds;

    while (true) {
        nfds = epoll_wait(epfd_, events, 64, -1);
        if (nfds == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("epoll_wait");
            return;
        }
        break;
    }


    for (int i = 0; i < nfds; i++) {


        int fd = events[i].data.fd;

        auto it = handlers.find(fd);
        if (it == handlers.end()) continue;

        it->second->handle_event(events[i].events);
    }
}