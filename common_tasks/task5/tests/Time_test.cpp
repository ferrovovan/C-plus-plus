#include <gtest/gtest.h>
#include "Time.hpp"

// Тесты для конструкторов
TEST(Constructors, Default_Constructor) {
	Time t;
	EXPECT_EQ(t.GetHours(), 0);
	EXPECT_EQ(t.GetMinutes(), 0);
	EXPECT_EQ(t.GetSeconds(), 0);
}

TEST(Constructors, Parameterized_Constructor) {
	Time t(10, 15, 30);
	EXPECT_EQ(t.GetHours(), 10);
	EXPECT_EQ(t.GetMinutes(), 15);
	EXPECT_EQ(t.GetSeconds(), 30);
}

TEST(Constructors, Copy_Constructor) {
	Time t1(10, 15, 30);
	Time t2(t1);
	EXPECT_EQ(t2.GetHours(), t1.GetHours());
	EXPECT_EQ(t2.GetMinutes(), t1.GetMinutes());
	EXPECT_EQ(t2.GetSeconds(), t1.GetSeconds());
}

// Тесты для операторов сложения
TEST(Operators, Add_Seconds_To_Object) {
	Time t(1, 59, 50);
	t += 20;  // 1:59:50 + 20 секунд = 2:00:10
	EXPECT_EQ(t.GetHours(), 2);
	EXPECT_EQ(t.GetMinutes(), 0);
	EXPECT_EQ(t.GetSeconds(), 10);
}

TEST(Operators, Add_Object_To_Seconds) {
	Time t1(2, 30, 45);
	Time t2 = t1 + 75;  // 2:30:45 + 75 секунд = 2:32:00
	EXPECT_EQ(t2.GetHours(), 2);
	EXPECT_EQ(t2.GetMinutes(), 32);
	EXPECT_EQ(t2.GetSeconds(), 0);
}

TEST(Operators, Add_Objects) {
	Time t1(2, 30, 45);
	Time t2(1, 45, 30);
	t1 += t2;  // 2:30:45 + 1:45:30 = 4:16:15
	EXPECT_EQ(t1.GetHours(), 4);
	EXPECT_EQ(t1.GetMinutes(), 16);
	EXPECT_EQ(t1.GetSeconds(), 15);
}

// Тесты для операторов вычитания
TEST(Operators, Subtract_Seconds_From_Object) {
	Time t(2, 0, 10);
	t -= 20;  // 2:00:10 - 20 секунд = 1:59:50
	EXPECT_EQ(t.GetHours(), 1);
	EXPECT_EQ(t.GetMinutes(), 59);
	EXPECT_EQ(t.GetSeconds(), 50);
}

TEST(Operators, Subtract_Object_From_Seconds) {
	Time t1(2, 0, 10);
	Time t2 = t1 - 15;  // 2:00:10 - 15 секунд = 2:00:55
	EXPECT_EQ(t2.GetHours(), 1);
	EXPECT_EQ(t2.GetMinutes(), 59);
	EXPECT_EQ(t2.GetSeconds(), 55);
}

TEST(Operators, Subtract_Objects) {
	Time t1(2, 30, 45);
	Time t2(1, 45, 30);
	Time result = t1 - t2;  // 2:30:45 - 1:45:30 = 0:45:15
	EXPECT_EQ(result.GetHours(), 0);
	EXPECT_EQ(result.GetMinutes(), 45);
	EXPECT_EQ(result.GetSeconds(), 15);
}

// Тесты для операторов сравнения
TEST(Operators, Equality_Operator) {
	Time t1(2, 30, 45);
	Time t2(2, 30, 45);
	EXPECT_TRUE(t1 == t2);

	Time t3(1, 45, 30);
	EXPECT_FALSE(t1 == t3);
}

// Тесты для нормализации
TEST(Normalization, Normalize_Positive) {
	Time t(25, 61, 3665);  // 25 часов, 61 минута, 3665 секунд
	EXPECT_EQ(t.GetHours(), 3);
	EXPECT_EQ(t.GetMinutes(), 2);
	EXPECT_EQ(t.GetSeconds(), 5);
}

TEST(Normalization, Normalize_Negative) {
	Time t(-1, -61, -3665);  // -1 час, -61 минута, -3665 секунд
	EXPECT_EQ(t.GetHours(), 20);
	EXPECT_EQ(t.GetMinutes(), 57);
	EXPECT_EQ(t.GetSeconds(), 55);
}

// Тесты для статического члена
TEST(Static, Object_Count) {
	int initial_count = Time::GetObjectCount();
	Time t1, t2, t3;
	EXPECT_EQ(Time::GetObjectCount(), initial_count + 3);
	{
		Time t4;
		EXPECT_EQ(Time::GetObjectCount(), initial_count + 4);
	}
	EXPECT_EQ(Time::GetObjectCount(), initial_count + 3);
}


