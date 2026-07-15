#include <iostream>

#include "../handlers/tcp_listener.h"
#include "../handlers/udp_handler.h"
#include "../reactor/reactor.h"
#include "../wire/msg_types.h"






void connect_to_peer(Reactor& reactor, const std::string& ip, uint16_t port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    set_nonblocking(fd);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    ::connect(
        fd,
        reinterpret_cast<sockaddr*>(&addr),
        sizeof(addr)
    );

    sockaddr_in local{};
    socklen_t len = sizeof(local);

    getsockname(
        fd,
        reinterpret_cast<sockaddr*>(&local),
        &len
    );

    ConnectionInfo conn{
        UniqueFD(fd),
        sockaddr_to_endpoint(local),
        sockaddr_to_endpoint(addr)
    };

    auto session =
        std::make_unique<Session>(
            std::move(conn)
        );


    session->set_message_callback(
        [](Session& s, const Message& msg)
        {
            auto type =
                static_cast<MsgType>(msg.header.type);

            if (type == MsgType::hello)
            {
                Hello hello =
                    MessageCodec::decode_hello(
                        msg.payload
                    );

                std::cout
                    << "Got hello from node_id: "
                    << hello.node_id
                    << std::endl;

                s.mark_established();
            }
        }
    );


    session->set_established_callback(
        [](Session& s)
        {
            std::cout
                << "Connected and established with "
                << s.remote_endpoint().address
                << ":"
                << s.remote_endpoint().port
                << std::endl;
        }
    );


    session->start_handshake();

    reactor.register_handler(
        std::move(session)
    );
}



int main(int argc, char* argv[]) {
    Reactor reactor;

    auto listener = std::make_unique<TCPListener>(
        8080,
        [&](ConnectionInfo connection) {
            auto session = std::make_unique<Session>(std::move(connection));

            session->set_message_callback([](Session& s, const Message& msg) {
                auto type = static_cast<MsgType>(msg.header.type);
                if (type == MsgType::hello) {
                    Hello hello = MessageCodec::decode_hello(msg.payload);
                    std::cout << "Got hello from node_id: " << hello.node_id << std::endl;
                    s.mark_established();
                }
            });

            session->set_established_callback([](Session& s) {
                std::cout << "Session established with "
                          << s.remote_endpoint().address << ":"
                          << s.remote_endpoint().port << std::endl;
            });

            session->start_handshake();
            reactor.register_handler(std::move(session));
        }
    );

    auto udp = std::make_unique<UDPHandler>(8080);

    reactor.register_handler(std::move(listener));
    reactor.register_handler(std::move(udp));

    // connect mode — runs after reactor is set up
    if (argc == 3 && std::string(argv[1]) == "--connect") {
        connect_to_peer(reactor, argv[2], 8080);
    }

    while (true) {
        reactor.handle_events();
    }
}