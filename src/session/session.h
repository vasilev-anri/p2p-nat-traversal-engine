#pragma once

#include "../net/endpoint.h"
#include "../handlers/event_handler.h"
#include "../wire/msg.h"

#include <functional>
#include <string>

#include "../transport/connection_info.h"
#include "../wire/msg_parser.h"

#include "../utils/socket_utils.h"
#include "../utils/io_events.h"


enum class SessionState {
    CREATED,
    CONNECTING,
    CONNECTED,
    HANDSHAKING,
    ESTABLISHED,
    CLOSING,
    CLOSED
};

class Session : public EventHandler {
public:
    using MessageCallback = std::function<void(Session&, const Message&)>;
    using StateCallback = std::function<void(Session&)>;
    using ErrorCallback = std::function<void(Session&, const std::string&)>;

    void handle_event(uint32_t events) override;
    [[nodiscard]] int get_fd() const override;

    // Session(UniqueFD fd, Endpoint local, Endpoint remote);
    explicit Session(ConnectionInfo connection);

    ~Session();

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;
    Session(Session&&) = delete;
    Session& operator=(Session&&) = delete;

    // lifecycle
    void start_handshake();
    void close();

    void send(const Message& msg);

    // register callback
    void set_message_callback(MessageCallback cb);
    void set_established_callback(StateCallback cb);
    void set_closed_callback(StateCallback cb);
    void set_error_callback(ErrorCallback cb);

    // state
    [[nodiscard]] SessionState state() const noexcept;
    [[nodiscard]] bool is_ready() const noexcept;
    [[nodiscard]] bool is_closed() const noexcept;

    // endpoints
    [[nodiscard]] const Endpoint& local_endpoint() const noexcept;
    [[nodiscard]] const Endpoint& remote_endpoint() const noexcept;

    [[nodiscard]] int fd() const noexcept;


    void mark_established();


private:
    // rector events
    void handle_read();
    void handle_write();
    void handle_error();

    // callback helpers
    void emit_message(const Message& msg);
    void emit_established();
    void emit_closed();
    void emit_error(const std::string& error);


private:


    SessionState state_ = SessionState::CREATED;

    ConnectionInfo connection_;

    MsgParser parser_;

    MessageCallback message_callback_;
    StateCallback established_callback_;
    StateCallback closed_callback_;
    ErrorCallback error_callback_;

};

