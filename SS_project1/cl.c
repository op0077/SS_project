#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    // Create a socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server\n");

    // Login
    printf("Enter username: ");
    fgets(buffer, sizeof(buffer), stdin);
    send(client_socket, buffer, strlen(buffer), 0);

    printf("Enter password: ");
    fgets(buffer, sizeof(buffer), stdin);
    send(client_socket, buffer, strlen(buffer), 0);

    // Receive login status from the server
    int valread = read(client_socket, buffer, sizeof(buffer));
    if (valread <= 0) {
        printf("Server disconnected\n");
        close(client_socket);
        return 0;
    }

    printf("Server: %s\n", buffer);

    if (strncmp(buffer, "You are logged in.", 18) != 0) {
        close(client_socket);
        return 0;
    }

    // Continuously send and receive messages
    while (1) {
        // Send a message to the server
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, strlen(buffer), 0);

        int valread = read(client_socket, buffer, sizeof(buffer));
        if (valread <= 0) {
            printf("Server disconnected\n");
            break;
        }

        printf("Server: %s\n", buffer);
    }

    // Close the client socket
    close(client_socket);

    return 0;
}
    