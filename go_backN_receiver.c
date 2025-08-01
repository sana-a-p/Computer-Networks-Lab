#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define LOSS_PROBABILITY 30  // 30% chance of ACK loss

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int ack;

    srand(time(0));  // Random seed for ACK simulation

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for client
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server: Waiting for connection...\n");

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Server: Connection established.\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread == 0) break;

        ack = atoi(buffer);
        printf("Server: Received packet %d\n", ack);

        // Simulate ACK loss
        if (rand() % 100 < LOSS_PROBABILITY) {
            printf("Server: ACK for packet %d lost!\n\n", ack);
        } else {
            sleep(1);  // Simulate processing delay
            printf("Server: ACK sent for packet %d\n\n", ack);
            memset(buffer,0,BUFFER_SIZE);
            sprintf(buffer, "%d", ack);  // Send ACK
            send(new_socket, buffer, strlen(buffer)+1, 0);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}