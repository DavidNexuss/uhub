#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include "net.hpp"
#include "util.hpp"

int create_inet_server(int port_number,int max_client_queue)
{
    struct sockaddr_in servaddr = { 0 };
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        return -1;
    }
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(port_number);
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        return -1;
    }

    if ((listen(sockfd, max_client_queue)) != 0) {
        return -1;
    } 
    LOG("[INET] SSocket created %d",sockfd);
    return sockfd;
}

int create_inet_connection(const char* name,int port_number)
{
    int sock = 0, valread; 
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port_number); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, name, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }
    return sock;
}

int unix_build_address(const char *path, struct sockaddr_un *addr)
{
    if (addr == NULL || path == NULL) {
        errno = EINVAL;
        return -1;
    }

    memset(addr, 0, sizeof(struct sockaddr_un));
    addr->sun_family = AF_UNIX;
    if (strlen(path) < sizeof(addr->sun_path)) {
        strncpy(addr->sun_path, path, sizeof(addr->sun_path) - 1);
        return 0;
    } else {
        errno = ENAMETOOLONG;
        return -1;
    }
}

int create_unix_server(const char *path, int type)
{
    int sd, savedErrno;
    struct sockaddr_un addr;

    if (unix_build_address(path, &addr) == -1)
        return -1;

    sd = socket(AF_UNIX, type, 0);
    if (sd == -1)
        return -1;

    if (bind(sd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        close(sd); 
        return -1;
    }
    LOG("[UNIX] SSocket created %d for %s",sd,path);
    return sd;
}

int create_unix_connection(const char *path, int type)
{
    int sd;
    struct sockaddr_un addr;
    if (unix_build_address(path, &addr) == -1)
        return -1;

    sd = socket(AF_UNIX, type, 0);
    if (sd == -1)
        return -1;

    if (connect(sd, (struct sockaddr *) &addr,
                sizeof(struct sockaddr_un)) == -1) {
        close(sd);
        return -1;
    }

    return sd;
}