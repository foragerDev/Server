#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <unordered_set>


class WebSocketSession;

class SharedState{
    std::string doc_root_; 
    std::mutex mutex_;

    std::unordered_set<WebSocketSession*> sessions_;
public:
    explicit SharedState(std::string doc_root) : doc_root_(doc_root){

    }

    std::string const& doc_root() noexcept { return doc_root_; }
    void join(WebSocketSession* session){
        std::lock_guard<std::mutex> lock(mutex_);
        sessions_.insert(session);
    }

    void leave(WebSocketSession* session){
        std::lock_guard<std::mutex> lock(mutex_);
        sessions_.erase(session);
    }
    void send(std::string message);
};