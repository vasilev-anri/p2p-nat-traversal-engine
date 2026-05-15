#ifndef P2P_NAT_REACTOR_H
#define P2P_NAT_REACTOR_H
#include <memory>
#include <unordered_map>

#include "../handlers/event_handler.h"
#include <sys/epoll.h>

#include <sys/socket.h>

#include "../utils/socket_utils.h"

class Reactor {
    std::unordered_map<int, std::unique_ptr<EventHandler>> handlers;
    int epfd_;
public:
    Reactor();
    void register_handler(std::unique_ptr<EventHandler> handler);
    void unregister_handler(int fd);
    void handle_events();
};

#endif //P2P_NAT_REACTOR_H