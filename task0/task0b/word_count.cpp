#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

// Функция для проверки, является ли символ разделителем (все символы кроме букв и цифр)
bool isSeparator(char c) {
    // Функция isalnum проверяет, является ли символ буквой или цифрой.
    return !isalnum(static_cast<unsigned char>(c));
}

// Функция для разбивания строки на слова с использованием списка
list<string> split(const string& line) {
    list<string> words;
    string word;
    for (char c : line) {
        if (isSeparator(c)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += tolower(c); // Приведение символов к нижнему регистру
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

// Функция для подсчета слов и их частоты из файла
map<string, int> countWords(ifstream& inputFile, int& totalWords) {
    map<string, int> wordCount;
    string line;

    while (getline(inputFile, line)) {
        list<string> words = split(line);
        for (const string& word : words) {
            wordCount[word]++;
            totalWords++;
        }
    }

    return wordCount;
}

// Функция для сортировки слов по частоте
list<pair<string, int>> sortWordsByFrequency(const map<string, int>& wordCount) {

    list<pair<string, int>> sortedWords(wordCount.begin(), wordCount.end());

    sortedWords.sort([](const auto& a, const auto& b) {
        return a.second > b.second; // Сортировка по убыванию частоты
    });

    return sortedWords;
}

// Функция для записи результата в CSV файл
void writeToCSV(ofstream& outputFile, const list<pair<string, int>>& sortedWords, int totalWords) {
    outputFile << "Word,Count,Percentage\n";

    for (const auto& [word, count] : sortedWords) {
        double percentage = (count * 100.0) / totalWords;
        outputFile << word << "," << count << "," << fixed << setprecision(2) << percentage << "\n";
    }
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input.txt output.csv\n";
        return 1;
    }

    // Открытие входного файла
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error: Could not open input file.\n";
        return 1;
    }

    // Открытие выходного файла
    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Error: Could not open output file.\n";
        return 1;
    }

    // Подсчёт слов и их частоты
    int totalWords = 0;
    map<string, int> wordCount = countWords(inputFile, totalWords);

    // Сортировка слов по частоте
    list<pair<string, int>> sortedWords = sortWordsByFrequency(wordCount);

    // Запись результата в CSV
    writeToCSV(outputFile, sortedWords, totalWords);

    cout << "CSV file created successfully.\n";
    return 0;
}

