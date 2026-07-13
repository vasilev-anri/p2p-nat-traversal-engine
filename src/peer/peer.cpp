#include "peer.h"


Peer::Peer(const std::string& peer_id) : id(peer_id) {
    last_seen = std::chrono::steady_clock::now();
}

void Peer::update_last_seen() {
    last_seen = std::chrono::steady_clock::now();
}

bool Peer::is_connected() const {
    return state == PeerState::ONLINE || state == PeerState::AUTHENTICATED;
}

bool Peer::is_healthy() const {
    if (state == PeerState::BLOCKED) return false;
    if (!is_connected()) return false;

    // seen recently
    auto diff = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - last_seen);
    return diff.count() < 5; // seen in last 5 mins -> healthy
}

void Peer::add_session(std::shared_ptr<Session> session) {
    if (!session) return;

    active_sessions.push_back(std::move(session));

    // state update
    if (state == PeerState::UNKNOWN || state == PeerState::OFFLINE) {
        state = PeerState::CONNECTING;
    }

    update_last_seen();
}

void Peer::remove_session(Session* session) {
    if (!session) return;
    auto it = std::remove_if(active_sessions.begin(), active_sessions.end(),
                             [session](const auto& s) { return s.get() == session; });
    active_sessions.erase(it, active_sessions.end());
    if (active_sessions.empty() && state != PeerState::BLOCKED) {
        state = PeerState::OFFLINE;
    }
}

void Peer::send(const Message& msg) {
    for (auto& session : active_sessions) {
        // if (session && session->is_ready()) {
        //     session->send(msg);
        //     return;
        // }
    }
}
