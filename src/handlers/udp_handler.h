//
// Created by av on 5/16/26.
//

#ifndef P2P_NAT_UDP_HANDLER_H
#define P2P_NAT_UDP_HANDLER_H

#include <iostream>
#include <ostream>
#include <sys/socket.h>

#include "../utils/socket_utils.h"

#include "../reactor/reactor.h"

#include <cstdint>
#include <vector>

#include "event_handler.h"
#include "../utils/UniqueFD.h"
#include <netinet/in.h>

#include <arpa/inet.h>


class UDPHandler : public EventHandler {
    UniqueFD fd_;
    int port_;
    Reactor& reactor_;
public:
    explicit UDPHandler(int port, Reactor& reactor);
    void handle_event(uint32_t events) override;
    [[nodiscard]] int get_fd() const override;
private:
    void setup();
};

#endif //P2P_NAT_UDP_HANDLER_H