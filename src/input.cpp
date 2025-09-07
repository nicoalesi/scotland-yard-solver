#include "input.h"


void read_ints(std::vector<int>& result, const std::string& filepath, int lines) {
    if (!result.empty()) {
        throw std::invalid_argument("Expected empty vector as output parameter.");
    }

    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file '" + filepath + "'.");
    }

    result.reserve(lines);
    std::string line;
    int count = 0;
    while (count < lines && std::getline(file, line)) {
        try {
            result.push_back(std::stoi(line));
        } catch (const std::exception&) {
            throw std::runtime_error("Invalid integer on line " + std::to_string(count + 1) + ".");
        }
        count++;
    }

    if (count < lines) {
        throw std::runtime_error("Expected " + std::to_string(lines) + " lines but got " + std::to_string(count));
    }
}