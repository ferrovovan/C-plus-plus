#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>

#include "BitArray.h"

// Конструктор по умолчанию. Создаёт пустой битовый массив.
BitArray::BitArray() : num_bits(0) {}

// Конструктор, создающий массив с заданным количеством бит.
BitArray::BitArray(int num_bits, unsigned long value) : num_bits(num_bits) {
    bits.resize((num_bits + 7) / 8, 0);
    for (int i = 0; i < static_cast<int>(sizeof(unsigned long) * 8) && i < num_bits; ++i) {
        set(i, (value >> i) & 1);
    }
}

// Конструктор копирования.
BitArray::BitArray(const BitArray& other) : bits(other.bits), num_bits(other.num_bits) {}

// Деструктор по умолчанию.
BitArray::~BitArray() {}

// Метод для обмена значений двух битовых массивов.
void BitArray::swap(BitArray& other) {
    std::swap(bits, other.bits);
    std::swap(num_bits, other.num_bits);
}

// Оператор присваивания.
BitArray& BitArray::operator=(const BitArray& other) {
    if (this != &other) {
        BitArray temp(other);
        swap(temp);
    }
    return *this;
}

// Изменяет размер битового массива.
void BitArray::resize(int new_num_bits, bool value) {
    std::vector<unsigned char> new_bits((new_num_bits + 7) / 8, value ? 0xFF : 0x00);
    int min_bits = std::min(num_bits, new_num_bits);
    for (int i = 0; i < min_bits; ++i) {
        if ((*this)[i]) {
            new_bits[i / 8] |= (1 << (i % 8));
        }
    }
    bits.swap(new_bits);
    num_bits = new_num_bits;
}

// Очищает битовый массив.
void BitArray::clear() {
    bits.clear();
    num_bits = 0;
}

// Добавляет новый бит в конец массива.
void BitArray::push_back(bool bit) {
    resize(num_bits + 1, bit);
}

// Оператор побитового И с присваиванием.
BitArray& BitArray::operator&=(const BitArray& other) {
    if (num_bits != other.num_bits) throw std::invalid_argument("Размеры битовых массивов не совпадают.");
    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] &= other.bits[i];
    }
    return *this;
}

// Оператор побитового ИЛИ с присваиванием.
BitArray& BitArray::operator|=(const BitArray& other) {
    if (num_bits != other.num_bits) throw std::invalid_argument("Размеры битовых массивов не совпадают.");
    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] |= other.bits[i];
    }
    return *this;
}

// Оператор побитового исключающего ИЛИ с присваиванием.
BitArray& BitArray::operator^=(const BitArray& other) {
    if (num_bits != other.num_bits) throw std::invalid_argument("Размеры битовых массивов не совпадают.");
    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] ^= other.bits[i];
    }
    return *this;
}

// Оператор сдвига влево с присваиванием.
BitArray& BitArray::operator<<=(int n) {
    if (n >= num_bits) {
        clear();
        return *this;
    }
    for (int i = num_bits - 1; i >= n; --i) {
        set(i, (*this)[i - n]);
    }
    for (int i = 0; i < n; ++i) {
        set(i, 0);
    }
    return *this;
}

// Оператор сдвига вправо с присваиванием.
BitArray& BitArray::operator>>=(int n) {
    if (n >= num_bits) {
        clear();
        return *this;
    }
    for (int i = 0; i < num_bits - n; ++i) {
        set(i, (*this)[i + n]);
    }
    for (int i = num_bits - n; i < num_bits; ++i) {
        set(i, 0);
    }
    return *this;
}

// Оператор сдвига влево без изменения исходного массива.
BitArray BitArray::operator<<(int n) const {
    BitArray result(*this);
    result <<= n;
    return result;
}

// Оператор сдвига вправо без изменения исходного массива.
BitArray BitArray::operator>>(int n) const {
    BitArray result(*this);
    result >>= n;
    return result;
}

// Устанавливает бит с индексом n в значение val.
BitArray& BitArray::set(int n, bool val) {
    if (n >= num_bits) throw std::out_of_range("Индекс за пределами массива.");
    if (val) {
        bits[n / 8] |= (1 << (n % 8));
    } else {
        bits[n / 8] &= ~(1 << (n % 8));
    }
    return *this;
}

// Заполняет весь массив единичными битами.
BitArray& BitArray::set() {
    std::fill(bits.begin(), bits.end(), 0xFF);
    return *this;
}

// Сбрасывает бит с индексом n.
BitArray& BitArray::reset(int n) {
    return set(n, false);
}

// Заполняет весь массив нулями.
BitArray& BitArray::reset() {
    std::fill(bits.begin(), bits.end(), 0);
    return *this;
}

// Возвращает true, если в массиве есть хотя бы один бит, равный истине.
bool BitArray::any() const {
    for (unsigned char byte : bits) {
        if (byte) return true;
    }
    return false;
}

// Возвращает true, если все биты в массиве равны лжи.
bool BitArray::none() const {
    return !any();
}

// Оператор побитовой инверсии.
BitArray BitArray::operator~() const {
    BitArray result(*this);
    for (unsigned char& byte : result.bits) {
        byte = ~byte;
    }
    return result;
}

// Подсчитывает количество битов, равных единице.
int BitArray::count() const {
    int cnt = 0;
    for (unsigned char byte : bits) {
        for (int i = 0; i < 8; ++i) {
            if (byte & (1 << i)) ++cnt;
        }
    }
    return cnt;
}

// Оператор доступа к биту по индексу.
bool BitArray::operator[](int n) const {
    if (n >= num_bits) throw std::out_of_range("Индекс за пределами массива.");
    return bits[n / 8] & (1 << (n % 8));
}

// Возвращает количество бит в массиве.
int BitArray::size() const {
    return num_bits;
}

// Проверяет, пустой ли массив.
bool BitArray::empty() const {
    return num_bits == 0;
}

// Возвращает строковое представление битового массива.
std::string BitArray::to_string() const {
    std::string result(num_bits, '0');
    for (int i = 0; i < num_bits; ++i) {
        if ((*this)[i]) {
            result[num_bits - i - 1] = '1';
        }
    }
    return result;
}

// Оператор сравнения (равенство).
bool operator==(const BitArray& a, const BitArray& b) {
    return a.num_bits == b.num_bits && a.bits == b.bits;
}

// Оператор сравнения (неравенство).
bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

// Оператор побитового И.
BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result &= b2;
    return result;
}

// Оператор побитового ИЛИ.
BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result |= b2;
    return result;
}

// Оператор побитового исключающего ИЛИ.
BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result ^= b2;
    return result;
}

