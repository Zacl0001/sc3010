#include <stdio.h>

int main() {
    unsigned short payload;
    char data[64];

    printf("Enter payload length: ");
    scanf("%hu", &payload);

    printf("Enter data: ");
    scanf("%s", data);

    printf("\nSend this to server:\n");
    printf("%hu %s\n", payload, data);

    return 0;
}