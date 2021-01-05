#include "server.hpp"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include "net.hpp"
int main()
{
    ServerSocket server(create_unix_server("server",SOCK_STREAM));
    server.listen_loop();
}