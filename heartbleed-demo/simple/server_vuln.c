#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    char secret[32] = "TOP_SECRET_KEY_123456";
    char buffer[64];
    char response[128];

    unsigned short payload;
    char data[64];

    printf("Server started (vulnerable)...\n");

    while (1) {
        printf("\nWaiting for request...\n");

        // Simulate receiving payload length + data
        scanf("%hu", &payload);
        scanf("%s", data);

        printf("Received payload length: %hu\n", payload);

        // Vulnerability: no bounds check
        memcpy(response, data, payload);

        printf("Response sent: ");
        for (int i = 0; i < payload; i++) {
            printf("%c", response[i]);
        }
        printf("\n");
    }

    return 0;
}