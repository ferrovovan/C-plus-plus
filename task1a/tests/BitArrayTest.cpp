#include <gtest/gtest.h>
#include "BitArray.hpp"

// Тесты конструкторов
TEST(Constructors, Default_Constructor) {
	BitArray arr;
	EXPECT_TRUE(arr.empty());
	EXPECT_EQ(arr.size(), 0);
}

TEST(Constructors, Overloaded_Constructor) {
	BitArray arr(8, 0xAA);  // 10101010
	EXPECT_EQ(arr.size(), 8);
	EXPECT_EQ(arr.to_string(), "10101010");
}

TEST(Constructors, Copy_Constructor) {
	BitArray original(8, 0xAA);
	BitArray copy(original);
	EXPECT_EQ(copy.size(), original.size());
	EXPECT_EQ(copy.to_string(), original.to_string());
}

// Тесты изменения размера
TEST(Resize, Increase_Size) {
	BitArray arr(4, 0xF); // 1111
	arr.resize(8, false);
	EXPECT_EQ(arr.size(), 8);
	EXPECT_EQ(arr.to_string(), "00001111");
}

TEST(Resize, Decrease_Size) {
	BitArray arr(8, 0xFF); // 11111111
	arr.resize(4);
	EXPECT_EQ(arr.size(), 4);
	EXPECT_EQ(arr.to_string(), "1111");
}

// Тесты битовых операций над массивами
TEST(BitwiseOperations, Bitwise_AND) {
	BitArray arr1(4, 0b1100);
	BitArray arr2(4, 0b1010);
	arr1 &= arr2;
	EXPECT_EQ(arr1.to_string(), "1000");
}

TEST(BitwiseOperations, Bitwise_OR) {
	BitArray arr1(4, 0b1100);
	BitArray arr2(4, 0b1010);
	arr1 |= arr2;
	EXPECT_EQ(arr1.to_string(), "1110");
}

TEST(BitwiseOperations, Bitwise_XOR) {
	BitArray arr1(4, 0b1100);
	BitArray arr2(4, 0b1010);
	arr1 ^= arr2;
	EXPECT_EQ(arr1.to_string(), "0110");
}

TEST(BitwiseOperations, Bitwise_NOT) {
	BitArray arr(4, 0b1100);
	BitArray result = ~arr;
	EXPECT_EQ(result.to_string(), "0011");
}

// Тесты операторов сдвига
TEST(BitShiftOperations, Shift_Left) {
	BitArray arr(4, 0b1100);
	arr <<= 2;
	EXPECT_EQ(arr.to_string(), "0000");
}

TEST(BitShiftOperations, Shift_Right) {
	BitArray arr(4, 0b1100);
	arr >>= 2;
	EXPECT_EQ(arr.to_string(), "0011");
}

// Тесты изменения битового состояния
TEST(BitState, Set_Reset_Single_Bit) {
	BitArray arr(4, 0);
	arr.set(1);
	EXPECT_TRUE(arr[1]);
	arr.reset(1);
	EXPECT_FALSE(arr[1]);
}

TEST(BitState, Set_Reset_All_Bits) {
	BitArray arr(4, 0);
	arr.set();
	EXPECT_EQ(arr.to_string(), "1111");
	arr.reset();
	EXPECT_EQ(arr.to_string(), "0000");
}

// Тесты чтения состояния
TEST(StateChecks, Any) {
	BitArray arr(4, 0b0100);
	EXPECT_TRUE(arr.any());
	arr.reset();
	EXPECT_FALSE(arr.any());
}

TEST(StateChecks, None) {
	BitArray arr(4, 0b0000);
	EXPECT_TRUE(arr.none());
	arr.set(1);
	EXPECT_FALSE(arr.none());
}

TEST(StateChecks, Count) {
	BitArray arr(8, 0b11001100);
	EXPECT_EQ(arr.count(), 4);
}

// Тесты операций с массивом
TEST(Miscellaneous, Push_Back) {
	BitArray arr;
	arr.push_back(true);
	arr.push_back(false);
	EXPECT_EQ(arr.size(), 2);
	EXPECT_EQ(arr.to_string(), "01");
}

TEST(Miscellaneous, Clear) {
	BitArray arr(8, 0xFF);
	arr.clear();
	EXPECT_TRUE(arr.empty());
}

TEST(Miscellaneous, Swap) {
	BitArray arr1(4, 0b1010);
	BitArray arr2(4, 0b0101);
	arr1.swap(arr2);
	EXPECT_EQ(arr1.to_string(), "0101");
	EXPECT_EQ(arr2.to_string(), "1010");
}

// Тесты дружественных операторов
TEST(FriendOperators, Equality) {
	BitArray arr1(4, 0b1010);
	BitArray arr2(4, 0b1010);
	EXPECT_TRUE(arr1 == arr2);
}

TEST(FriendOperators, Inequality) {
	BitArray arr1(4, 0b1010);
	BitArray arr2(4, 0b0101);
	EXPECT_TRUE(arr1 != arr2);
}

TEST(FriendOperators, Bitwise_AND) {
	BitArray arr1(4, 0b1100);
	BitArray arr2(4, 0b1010);
	BitArray result = arr1 & arr2;
	EXPECT_EQ(result.to_string(), "1000");
}

TEST(FriendOperators, Bitwise_OR) {
	BitArray arr1(4, 0b1100);
	BitArray arr2(4, 0b1010);
	BitArray result = arr1 | arr2;
	EXPECT_EQ(result.to_string(), "1110");
}

TEST(FriendOperators, Bitwise_XOR) {
	BitArray arr1(4, 0b1100);
	BitArray arr2(4, 0b1010);
	BitArray result = arr1 ^ arr2;
	EXPECT_EQ(result.to_string(), "0110");
}

