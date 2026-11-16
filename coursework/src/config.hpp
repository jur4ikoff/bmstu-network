#pragma once

#include <string>
#include <cstdint>
#include <stdexcept>
#include <utility>

class ListenConfig
{
public:
    ListenConfig(std::string address, int port, int backlog = 128) : _address(std::move(address))
    {
        if (port < 1 || port > 65535)
        {
            throw std::invalid_argument("Port must be between 1 and 65535");
        }
        if (backlog <= 0)
        {  
            throw std::invalid_argument("Backlog must be positive");
        }
        _port = static_cast<std::uint16_t>(port);
        _backlog = backlog;
    }

    const std::string &address() const noexcept { return _address; }
    std::uint16_t port() const noexcept { return _port; }
    int backlog() const noexcept { return _backlog; }

private:
    std::string _address;
    std::uint16_t _port;
    int _backlog;
};

class Config
{
public:
    ListenConfig listen_config;
};
