#pragma once

#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>

/**
 * @brief Reads a fixed number of integers from a text file into a vector.
 *
 * This function reads exactly `lines` number of lines from the file at the given `filepath`.
 * Each line is expected to contain a single valid integer. The integers are stored in the
 * provided output vector `result`.
 *
 * @param[out] result An empty vector to store the parsed integers. The vector must be empty;
 *                    otherwise, the function throws an exception.
 * @param[in] filepath Path to the input text file. Each line must contain a valid integer.
 * @param[in] lines The number of lines (integers) expected to be read from the file.
 *
 * @throws std::invalid_argument If the output vector is not empty.
 * @throws std::runtime_error If the file cannot be opened.
 * @throws std::runtime_error If a line does not contain a valid integer.
 * @throws std::runtime_error If the file contains fewer than `lines` lines.
 *
 * @note This function does not clear the `result` vector. It assumes full ownership
 *       of writing to it and expects it to be empty at the start.
 *
 * @example
 * @code
 * std::vector<int> numbers;
 * read_ints(numbers, "numbers.txt", 100);
 * // numbers now contains 100 integers from the file
 * @endcode
 */
void read_ints(std::vector<int>& result, const std::string& filepath, int lines);
