#include "logger.h"
#include <iostream>
#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 1024

Logger logger("client.log");

void receive_messages(int sock) {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(sock, buffer, sizeof(buffer), 0);
        if (bytes <= 0) {
            logger.log(LogLevel::WARN, "Servidor desconectado.");
            break;
        }
        std::cout << "\n[Broadcast] " << buffer << std::endl;
    }
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        logger.log(LogLevel::ERROR, "Erro ao criar socket do cliente.");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        logger.log(LogLevel::ERROR, "Endereço inválido.");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        logger.log(LogLevel::ERROR, "Falha na conexão com o servidor.");
        return -1;
    }

    logger.log(LogLevel::INFO, "Conectado ao servidor.");
    std::thread receiver(receive_messages, sock);

    std::string msg;
    while (true) {
        std::getline(std::cin, msg);
        if (msg == "/quit") {
            send(sock, msg.c_str(), msg.size(), 0);
            break;
        }
        send(sock, msg.c_str(), msg.size(), 0);
    }

    close(sock);
    receiver.detach();
    return 0;
}
