#include <gtest/gtest.h>
#include "../source/GameMatrix/MatrixReader.hpp"
#include "../source/GameMatrix/GameMatrix.hpp"
#include <fstream>

// Тест: базовый конструктор
TEST(MatrixReaderTest, Constructor_DefaultValues) {
    MatrixReader reader;

    // Ожидаем, что матрица заполнилась корректными значениями
    EXPECT_EQ(reader.getResult('C', 0), 7);
    EXPECT_EQ(reader.getResult('C', 1), 3);
    EXPECT_EQ(reader.getResult('C', 2), 0);
    EXPECT_EQ(reader.getResult('D', 0), 9);
    EXPECT_EQ(reader.getResult('D', 1), 5);
    EXPECT_EQ(reader.getResult('D', 2), 1);
}

// Тест: загрузка матрицы из файла
TEST(MatrixReaderTest, LoadMatrix_FromFile) {
    // Подготовьте тестовый файл
    const std::string file_path = "../config/matrices/Extreme Payoff for Solo Betrayal.conf";
    std::ofstream file(file_path);
    file << "choice;count;result\n";
    file << "C;0;4\n";
    file << "C;1;3\n";
    file << "D;0;5\n";
    file.close();

    // Загружаем матрицу из файла
    MatrixReader reader(file_path);

    EXPECT_EQ(reader.getResult('C', 0), 4);
    EXPECT_EQ(reader.getResult('C', 1), 3);
    EXPECT_EQ(reader.getResult('D', 0), 5);

    // Убедитесь, что исключение вызывается для неизвестного сочетания
    EXPECT_THROW(reader.getResult('X', 0), std::out_of_range);

    // Удаление тестового файла
    std::remove(file_path.c_str());
}

// Тест: некорректный файл
TEST(MatrixReaderTest, LoadMatrix_InvalidFile) {
    // Убедитесь, что неверный путь вызывает исключение
    EXPECT_THROW(MatrixReader reader("non_existent.txt"), std::runtime_error);
}

// Тест: некорректная строка в файле
/*
TEST(MatrixReaderTest, LoadMatrix_InvalidLine) {
    const std::string file_path = "test_invalid_line.txt";
    std::ofstream file(file_path);
    file << "choice;count;result\n";
    file << "Invalid;Line;Data\n";
    file.close();

    MatrixReader reader;

    // Загрузка файла должна бросить исключение
    EXPECT_THROW(reader.loadMatrix(file_path), std::runtime_error);

    // Удаление тестового файла
    std::remove(file_path.c_str());
}*/

// Тест: конструктор по умолчанию
TEST(GameMatrixTest, DefaultConstructor) {
    GameMatrix gameMatrix; // Ожидается, что матрица создаётся без выброса исключений
}
