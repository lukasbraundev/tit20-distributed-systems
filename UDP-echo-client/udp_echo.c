#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888
#define MAX_BUFFER_SIZE 1024
#define RETURN_MESSAGE_SIZE 1028 // maximum length of return message

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;
    char buffer[MAX_BUFFER_SIZE], return_message[RETURN_MESSAGE_SIZE];
    socklen_t client_address_length = sizeof(client_address);
    int message_count = 0;

    // create UDP socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // bind socket to address and port
    memset((char *) &server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    printf("UDP echo server listening on port %d...\n", PORT);

    while (1) {
        // receive message from client
        memset(buffer, 0, sizeof(buffer)); // initialize buffer to all zeros
        if (recvfrom(server_socket, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &client_address, &client_address_length) < 0) {
            perror("Error receiving message");
            exit(EXIT_FAILURE);
        }

        printf("Received message #%d from %s:%d: %s\n", ++message_count, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), buffer);

        // construct return message
        int message_length = snprintf(return_message, RETURN_MESSAGE_SIZE, "%04d:%s", message_count, buffer);
        if (message_length < 0 || message_length >= RETURN_MESSAGE_SIZE) {
            fprintf(stderr, "Error constructing return message\n");
            exit(EXIT_FAILURE);
        }

        // send message back to client
        if (sendto(server_socket, return_message, message_length, 0, (struct sockaddr *) &client_address, client_address_length) < 0) {
            perror("Error sending message");
            exit(EXIT_FAILURE);
        }

        printf("Sent message #%d back to %s:%d\n", message_count, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
    }

    close(server_socket);
    return 0;
}
