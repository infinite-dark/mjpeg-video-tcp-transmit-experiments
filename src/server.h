#include <iostream>
#include <string>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>


class SocketServer {
public:
    void initialize(const std::string& ip, int port);
    void start();
    void listen();
    int accept() const;
    void run();
    void join();
    virtual void serve(int client) = 0;
    void stop();
    ~SocketServer();
private:
    struct sockaddr_in address;
    std::thread runner;
    int sockfd;
protected:
    bool running = false;
};