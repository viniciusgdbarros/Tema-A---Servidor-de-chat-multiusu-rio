#include "logger.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

Logger logger("server.log");
std::vector<int> clients;
std::mutex clients_mtx;

void broadcast(const std::string &msg, int sender_fd) {
    std::lock_guard<std::mutex> lock(clients_mtx);
    for (int client_fd : clients) {
        if (client_fd != sender_fd) {
            send(client_fd, msg.c_str(), msg.size(), 0);
        }
    }
}

void handle_client(int client_fd) {
    char buffer[1024];
    logger.log(LogLevel::INFO, "Novo cliente conectado.");

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes <= 0) {
            logger.log(LogLevel::WARN, "Cliente desconectado.");
            close(client_fd);

            // Remove da lista de clientes
            std::lock_guard<std::mutex> lock(clients_mtx);
            clients.erase(std::remove(clients.begin(), clients.end(), client_fd), clients.end());
            break;
        }

        std::string msg(buffer);
        logger.log(LogLevel::INFO, "Mensagem recebida: " + msg);
        broadcast(msg, client_fd);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    logger.log(LogLevel::INFO, "Servidor iniciado na porta " + std::to_string(PORT));

    while (true) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        {
            std::lock_guard<std::mutex> lock(clients_mtx);
            clients.push_back(new_socket);
        }

        std::thread(handle_client, new_socket).detach();
    }

    return 0;
}
