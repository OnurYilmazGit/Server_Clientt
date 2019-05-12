#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define PORT 10000

struct sockaddr_in client;
int client_fd;
char ongoingMessage[250] = ""; // Message from client
char incomingMessage[250] = "";// Message from server

void connectServer() {
    // Connect server in here
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    connect(client_fd, (struct sockaddr *)&client, sizeof(client));
}

void handleConnection(int socket_fd) {
    // Exchange messages with server here
    read(client_fd, incomingMessage, sizeof(incomingMessage));
    char name[20];
    printf(incomingMessage);
    scanf("%s", &name);
    strcpy(ongoingMessage, name);
    write(client_fd, ongoingMessage, sizeof(ongoingMessage));
}

int main() {
    connectServer();
    handleConnection(client_fd);
    close(client_fd);
    exit(0);
}
