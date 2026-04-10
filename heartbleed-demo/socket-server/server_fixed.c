#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090

int main() {
    int server_fd, client_sock;
    struct sockaddr_in server, client;
    socklen_t c = sizeof(client);

    char buffer[1024];
    char response[2048];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&server, sizeof(server));
    listen(server_fd, 1);

    printf("Fixed server listening on port %d...\n", PORT);

    client_sock = accept(server_fd, (struct sockaddr*)&client, &c);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int received = recv(client_sock, buffer, sizeof(buffer), 0);

        unsigned short payload;
        memcpy(&payload, buffer, sizeof(unsigned short));

        char *data = buffer + sizeof(unsigned short);
        int actual_data_len = received - sizeof(unsigned short);

        printf("Received payload length: %hu\n", payload);

        // FIX
        if (payload > actual_data_len) {
            printf("Attack detected! Blocking request.\n");
            continue;
        }

        memcpy(response, data, payload);
        send(client_sock, response, payload, 0);
    }

    return 0;
}