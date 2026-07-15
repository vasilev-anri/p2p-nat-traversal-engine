//
// Created by av on 7/13/26.
//

#ifndef P2P_NAT_PEER_H
#define P2P_NAT_PEER_H

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include "../wire/msg.h"

#include "../net/endpoint.h"

#include "../session/session.h"


enum class PeerState {
    UNKNOWN,
    CONNECTING,
    ONLINE,
    AUTHENTICATED,
    OFFLINE,
    BLOCKED
};

struct Peer {
    const std::string id;
    PeerState state = PeerState::UNKNOWN;
    std::chrono::steady_clock::time_point last_seen{};
    std::vector<Endpoint> known_endpoints;
    std::vector<std::shared_ptr<Session>> active_sessions;

    explicit Peer(const std::string& peer_id);

    void send(const Message& msg);
    void add_session(std::shared_ptr<Session> session);
    void remove_session(Session* session);
    void update_last_seen();

    [[nodiscard]] bool is_connected() const;
    [[nodiscard]] bool is_healthy() const;
};

#endif //P2P_NAT_PEER_H