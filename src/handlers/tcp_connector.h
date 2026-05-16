#ifndef P2P_NAT_TCP_ACCEPTOR_H
#define P2P_NAT_TCP_ACCEPTOR_H

#include <iostream>
#include <ostream>
#include <sys/socket.h>

#include "../utils/socket_utils.h"

#include "../reactor/reactor.h"

#include <cstdint>
#include <vector>

#include "event_handler.h"
#include "../utils/UniqueFD.h"

class TCPConnector : public EventHandler {
    UniqueFD fd_;
    std::vector<uint8_t> buf;
public:
    explicit TCPConnector(UniqueFD fd);
    void handle_event(uint32_t events) override;
    [[nodiscard]] int get_fd() const override;
};

#endif //P2P_NAT_TCP_ACCEPTOR_H