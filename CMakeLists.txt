cmake_minimum_required(VERSION 4.1)
project(p2p_nat)

set(CMAKE_CXX_STANDARD 23)

add_executable(p2p_nat src/app/main.cpp
        src/reactor/reactor.cpp
        src/reactor/reactor.h
        src/handlers/event_handler.h
        src/handlers/tcp_connector.cpp
        src/handlers/tcp_connector.h
        src/handlers/tcp_listener.cpp
        src/handlers/tcp_listener.h
        src/utils/UniqueFD.h
        src/utils/socket_utils.h
        src/utils/socket_utils.cpp
        src/handlers/udp_handler.cpp
        src/handlers/udp_handler.h
        src/wire/msg_types.h
        src/wire/msg_codec.cpp
        src/wire/msg_codec.h
        src/wire/msg.h
        src/wire/msg_header.h
        src/wire/messages/hello.h
        src/wire/msg_parser.cpp
        src/wire/msg_parser.h
        src/peer/peer.cpp
        src/peer/peer.h
        src/peer/peers_manager.cpp
        src/peer/peers_manager.h
        src/peer/endpoint.h
        src/session/session.cpp
        src/session/session.h
        src/transport/connection_info.h

)
