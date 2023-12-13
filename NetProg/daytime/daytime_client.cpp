#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <server_ip_address> <port>" << std::endl;
        return 1;
    }

    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        std::cerr << "Недопустимый адрес/ Адрес, который не поддерживается" << std::endl;
        return 1;
    }

    sendto(sockfd, "GET TIME", strlen("GET TIME"), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    buffer[n] = '\0';
    std::cout << "Текущее время: " << buffer;

    close(sockfd);
    return 0;
}
