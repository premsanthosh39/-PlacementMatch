#include "utils/logger.h"
#include <iostream>
#include <fstream>
#include <ctime>

void logevent(const std::string& message) {
    std::ofstream file("logs/app.log", std::ios::app);
    if (!file.is_open()) {
        std::cout << "Warning: Log file could not be opened\n";
        return;
    }
    std::time_t now = std::time(nullptr);
    std::string timestamp = std::ctime(&now);
    if (!timestamp.empty() && timestamp.back() == '\n') timestamp.pop_back();

    file << "[" << timestamp << "] " << message << "\n";
}