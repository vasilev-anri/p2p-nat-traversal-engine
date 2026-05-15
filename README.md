# peer-2-peer-nat-traversal-engine

## Current Features
- epoll-based reactor
- edge-triggered non-blocking TCP
- modular event handler system
- RAII file descriptor management
- non-blocking socket draining for EPOLLET
- callback-based connection acceptance architecture

## Planned Features
- UDP transport layer
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
    }

    class TCPListener {
        -fd_: UniqueFD
        -port_: int
        -reactor_: Reactor&
        +handle_event(events: uint32_t)
        +get_fd(): int
        +setup()
    }

    class TCPConnector {
        -fd_: UniqueFD
        -reactor_: Reactor&
        -buf: vector<uint8_t>
        +handle_event(events: uint32_t)
        +get_fd(): int
    }

    class UDPHandler {
        -fd_: UniqueFD
        -reactor_: Reactor&
        +handle_event(events: uint32_t)
        +get_fd(): int
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
    Reactor ..> epoll : uses (edge-triggered)

    EventHandler <|-- TCPListener
    EventHandler <|-- TCPConnector
    EventHandler <|-- UDPHandler

    TCPListener --> UniqueFD : owns
    TCPConnector --> UniqueFD : owns
    UDPHandler --> UniqueFD : owns

    TCPListener ..> accept_all : uses