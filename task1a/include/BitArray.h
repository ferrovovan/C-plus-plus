#ifndef BITARRAY_H
#define BITARRAY_H

#include <vector>
#include <string>
#include <stdexcept>


// Класс BitArray представляет динамический битовый массив,
// позволяющий выполнять различные побитовые операции.
class BitArray {
public:
	// конструктор по умолчанию. создаёт пустой битовый массив.
	BitArray();

	// Конструктор, создающий массив с заданным количеством бит.
	// Параметр value используется для инициализации первых sizeof(long) бит.
	explicit BitArray(int num_bits, unsigned long value = 0);

	// Конструктор копирования.
	BitArray(const BitArray& other);

	// Деструктор (по умолчанию).
	~BitArray();

	// Метод для обмена значений двух битовых массивов.
	void swap(BitArray& other);

	// Оператор присваивания.
	BitArray& operator=(const BitArray& other);

	// Изменяет размер битового массива. Новые биты инициализируются значением value.
	void resize(int new_num_bits, bool value = false);

	// Очищает битовый массив.
	void clear();

	// Добавляет новый бит в конец массива.
	void push_back(bool bit);

	// Оператор побитового И с присваиванием (&=).
	// Работает только на массивах одинакового размера.
	BitArray& operator&=(const BitArray& other);

	// Оператор побитового ИЛИ с присваиванием (|=).
	// Работает только на массивах одинакового размера.
	BitArray& operator|=(const BitArray& other);

	// Оператор побитового исключающего ИЛИ с присваиванием (^=).
	// Работает только на массивах одинакового размера.
	BitArray& operator^=(const BitArray& other);

	// Оператор сдвига влево с присваиванием (<<=).
	BitArray& operator<<=(int n);

	// Оператор сдвига вправо с присваиванием (>>=).
	BitArray& operator>>=(int n);

	// Оператор сдвига влево без изменения исходного массива (<<).
	BitArray operator<<(int n) const;

	// Оператор сдвига вправо без изменения исходного массива (>>).
	BitArray operator>>(int n) const;

	// Устанавливает бит с индексом n в значение val.
	BitArray& set(int n, bool val = true);

	// Заполняет весь массив единичными битами (истина).
	BitArray& set();

	// Сбрасывает бит с индексом n (устанавливает его в ложь).
	BitArray& reset(int n);

	// Заполняет весь массив нулями (ложь).
	BitArray& reset();

	// Возвращает true, если в массиве есть хотя бы один бит, равный истине.
	bool any() const;

	// Возвращает true, если все биты в массиве равны лжи.
	bool none() const;

	// Оператор побитовой инверсии (~).
	BitArray operator~() const;

	// Подсчитывает количество битов, равных единице.
	int count() const;

	// Оператор доступа к биту по индексу (читает значение бита).
	bool operator[](int n) const;

	// Возвращает количество бит в массиве.
	int size() const;

	// Проверяет, пустой ли массив (количество бит равно 0).
	bool empty() const;

	// Возвращает строковое представление битового массива (например, "101010").
	std::string to_string() const;

	// Дружественные функции для сравнения массивов.
	friend bool operator==(const BitArray& a, const BitArray& b);
	friend bool operator!=(const BitArray& a, const BitArray& b);

private:
	// Вектор для хранения битов в виде байтов.
	std::vector<unsigned char> bits;

	// Количество бит в массиве.
	int num_bits;
};

// Оператор сравнения двух битовых массивов (равенство).
bool operator==(const BitArray& a, const BitArray& b);

// Оператор сравнения двух битовых массивов (неравенство).
bool operator!=(const BitArray& a, const BitArray& b);

// Операторы побитовых операций для массивов (и, или, исключающее или).
BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif // BITARRAY_H

