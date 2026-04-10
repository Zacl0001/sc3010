#include <stdio.h>
#include <string.h>

int main() {
    char buffer[64];
    char response[128];

    unsigned short payload;
    char data[64];

    printf("Server started (fixed)...\n");

    while (1) {
        printf("\nWaiting for request...\n");

        scanf("%hu", &payload);
        scanf("%s", data);

        printf("Received payload length: %hu\n", payload);

        // FIX: bounds check
        if (payload > strlen(data)) {
            printf("Invalid payload length! Attack blocked.\n");
            continue;
        }

        memcpy(response, data, payload);

        printf("Response sent: %.*s\n", payload, response);
    }

    return 0;
}