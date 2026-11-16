#include "webserver/tcp_listener.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept>
#include <system_error>

[[noreturn]] static void throw_system_error(const char *operation) {
    const int error = errno;
    throw std::system_error(error, std::generic_category(), operation);
}

TcpListener::TcpListener(const ListenConfig &config) {
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(config.port());

    const int result = inet_pton(
        AF_INET,
        config.address().c_str(),
        &address.sin_addr
    );

    if (result == 0) {
        throw std::invalid_argument("Invalid IPv4 address");
    }

    if (result == -1) {
        throw_system_error("inet_pton");
    }

    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd == -1) {
        throw_system_error("socket");
    }

    try {
        const int enabled = 1;
        if (setsockopt(
                _fd,
                SOL_SOCKET,
                SO_REUSEADDR,
                &enabled,
                sizeof(enabled)
            ) == -1) {
            throw_system_error("setsockopt");
        }
        const int flags = fcntl(_fd, F_GETFL, 0);

        if (flags == -1) {
            throw_system_error("fcntl(F_GETFL)");
        }
        if (fcntl(_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
            throw_system_error("fcntl(F_SETFL)");
        }

        if (bind(
            _fd, reinterpret_cast<const sockaddr*>(&address),
            sizeof(address)
        ) == -1) {
            throw_system_error("bind");
        }
        
        if (listen(_fd, config.backlog()) == -1) {
            throw_system_error("listen");
        }
    } catch(...) {
        close(_fd);
        _fd = -1;
        throw;
    }
}

TcpListener::~TcpListener() {
    if (_fd != -1) {
        close(_fd);
    }
}

int TcpListener::native_handle() const noexcept {
    return _fd;
}
