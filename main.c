#include "argument-valid.h"
#include "all-off.h"
#include "debug.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char ip[1024] = {0};
    char port[1024] = {0};
    argument_valid(argc, argv, ip, port);

    unsigned int num_port = 0;
    num_port = atoi(port);

    struct sockaddr_in usr_r16;
    usr_r16.sin_family = AF_INET;
    usr_r16.sin_port = htons(num_port);
    inet_pton(AF_INET, ip, &usr_r16.sin_addr.s_addr);

    int fd_data = socket(AF_INET, SOCK_STREAM, 0);
    
    if(fd_data < 0)
    {
    	handle_error("socket()");
    }

    int req = connect(fd_data, (const struct sockaddr *) &usr_r16, sizeof(struct sockaddr_in));
    
    if (req < 0)
    {	
	close(fd_data);
	handle_error("connect()");
    }

    char buffer[256] = {0};
    char command[] = "admin\r\n";

    req = send(fd_data, command, strlen(command), 0);
    
    if (req < 0)
    {
	close(fd_data);
        handle_error("send()");
    }

    req = recv(fd_data, buffer, 256, 0);
    
    if (req < 0)
    {	
	close(fd_data);
        handle_error("recv() login");
    }

    printf("%s\n", buffer);

    //char command_to_rele[32] = {0};
    char command_to_rele [] = "\x55\xaa\x00\x03\x00\x03\x02\x03";
    //all_off(command_to_rele);
    
    req = send(fd_data, command_to_rele, sizeof command_to_rele, 0);
    
    if (req < 0)
    {
	close(fd_data);
	handle_error("send() command");
    }

    req = recv(fd_data, buffer, 256, 0);
    
    if (req < 0)
    {	
	close(fd_data);
	handle_error("recv() command");
    }

    printf("%s\n", buffer);

    close(fd_data);
    exit(EXIT_SUCCESS);
    
    return 0;
}

