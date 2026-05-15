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