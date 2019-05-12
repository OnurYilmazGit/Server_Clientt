#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include "meal.h"

#define PORT 10000

struct sockaddr_in server; //Socket to listen connections
struct sockaddr_in client; //Socket for incoming connection
int server_fd; //Listening socket descriptor
int client_fd; //Incoming socket descriptor
char ongoingMessage[250] = ""; // Message from server
char incomingMessage[250] = ""; // Message from client

char MenuMessage[250] = {"Welcome to OzuRest! Please Pick your Order:\n0.Menemen \n1.Chicken Pasta \n2.Beef Steak \n3.Ali Nazik\n"}; //Pre determined message to be sent

 void start_server() {
    // Initialize server socket here
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int true = 1;
    setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)); // This line is to make sure the socket is reusable
    // Bind the socket here and make it listen to connections
    bind(server_fd,(struct sockaddr *)&server, sizeof(server));
    listen(server_fd,1);
  
}

void orderMeal(char* message) {
    // Message is incoming message from client
    // Invoke kitchen simulation in here
    // recv(client_fd,message, strlen(MenuMessage), 0);
    int result = atoi(message);
    prepare_meal(result);
}

void accept_connection() {
    // Accept connection from client in here
    int clen = sizeof(server);
    client_fd = accept(server_fd,(struct sockaddr *)&server,(socklen_t*)&clen);
}

void handle_connection(int socket_fd) {
    // Exchange messages with client in here
    strcpy(ongoingMessage, MenuMessage);
    write(socket_fd, ongoingMessage, sizeof(ongoingMessage));
    read(socket_fd, incomingMessage, sizeof(ongoingMessage));
    orderMeal(incomingMessage);
    strcpy(ongoingMessage, MenuMessage);
    write(socket_fd, ongoingMessage, sizeof(ongoingMessage));
    
}

int main() {
    start_server();
    printf("Started the server\n");
    while(1) {
        accept_connection();
        handle_connection(client_fd);
        break;
    }
}
