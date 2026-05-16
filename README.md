# peer-2-peer-nat-traversal-engine

## Current Features
- epoll-based reactor
- edge-triggered non-blocking TCP & UDP
- modular event handler system
- RAII file descriptor management
- non-blocking socket draining for EPOLLET
- callback-based connection acceptance architecture

## Planned Features
- custom binary wire protocol
- peer abstraction & connection state machine
- lightweight signaling/bootstrap server
- peer registration & discovery
- NAT traversal engine
- UDP hole punching
- adaptive retry and fallback strategies
- observability & connection metrics
- multi-network testing framework

## Architecture

```mermaid
classDiagram

    class Reactor {
        -epfd_: int
        -handlers: unordered_map~int, unique_ptr~EventHandler~~
        +register_handler(handler: unique_ptr~EventHandler~)
        +unregister_handler(fd: int)
        +handle_events()
    }

    class EventHandler {
        <<interface>>
        +handle_event(events: uint32_t)
        +get_fd(): int
        +set_done_callback(cb: DoneCallback)
        #done()
    }

    class TCPListener {
        -fd_: UniqueFD
        -port_: int
        -spawn_: SpawnCallback
        +handle_event(events: uint32_t)
        +get_fd(): int
        -setup()
    }

    class TCPConnector {
        -fd_: UniqueFD
        +handle_event(events: uint32_t)
        +get_fd(): int
    }

    class UDPHandler {
        -fd_: UniqueFD
        +handle_event(events: uint32_t)
        +get_fd(): int
        -setup()
    }

    class UniqueFD {
        -fd: int
        +get(): int
    }

    class accept_all {
        <<utility>>
        +accept_all(fd, callback)
    }

    Reactor --> EventHandler : owns
    Reactor ..> epoll : uses

    EventHandler <|-- TCPListener
    EventHandler <|-- TCPConnector
    EventHandler <|-- UDPHandler

    TCPListener --> UniqueFD : owns
    TCPConnector --> UniqueFD : owns
    UDPHandler --> UniqueFD : owns

    TCPListener ..> accept_all : uses
    TCPListener ..> TCPConnector : spawns
    TCPConnector ..> drain_tcp_socket : uses
    UDPHandler ..> drain_udp_socket : uses