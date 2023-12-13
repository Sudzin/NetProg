#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int clientSocket, portNum, n;
    struct sockaddr_in serverAddr;
    char buffer[1024];
	
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    memset((char *) &serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7);
    serverAddr.sin_addr.s_addr = inet_addr("82.179.90.12");

    if (connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    std::string message;
    std::cout << "Enter a message: ";
    std::getline(std::cin, message);
    n = write(clientSocket, message.c_str(), message.length());
    if (n < 0) {
        std::cerr << "Error writing to socket" << std::endl;
        return 1;
    }

    memset(buffer, 0, 1024);
    n = read(clientSocket, buffer, 1023);
    if (n < 0) {
        std::cerr << "Error reading from socket" << std::endl;
        return 1;
    }
    std::cout << "Server response: " << buffer << std::endl;

    close(clientSocket);

    return 0;
}
