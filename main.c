#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define USR_IP "192.168.0.23"
#define USR_PORT 8899

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
        struct sockaddr_in usr_r16;

        usr_r16.sin_family = AF_INET;

        usr_r16.sin_port = htons(USR_PORT);

        inet_pton(AF_INET, USR_IP, &usr_r16.sin_addr.s_addr);

        int fd_data = socket(AF_INET, SOCK_STREAM, 0);

        if(fd_data < 0)
        {
                 handle_error("socket()");
        }
        else
        {
                printf("Socket created\n");
        }

        int req = connect(fd_data, (const struct sockaddr *) &usr_r16, sizeof(struct sockaddr_in));

        if (req < 0)
        {
            handle_error("connect()");
        }
        else
        {
                printf("Connect\n");
        }

        char buffer[256] = {0};
        char command[] = "admin\r\n";

        req = send(fd_data, command, strlen(command), 0);
        if (req < 0) 
        {
                    handle_error("send() login");
        }

        req = recv(fd_data, buffer, 256, 0);
        if (req < 0)
        {
                    handle_error("recv() login");
        }

        printf("%s\n", buffer);
       
        char command_to_rele[] = "\x55\xaa\x00\x03\x00\x03\x02\x03";

        req = send(fd_data, command_to_rele, sizeof command_to_rele, 0);
        if (req < 0)     
        {
                    handle_error("send() command");
        }

        req = recv(fd_data, buffer, 256, 0);
        if (req < 0)
        {
                    handle_error("recv() command");
        }

        printf("%s\n", buffer);

        close(fd_data);
        exit(EXIT_SUCCESS);
}
