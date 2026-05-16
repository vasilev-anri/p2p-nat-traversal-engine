#include <iostream>

#include "../handlers/tcp_listener.h"
#include "../handlers/udp_handler.h"
#include "../reactor/reactor.h"


int main() {
    Reactor reactor;

    auto listener = std::make_unique<TCPListener>(8080,
                                                  [&](std::unique_ptr<EventHandler> h) {
                                                      reactor.register_handler(std::move(h));
                                                  });


    // auto listener = std::make_unique<TCPListener>(8080, reactor);
    // auto listener = std::make_unique<UDPHandler>(8080, reactor);

    auto udp = std::make_unique<UDPHandler>(8080);

    reactor.register_handler(std::move(listener));
    reactor.register_handler(std::move(udp));

    while (true) {
        reactor.handle_events();
    }
}
