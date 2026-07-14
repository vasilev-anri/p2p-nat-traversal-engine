#ifndef P2P_NAT_TCP_LISTENER_H
#define P2P_NAT_TCP_LISTENER_H

#include "../utils/UniqueFD.h"
#include <sys/socket.h>
#include <netinet/in.h>

#include "event_handler.h"
#include "../reactor/reactor.h"
#include "../transport/connection_info.h"

#include <iostream>
#include "../peer/session.h"

#include "../utils/socket_utils.h"

class TCPListener : public EventHandler{

public:
    // using SpawnCallback = std::function<void(std::unique_ptr<EventHandler>)>;

    using AcceptCallback = std::function<void(ConnectionInfo)>;

    explicit TCPListener(int port, AcceptCallback on_accept);

    void handle_event(uint32_t events) override;
    [[nodiscard]] int get_fd() const override;

private:
    void setup();

private:
    UniqueFD fd_;
    int port_;
    AcceptCallback on_accept_;
};

#endif //P2P_NAT_TCP_LISTENER_H