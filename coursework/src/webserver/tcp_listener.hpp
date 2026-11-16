#pragma once

#include "config.hpp"

class TcpListener {
public: 
    explicit TcpListener(const ListenConfig &config);
    ~TcpListener();

    TcpListener(const TcpListener&) = delete;
    TcpListener &operator=(const TcpListener&) = delete;

    int native_handle() const noexcept;


private:
    int _fd = -1;
};
