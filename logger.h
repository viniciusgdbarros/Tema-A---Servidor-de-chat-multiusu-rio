#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <chrono>
#include <ctime>

enum class LogLevel { INFO, WARN, ERROR, DEBUG };

class Logger {
private:
    std::mutex mtx;
    std::ofstream logfile;
    bool toFile;

    std::string timestamp() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        char buf[20];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&in_time_t));
        return std::string(buf);
    }

    std::string levelToString(LogLevel level) {
        switch(level) {
            case LogLevel::INFO:  return "INFO";
            case LogLevel::WARN:  return "WARN";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::DEBUG: return "DEBUG";
            default: return "UNKNOWN";
        }
    }

public:
    Logger(const std::string& filename = "") {
        if (!filename.empty()) {
            logfile.open(filename, std::ios::app);
            toFile = true;
        } else {
            toFile = false;
        }
    }

    ~Logger() {
        if (logfile.is_open())
            logfile.close();
    }

    void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        std::string entry = "[" + timestamp() + "] " + levelToString(level) + ": " + message;

        if (toFile && logfile.is_open())
            logfile << entry << std::endl;
        else
            std::cout << entry << std::endl;
    }
};

#endif
