#pragma once
#include <string>
#include <thread>

class Client
{
    std::string hostname;
    int port;
    
    std::thread thread;

    public:
    Client(std::string _hostname,int _port);
    ~Client();
};