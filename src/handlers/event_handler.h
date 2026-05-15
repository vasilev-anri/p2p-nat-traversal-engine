#ifndef P2P_NAT_HANDLE_EVENT_H
#define P2P_NAT_HANDLE_EVENT_H

class EventHandler {
public:
    virtual ~EventHandler() = default;
    virtual void handle_event(uint32_t events) = 0;
    [[nodiscard]] virtual int get_fd() const = 0;
};

#endif //P2P_NAT_HANDLE_EVENT_H