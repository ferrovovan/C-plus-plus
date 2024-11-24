#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>

#include "BitArray.hpp"

// Конструктор по умолчанию. Создаёт пустой битовый массив.
BitArray::BitArray() : num_bits(0) {}

// Деструктор по умолчанию.
BitArray::~BitArray() {}

// Конструктор, создающий массив с заданным количеством бит.
BitArray::BitArray(int num_bits, unsigned long value) : num_bits(num_bits) {
	bits.resize((num_bits + 7) / 8, 0); // метод контейнера vector
	for (int i = 0; i < static_cast<int>(sizeof(unsigned long) * 8) && i < num_bits; ++i) {
		set(i, (value >> i) & 1);
	}
}

// Конструктор копирования.
BitArray::BitArray(const BitArray& other) : bits(other.bits), num_bits(other.num_bits) {}



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

void BitArray::clear() {
	bits.clear(); // метод контейнера vector
	num_bits = 0;
}

void BitArray::push_back(bool bit) {
	resize(num_bits + 1, bit);
}

/* Битовые операции над массивами. */

BitArray& BitArray::operator&=(const BitArray& other) {
	if (num_bits != other.num_bits) throw std::invalid_argument("Размеры битовых массивов не совпадают.");
	for (size_t i = 0; i < bits.size(); ++i) {
		bits[i] &= other.bits[i];
	}
	return *this;
}

BitArray& BitArray::operator|=(const BitArray& other) {
	if (num_bits != other.num_bits) throw std::invalid_argument("Размеры битовых массивов не совпадают.");
	for (size_t i = 0; i < bits.size(); ++i) {
		bits[i] |= other.bits[i];
	}
	return *this;
}

BitArray& BitArray::operator^=(const BitArray& other) {
	if (num_bits != other.num_bits) throw std::invalid_argument("Размеры битовых массивов не совпадают.");
	for (size_t i = 0; i < bits.size(); ++i) {
		bits[i] ^= other.bits[i];
	}
	return *this;
}

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

/* Операторы битовый сдвига с заполнением нулями. */

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

BitArray BitArray::operator<<(int n) const {
	BitArray result(*this);
	result <<= n;
	return result;
}

BitArray BitArray::operator>>(int n) const {
	BitArray result(*this);
	result >>= n;
	return result;
}

/* Установление состояния. */

BitArray& BitArray::set(int n, bool val) {
	if (n >= num_bits) throw std::out_of_range("Индекс за пределами массива.");
	if (val) {
		bits[n / 8] |= (1 << (n % 8));
	} else {
		bits[n / 8] &= ~(1 << (n % 8));
	}
	return *this;
}

BitArray& BitArray::set() {
	std::fill(bits.begin(), bits.end(), 0xFF);
	return *this;
}

BitArray& BitArray::reset(int n) {
	if (n >= num_bits) throw std::out_of_range("Индекс за пределами массива.");
	bits[n / 8] &= ~(1 << (n % 8));
	return *this;
}

BitArray& BitArray::reset() {
	std::fill(bits.begin(), bits.end(), 0);
	return *this;
}

/* Считывание состояния. */

bool BitArray::any() const {
	for (unsigned char byte : bits) {
		if (byte) return true;
	}
	return false;
}

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

