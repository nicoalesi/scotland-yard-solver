#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief Reads a single integer from the first line of a text file.
 *
 * This function opens the file specified by `filepath` and attempts to read
 * the first line. It expects the line to contain a single valid integer,
 * which it parses and returns.
 *
 * @param[in] filepath Path to the input text file. The first line must contain
 * a valid integer.
 *
 * @return The integer value parsed from the first line of the file.
 *
 * @throws std::runtime_error If the file cannot be opened.
 * @throws std::runtime_error If the file is empty or no lines can be read.
 * @throws std::runtime_error If the first line does not contain a valid
 * integer.
 *
 * @note Only the first line of the file is read. Additional content is ignored.
 *
 * @example
 * @code
 * int value = read_int("input.txt");
 * // value now contains the integer read from the first line of input.txt
 * @endcode
 */
int read_int(const std::string &filepath);

/**
 * @brief Reads a fixed number of integers from a text file into a vector.
 *
 * This function reads exactly `lines` number of lines from the file at the
 * given `filepath`. Each line is expected to contain a single valid integer.
 * The integers are stored in the provided output vector `result`.
 *
 * @param[out] result An empty vector to store the parsed integers. The vector
 * must be empty; otherwise, the function throws an exception.
 * @param[in] filepath Path to the input text file. Each line must contain a
 * valid integer.
 * @param[in] lines The number of lines (integers) expected to be read from the
 * file.
 *
 * @throws std::invalid_argument If the output vector is not empty.
 * @throws std::invalid_argument If `lines` is negative.
 * @throws std::runtime_error If the file cannot be opened.
 * @throws std::runtime_error If a line does not contain a valid integer.
 * @throws std::runtime_error If the file contains fewer than `lines` lines.
 *
 * @note This function does not clear the `result` vector. It assumes full
 * ownership of writing to it and expects it to be empty at the start.
 *
 * @example
 * @code
 * std::vector<int> numbers;
 * read_ints(numbers, "numbers.txt", 100);
 * // numbers now contains 100 integers from the file
 * @endcode
 */
void read_ints(std::vector<int> &result, const std::string &filepath,
               int lines);

/**
 * @brief Reads a fixed number of integer pairs from a text file into a vector.
 *
 * This function reads exactly `lines` number of lines from the file at the
 * given `filepath`. Each line is expected to contain exactly two valid integers
 * separated by a space. The integer pairs are stored in the provided output
 * vector `result`.
 *
 * @param[out] result An empty vector to store the parsed integer pairs. The
 * vector must be empty; otherwise, the function throws an exception.
 * @param[in] filepath Path to the input text file. Each line must contain
 * exactly two integers separated by a space.
 * @param[in] lines The number of lines (integer pairs) expected to be read from
 * the file.
 *
 * @throws std::invalid_argument If the output vector is not empty.
 * @throws std::invalid_argument If `lines` is negative.
 * @throws std::runtime_error If the file cannot be opened.
 * @throws std::runtime_error If a line does not contain exactly two valid
 * integers.
 * @throws std::runtime_error If the file contains fewer than `lines` lines.
 *
 * @note This function does not clear the `result` vector. It assumes full
 * ownership of writing to it and expects it to be empty at the start.
 *
 * @example
 * @code
 * std::vector<std::pair<int, int>> pairs;
 * read_int_pairs(pairs, "pairs.txt", 50);
 * // pairs now contains 50 integer pairs from the file
 * @endcode
 */
void read_int_pairs(std::vector<std::pair<int, int>> &result,
                    const std::string &filepath, int lines);
