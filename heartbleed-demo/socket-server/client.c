#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 9090

int main() {
    int sock;
    struct sockaddr_in server;

    unsigned short payload;
    char data[1024];
    char buffer[2048];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    printf("Enter payload length: ");
    scanf("%hu", &payload);

    printf("Enter data: ");
    scanf("%s", data);

    // Build packet: [length][data]
    memcpy(buffer, &payload, sizeof(unsigned short));
    memcpy(buffer + sizeof(unsigned short), data, strlen(data));

    send(sock, buffer, sizeof(unsigned short) + strlen(data), 0);

    // Receive response
    int len = recv(sock, buffer, sizeof(buffer), 0);

    printf("\nReceived (%d bytes):\n", len);
    for (int i = 0; i < len; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    return 0;
}
