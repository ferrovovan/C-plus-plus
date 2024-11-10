#include <gtest/gtest.h>
#include "Time.h"

// Тестирование конструктора по умолчанию
TEST(TimeTest, DefaultConstructor) {
    Time t;
    EXPECT_EQ(t.GetHours(), 0);
    EXPECT_EQ(t.GetMinutes(), 0);
    EXPECT_EQ(t.GetSeconds(), 0);
}

// Тестирование параметрического конструктора
TEST(TimeTest, ParametrizedConstructor) {
    Time t(10, 30, 45);
    EXPECT_EQ(t.GetHours(), 10);
    EXPECT_EQ(t.GetMinutes(), 30);
    EXPECT_EQ(t.GetSeconds(), 45);
}

// Тестирование конструктора копирования
TEST(TimeTest, CopyConstructor) {
    Time t1(5, 15, 25);
    Time t2 = t1;
    EXPECT_EQ(t2.GetHours(), 5);
    EXPECT_EQ(t2.GetMinutes(), 15);
    EXPECT_EQ(t2.GetSeconds(), 25);
}

// Тестирование оператора присваивания
TEST(TimeTest, AssignmentOperator) {
    Time t1(10, 20, 30);
    Time t2;
    t2 = t1;
    EXPECT_EQ(t2.GetHours(), 10);
    EXPECT_EQ(t2.GetMinutes(), 20);
    EXPECT_EQ(t2.GetSeconds(), 30);
}

// Тестирование оператора сложения с целым числом
TEST(TimeTest, PlusOperatorInt) {
    Time t(1, 20, 30);
    t = t + 5000; // Прибавим 5000 секунд = 20 s + 23m + 1h
    EXPECT_EQ(t.GetHours(), 2);
    EXPECT_EQ(t.GetMinutes(), 43);
    EXPECT_EQ(t.GetSeconds(), 50);
}

// Тестирование оператора сложения с объектом Time
TEST(TimeTest, PlusOperatorTime) {
    Time t1(1, 20, 30);
    Time t2(0, 45, 50);
    t1 += t2; // Ожидаем 2ч 6м 20с
    EXPECT_EQ(t1.GetHours(), 2);
    EXPECT_EQ(t1.GetMinutes(), 6);
    EXPECT_EQ(t1.GetSeconds(), 20);
}

// Тестирование оператора вычитания с объектом Time
TEST(TimeTest, MinusOperatorTime) {
    Time t1(2, 0, 0);
    Time t2(1, 30, 0);
    Time result = t1 - t2;  // Ожидаем 0ч 30м 0с
    EXPECT_EQ(result.GetHours(), 0);
    EXPECT_EQ(result.GetMinutes(), 30);
    EXPECT_EQ(result.GetSeconds(), 0);
}

// Тестирование оператора вычитания с целым числом
TEST(TimeTest, MinusOperatorInt) {
    Time t(2, 10, 15);
    t -= 1500; // Вычитаем 1500 секунд
    EXPECT_EQ(t.GetHours(), 1);
    EXPECT_EQ(t.GetMinutes(), 45);
    EXPECT_EQ(t.GetSeconds(), 15);
}

// Тестирование оператора сравнения
TEST(TimeTest, EqualityOperator) {
    Time t1(5, 15, 25);
    Time t2(5, 15, 25);
    EXPECT_TRUE(t1 == t2);
}

TEST(TimeTest, InequalityOperator) {
    Time t1(5, 15, 25);
    Time t2(4, 15, 25);
    EXPECT_FALSE(t1 == t2);
}

// Тестирование нормализации времени
TEST(TimeTest, NormalizeTest) {
    Time t(25, 100, 5000);  // Часы > 24, минуты > 60, секунды > 60
    t.Normalize();
    EXPECT_EQ(t.GetHours(), 4);    // Нормализуем часы
    EXPECT_EQ(t.GetMinutes(), 3); // Нормализуем минуты
    EXPECT_EQ(t.GetSeconds(), 20); // Нормализуем секунды
}

// Тест с ошибкой (некорректный результат)
TEST(TimeTest, FailTest) {
    Time t1(10, 30, 45);
    Time t2(5, 30, 45);
    EXPECT_EQ(t1.GetHours(), 5);  // Ошибка, потому что часы должны быть 10
}

// Тестирование метода ToSeconds()
TEST(TimeTest, ToSecondsTest) {
    Time t(1, 30, 45);
    EXPECT_EQ(t.ToSeconds(), 5445); // (1*3600 + 30*60 + 45 = 5445)
}

// Тестирование метода SetHours()
TEST(TimeTest, SetHoursTest) {
    Time t;
    t.SetHours(8);
    EXPECT_EQ(t.GetHours(), 8);
}

// Проверка на количество объектов
TEST(TimeTest, ObjectCountTest) {
    EXPECT_EQ(Time::GetObjectCount(), 0); // В момент начала теста объект еще не создан
    Time t1(5, 10, 15);
    EXPECT_EQ(Time::GetObjectCount(), 1); // Один объект должен быть создан
    Time t2 = t1;
    EXPECT_EQ(Time::GetObjectCount(), 2); // Второй объект после копирования
    {
        Time t3(7, 25, 30);
        EXPECT_EQ(Time::GetObjectCount(), 3); // Третий объект
    }
    EXPECT_EQ(Time::GetObjectCount(), 2); // Объект t3 был уничтожен
}

