#include "input.h"

int read_int(const std::string &filepath) {
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

void read_ints(std::vector<int> &result, const std::string &filepath,
               int lines) {
    if (!result.empty()) {
        throw std::invalid_argument(
            "Expected empty vector as output parameter.");
    }

    if (lines < 0) {
        throw std::invalid_argument(
            "Expected positive integer as number of lines.");
    }

    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file '" + filepath + "'.");
    }

    result.reserve((size_t)lines);
    std::string line;
    int count = 0;
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

void read_int_pairs(std::vector<std::pair<int, int>> &result,
                    const std::string &filepath, int lines) {
    if (!result.empty()) {
        throw std::invalid_argument(
            "Expected empty vector as output parameter.");
    }

    if (lines < 0) {
        throw std::invalid_argument(
            "Expected positive integer as number of lines.");
    }

    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file '" + filepath + "'.");
    }

    result.reserve((size_t)lines);
    std::string line;
    int count = 0;
    while (count < lines && std::getline(file, line)) {
        try {
            size_t space_pos = line.find(' ');

            if (space_pos == std::string::npos) {
                throw std::runtime_error("No space.");
            }

            std::string first_part = line.substr(0, space_pos);
            std::string second_part = line.substr(space_pos + 1);

            if (first_part.empty() || second_part.empty()) {
                throw std::runtime_error("One integer missing.");
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