#include "input.h"

int32_t read_int(const std::string &filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file '" + filepath + "'.");
    }

    std::string line;
    if (std::getline(file, line)) {
        try {
            return std::stoi(line);
        } catch (const std::exception &) {
            throw std::runtime_error("Invalid integer.");
        }
    } else {
        throw std::runtime_error("No integer found.");
    }
}

void read_ints(std::vector<int32_t> &result, const std::string &filepath,
               uint32_t lines) {
    if (!result.empty()) {
        throw std::invalid_argument(
            "Expected empty vector as output parameter.");
    }

    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file '" + filepath + "'.");
    }

    result.reserve(lines);
    std::string line;
    uint32_t count = 0;
    while (count < lines && std::getline(file, line)) {
        try {
            result.emplace_back(std::stoi(line));
        } catch (const std::exception &) {
            throw std::runtime_error("Invalid integer on line " +
                                     std::to_string(count + 1) + ".");
        }
        count++;
    }

    if (count < lines) {
        throw std::runtime_error("Expected " + std::to_string(lines) +
                                 " lines but got " + std::to_string(count));
    }
}

void read_int_pairs(std::vector<std::pair<int32_t, int32_t>> &result,
                    const std::string &filepath, uint32_t lines) {
    if (!result.empty()) {
        throw std::invalid_argument(
            "Expected empty vector as output parameter.");
    }

    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file '" + filepath + "'.");
    }

    result.reserve(lines);
    std::string line;
    uint32_t count = 0;
    while (count < lines && std::getline(file, line)) {
        try {
            size_t space_pos = line.find(' ');

            if (space_pos == std::string::npos) {
                throw std::runtime_error("No space separator on line " +
                                         std::to_string(count + 1) + ".");
            }

            std::string first_part = line.substr(0, space_pos);
            std::string second_part = line.substr(space_pos + 1);

            if (first_part.empty() || second_part.empty()) {
                throw std::runtime_error("One integer missing on line " +
                                         std::to_string(count + 1) + ".");
            }

            result.emplace_back(std::stoi(first_part), std::stoi(second_part));
        } catch (const std::exception &) {
            throw std::runtime_error("Invalid integer pair on line " +
                                     std::to_string(count + 1) + ".");
        }
        count++;
    }

    if (count < lines) {
        throw std::runtime_error("Expected " + std::to_string(lines) +
                                 " lines but got " + std::to_string(count));
    }
}
