#include "utils/config.h"
#include <fstream>
#include <sstream>

bool Config::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq);
        std::string value = line.substr(eq + 1);
        values[key] = value;
    }
    return true;
}

std::string Config::get(const std::string& key, const std::string& defaultValue) const {
    auto it = values.find(key);
    if (it == values.end()) return defaultValue;
    return it->second;
}