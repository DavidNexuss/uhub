#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h>  
#include "server.hpp"
#include "util.hpp"

#define SA struct sockaddr 

using namespace std;

ServerSocket::ServerSocket(int _sockfd) : sockfd(_sockfd)
{ 
}

void ServerSocket::listen_loop()
{

    LOG("[SSocket] Listening %d..",sockfd);
    struct sockaddr_in cli = { 0 };
    socklen_t addr_len = sizeof(cli);
    int confd;
    while((confd = accept(sockfd,(SA*)&cli,&addr_len)) > 0)
    {

        LOG("[SSocket] Accepting %d - %d..",sockfd,confd);
        thread child([confd](){
            int s = 256;
            int n;
            char buf[s];
            while((n = read(confd,buf,s)) > 0)
            {
                write(0,buf,n);
            }
        });
        connections.push_back(move(child));
    }
}

ServerSocket::~ServerSocket()
{
    for(thread& t : connections)
        t.join();
}