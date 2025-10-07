#include "logger.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 1024

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
    logger.log(LogLevel::DEBUG, "Broadcast enviado: " + msg);
}

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE];
    logger.log(LogLevel::INFO, "Novo cliente conectado.");

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(client_fd, buffer, sizeof(buffer), 0);

        if (bytes <= 0) {
            logger.log(LogLevel::WARN, "Cliente desconectado.");
            close(client_fd);

            std::lock_guard<std::mutex> lock(clients_mtx);
            clients.erase(std::remove(clients.begin(), clients.end(), client_fd), clients.end());
            break;
        }

        std::string msg(buffer);
        if (msg == "/quit") {
            logger.log(LogLevel::INFO, "Cliente enviou comando /quit.");
            close(client_fd);
            break;
        }

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
        logger.log(LogLevel::ERROR, "Falha ao criar socket.");
        return -1;
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        logger.log(LogLevel::ERROR, "Erro no bind().");
        return -1;
    }

    if (listen(server_fd, 5) < 0) {
        logger.log(LogLevel::ERROR, "Erro no listen().");
        return -1;
    }

    logger.log(LogLevel::INFO, "Servidor iniciado na porta " + std::to_string(PORT));

    while (true) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            logger.log(LogLevel::ERROR, "Erro no accept().");
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(clients_mtx);
            clients.push_back(new_socket);
        }

        std::thread(handle_client, new_socket).detach();
    }

    close(server_fd);
    return 0;
}
