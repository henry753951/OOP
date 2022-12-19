#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
std::string getConfig(std::string key) {
    std::ifstream cFile("config.txt");
    if (cFile.is_open()) {
        std::string line;
        while (getline(cFile, line)) {
            line.erase(std::remove_if(line.begin(), line.end(), isspace),
                       line.end());
            if (line[0] == '#' || line[0] == '[' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            std::string name = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            if (name == key)
                return value;
        }
        return "";

    } else {
        std::cerr << "Couldn't open config file for reading.\n";
        return "";
    }
};