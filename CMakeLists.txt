cmake_minimum_required(VERSION 4.1)
project(p2p_nat)

set(CMAKE_CXX_STANDARD 23)

add_executable(p2p_nat main.cpp
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

)
