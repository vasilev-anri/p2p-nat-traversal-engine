//
// Created by av on 7/13/26.
//

#include "session.h"

#include "../utils/socket_utils.h"


Session::Session(ConnectionInfo connection) : connection_(std::move(connection)) {
    state_ = SessionState::CONNECTED; // socket, tcp_conn exist. No handshake yet  crtd->con->handsh->established
}

Session::~Session() = default;

const Endpoint& Session::local_endpoint() const noexcept {
    return connection_.local_endpoint;
}

const Endpoint& Session::remote_endpoint() const noexcept {
    return connection_.remote_endpoint;
}

SessionState Session::state() const noexcept {
    return state_;
}

bool Session::is_ready() const noexcept {
    return state_ == SessionState::ESTABLISHED;
}

bool Session::is_closed() const noexcept {
    return state_ == SessionState::CLOSED;
}


// callbacks
void Session::set_message_callback(MessageCallback cb) {
    message_callback_ = std::move(cb);
}

void Session::set_established_callback(StateCallback cb) {
    established_callback_ = std::move(cb);
}

void Session::set_closed_callback(StateCallback cb) {
    closed_callback_ = std::move(cb);
}

void Session::set_error_callback(ErrorCallback cb) {
    error_callback_ = std::move(cb);
}

// emitters
void Session::emit_message(const Message& msg) {
    if (message_callback_) message_callback_(*this, msg);
}

void Session::emit_established() {
    if (established_callback_) established_callback_(*this);
}

void Session::emit_closed() {
    if (closed_callback_) closed_callback_(*this);
}

void Session::emit_error(const std::string& error) {
    if (error_callback_) error_callback_(*this, error);
}

void Session::close() {
    if (state_ == SessionState::CLOSED) return;
    state_ = SessionState::CLOSED;
    emit_closed();
    done();
}

void Session::handle_event(uint32_t events) {
    if (events & EPOLLERR) {
        handle_error();
        return;
    }

    if (events & EPOLLHUP) {
        done();
        return;
    }

    if (events & EPOLLIN) {
        handle_read();
    }

    if (events & EPOLLRDHUP) {
        close();
    }

    if (events & EPOLLOUT) {
        handle_write();
    }
}

void Session::handle_read() {
    std::vector<uint8_t> data;
    auto status = drain_tcp_socket(get_fd(), data);
    if (status == RecvStatus::CLOSED || status == RecvStatus::ERROR) {
        close();
        return;
    }
    parser_.feed(data);
    Message msg;
    while (parser_.next(msg)) {
        emit_message(msg);
    }
}

void Session::handle_write() {

}

int Session::get_fd() const {
    return connection_.fd.get();
}

void Session::handle_error() {
    emit_error("socket error");
    close();
}
