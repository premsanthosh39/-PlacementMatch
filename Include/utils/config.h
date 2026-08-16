#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <unordered_map>

class Config {
private:
    std::unordered_map<std::string, std::string> values;
public:
    bool load(const std::string& filename);
    std::string get(const std::string& key, const std::string& defaultValue = "") const;
};

#endif