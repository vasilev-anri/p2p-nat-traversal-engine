#ifndef P2P_NAT_TCP_LISTENER_H
#define P2P_NAT_TCP_LISTENER_H

#include "../utils/UniqueFD.h"
#include <sys/socket.h>
#include <netinet/in.h>

#include "event_handler.h"
#include "../reactor/reactor.h"

class TCPListener : public EventHandler{
    UniqueFD fd_;
    int port_;
    Reactor& reactor_;

public:
    explicit TCPListener(int port, Reactor& reactor);
    void handle_event(uint32_t events) override;
    [[nodiscard]] int get_fd() const override;
private:
    void setup();
};

#endif //P2P_NAT_TCP_LISTENER_H