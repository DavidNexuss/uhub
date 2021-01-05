#pragma once
#include <list>
#include <thread>
#include <string>
  
class ServerSocket
{
    const static int max_client_queue_size = 5;

    int port_number;
    int sockfd;
    std::list<std::thread> connections;

    public:
    ServerSocket(int _sockfd);
    ~ServerSocket();
    void listen_loop();
};