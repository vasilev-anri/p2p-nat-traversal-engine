#ifndef P2P_NAT_HANDLE_EVENT_H
#define P2P_NAT_HANDLE_EVENT_H

#include <functional>

class EventHandler {
public:
    using DoneCallback = std::function<void()>;

    virtual ~EventHandler() = default;
    virtual void handle_event(uint32_t events) = 0;
    [[nodiscard]] virtual int get_fd() const = 0;

    void set_done_callback(DoneCallback cb) { on_done_ = std::move(cb); }

protected:
    void done() { if (on_done_) on_done_(); }

private:
    DoneCallback on_done_;
};

#endif //P2P_NAT_HANDLE_EVENT_H