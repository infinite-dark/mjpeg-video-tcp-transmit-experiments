#include "server.h"

void SocketServer::initialize(const std::string& ip, int port) {
    int status = inet_pton(AF_INET, ip.c_str(), (void*)&address.sin_addr);
    if (status <= 0)
        return;

    address.sin_port = htons(port);
    address.sin_family = AF_INET;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return;
    std::cout << "initialized\n";
}

void SocketServer::start() {
    int status = bind(sockfd, (sockaddr*)&address, sizeof(address));
    if (status < 0)
        return;

    running = true;
    runner = std::thread([this] { this->run(); });
    std::cout << "ready\n";
}

void SocketServer::listen() {
    std::cout << "listening: ";
    int status = ::listen(sockfd, 1);
    if (status < 0) {
        running = false;
        std::cout << "fail\n";
    }
    std::cout << "success\n";
}

int SocketServer::accept() const {
    struct sockaddr_in caddress{};
    socklen_t len = sizeof(caddress);
    std::cout << "connecting: ";
    int client = ::accept(sockfd, (sockaddr*)&caddress, &len);
    if (client < 0) {
        std::cout << "fail\n";
        return -1;
    }
    std::cout << "success\n";
    return client;
}

void SocketServer::run() {
    if(!running)
        return;
    else {
        std::cout << "starting...\n";
        int client;

        while (running) {
            SocketServer::listen();
            client = SocketServer::accept();
            serve(client);

            shutdown(client, SHUT_RDWR);
            close(client);
        }
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);
    }
}

void SocketServer::join() {
    if (runner.joinable())
        runner.join();
}

void SocketServer::stop() {
    running = false;
    if (runner.joinable())
        runner.join();
}

SocketServer::~SocketServer() {
    SocketServer::stop();
}
