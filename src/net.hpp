#pragma once

#define SA struct sockaddr

int create_inet_server(int port_number,int client_queue);
int create_inet_conn(const char* hostname,int port_number);

int create_unix_server(const char *path, int type);
int create_unix_connection(const char *path, int type);