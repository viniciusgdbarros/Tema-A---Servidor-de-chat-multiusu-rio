#include "logger.h"
#include <thread>
#include <vector>

void worker(Logger& logger, int id) {
    for (int i = 0; i < 5; i++) {
        logger.log(LogLevel::INFO, "Thread " + std::to_string(id) + " logging message " + std::to_string(i));
    }
}

int main() {
    Logger logger("output.log");

    const int numThreads = 5;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(worker, std::ref(logger), i);
    }

    for (auto& t : threads) {
        t.join();
    }

    logger.log(LogLevel::INFO, "All threads finished logging.");

    return 0;
}
