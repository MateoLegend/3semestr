#include <iostream>
#include "json.hpp"
#include <fstream>
#include <unordered_map>
#include <string>
#include <stdexcept>
using json = nlohmann::json;

class Config {
public:

    static Config& getInstance() {
        static Config instance;
        return instance;
    }

    /* dla stringa */
    void set(const std::string &key, const std::string &value) {
        stringConfig[key] = value;
    }
    /* dla inta */
    void set(const std::string &key, const int value) {
        intConfig[key] = value;
    }

    std::string getString(const std::string &key){
        if(stringConfig.find(key) != stringConfig.end()){
            return stringConfig[key];
        }
        else
            throw std::runtime_error("Klucz dla string nie znaleziony: " + key);
        
    }

    int getInt(const std::string &key){
        if(intConfig.find(key) != intConfig.end()){
            return intConfig[key];
        }
        else
            throw std::runtime_error("Klucz dla int nie znaleziony: " + key);
    }

    // jeszcze jakas metoda co zwraca referencje do obiektu singletonowego


private:
    std::unordered_map<std::string, std::string> stringConfig;
    std::unordered_map<std::string, int> intConfig;

    const std::string configFile = "config.json";

    Config() {
        loadConfig();
    }
    ~Config(){
        saveConfig();
    }

void loadConfig() {
        std::ifstream file(configFile);
        if (file.is_open()) {
            json j;
            file >> j;

            if (j.contains("stringConfig")) {
                stringConfig = j["stringConfig"].get<std::unordered_map<std::string, std::string>>();
            }

            if (j.contains("intConfig")) {
                intConfig = j["intConfig"].get<std::unordered_map<std::string, int>>();
            }

            file.close();
        }
    }

    void saveConfig() {
        json j;
        j["stringConfig"] = stringConfig;
        j["intConfig"] = intConfig;

        std::ofstream file(configFile);
        if (file.is_open()) {
            file << j.dump(4); // Pretty print with 4 spaces
            file.close();
        }
    }

    // Disable copy constructor and assignment operator
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};

int main() {
    Config& config = Config::getInstance();

    // Set some configuration values
    config.set("username", "admin");
    config.set("max_connections", 100);

    // Retrieve configuration values
    try {
        std::string username = config.getString("username");
        int maxConnections = config.getInt("max_connections");

        std::cout << "Username: " << username << "\n";
        std::cout << "Max Connections: " << maxConnections << "\n";
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}