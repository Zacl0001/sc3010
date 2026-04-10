#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 9090

int main() {
    WSADATA wsa;
    SOCKET server_fd, client_sock;
    struct sockaddr_in server, client;
    int c = sizeof(client);

    struct {
        char buffer[1024];
        char secret[32];
    } memory;

    strcpy(memory.secret, "SUPER_SECRET_KEY_12345");

    char response[2048];

    WSAStartup(MAKEWORD(2,2), &wsa);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&server, sizeof(server));
    listen(server_fd, 1);

    printf("Fixed server listening on port %d...\n", PORT);

    while (1) {

        client_sock = accept(server_fd, (struct sockaddr*)&client, &c);
        if (client_sock == INVALID_SOCKET) continue;

        printf("Client connected\n");

        while (1) {
            memset(memory.buffer, 0, sizeof(memory.buffer));

            int received = recv(client_sock, memory.buffer, sizeof(memory.buffer), 0);

            if (received <= 0) {
                printf("Client disconnected\n");
                break;
            }

            if (received < (int)sizeof(unsigned short)) {
                printf("Invalid packet\n");
                continue;
            }

            unsigned short payload;
            memcpy(&payload, memory.buffer, sizeof(unsigned short));

            char *data = memory.buffer;
            int data_len = received - sizeof(unsigned short);

            printf("Received payload length: %hu\n", payload);

            // ✅ PATCH: prevent over-read
            if (payload > data_len || payload > (int)sizeof(response)) {
                printf("Blocked: invalid payload (possible attack)\n");
                continue;
            }

            memcpy(response, data, payload);
            send(client_sock, response, payload, 0);
        }

        closesocket(client_sock);
    }

    closesocket(server_fd);
    WSACleanup();

    return 0;
}