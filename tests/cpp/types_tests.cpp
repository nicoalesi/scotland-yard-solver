// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

#include <gtest/gtest.h>

#include "types.h"

// No error
TEST(to_uint8_int32, ConvertsCorrectly) {
    EXPECT_EQ(0, to_uint8(0));
    EXPECT_EQ(255, to_uint8(255));
}

// Throw if negative
TEST(to_uint8_int32, ThrowIfNegative) {
    EXPECT_THROW(to_uint8(-1), std::invalid_argument);
}

// Throw if out of range
TEST(to_uint8_int32, ThrowIfOutOfRange) {
    EXPECT_THROW(to_uint8(256), std::invalid_argument);
}

// No error
TEST(to_uint8_size_t, ConvertsCorrectly) {
    EXPECT_EQ(0, to_uint8(static_cast<size_t>(0)));
    EXPECT_EQ(255, to_uint8(static_cast<size_t>(255)));
}

// Throw if out of range
TEST(to_uint8_size_t, ThrowIfOutOfRange) {
    EXPECT_THROW(to_uint8(static_cast<size_t>(256)), std::invalid_argument);
    EXPECT_THROW(to_uint8(static_cast<size_t>(UINT16_MAX)),
                 std::invalid_argument);
}

// No error
TEST(to_uint16_int32, ConvertsCorrectly) {
    EXPECT_EQ(0, to_uint16(0));
    EXPECT_EQ(65535, to_uint16(65535));
}

// Throw if negative
TEST(to_uint16_int32, ThrowIfNegative) {
    EXPECT_THROW(to_uint16(-1), std::invalid_argument);
}

// Throw if out of range
TEST(to_uint16_int32, ThrowIfOutOfRange) {
    EXPECT_THROW(to_uint16(65536), std::invalid_argument);
}

// No error
TEST(to_uint32_int32, ConvertsCorrectly) {
    EXPECT_EQ(0, to_uint32(0));
    EXPECT_EQ(123456789, to_uint32(123456789));
}

// Throw if negative
TEST(to_uint32_int32, ThrowIfNegative) {
    EXPECT_THROW(to_uint32(-1), std::invalid_argument);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
