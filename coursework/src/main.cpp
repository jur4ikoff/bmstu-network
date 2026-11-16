#include "webserver/tcp_listener.hpp"
#include "config.hpp"

#include <exception>
#include <iostream>

int main()
{
    try
    {
        const ListenConfig config("127.0.0.1", 8080);
        TcpListener listener(config);

        std::cout
            << "Listening on "
            << config.address() << ':' << config.port()
            << '\n';
    }
    catch (const std::exception &error)
    {
        std::cerr << "Startup failed: " << error.what() << '\n';
        return 1;
    }

    return 0;
}