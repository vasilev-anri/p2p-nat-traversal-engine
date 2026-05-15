#include <iostream>

#include "../handlers/tcp_listener.h"
#include "../reactor/reactor.h"



int main() {


    Reactor reactor = Reactor();
    auto listener = std::make_unique<TCPListener>(8080, reactor);
    reactor.register_handler(std::move(listener));
    while (true) {
        reactor.handle_events();
    }




}
