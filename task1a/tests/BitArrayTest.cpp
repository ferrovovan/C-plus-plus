#include <gtest/gtest.h>
#include "BitArray.h"

TEST(BitArrayTest, BasicOperations) {
    BitArray arr(8, 0xAA);  // 10101010
    EXPECT_EQ(arr.size(), 8);
    EXPECT_EQ(arr[0], false);
    EXPECT_EQ(arr[1], true);
    EXPECT_EQ(arr[2], false);

    arr.set(0);
    EXPECT_EQ(arr[0], true);

    arr.reset(1);
    EXPECT_EQ(arr[1], false);
}

TEST(BitArrayTest, ResizeAndPushBack) {
    BitArray arr;
    arr.push_back(true);
    arr.push_back(false);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], true);
    EXPECT_EQ(arr[1], false);

    arr.resize(5, true);
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[2], true);
}

TEST(BitArrayTest, BitwiseAndOrXor) {
    BitArray arr1(8, 0xAA);  // 10101010
    BitArray arr2(8, 0x55);  // 01010101

    arr1 &= arr2;
    EXPECT_EQ(arr1.to_string(), "00000000");

    arr1 |= arr2;
    EXPECT_EQ(arr1.to_string(), "01010101");

    arr1 ^= arr2;
    EXPECT_EQ(arr1.to_string(), "00000000");
}

TEST(BitArrayTest, ShiftOperations) {
    BitArray arr(8, 0xAA);  // 10101010

    arr <<= 1;
    EXPECT_EQ(arr.to_string(), "01010100");

    arr >>= 2;
    EXPECT_EQ(arr.to_string(), "00010101");
}

TEST(BitArrayTest, AnyNoneCount) {
    BitArray arr(8, 0x00);
    EXPECT_FALSE(arr.any());
    EXPECT_TRUE(arr.none());

    arr.set(1);
    EXPECT_TRUE(arr.any());
    EXPECT_EQ(arr.count(), 1);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

