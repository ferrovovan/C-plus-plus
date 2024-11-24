#ifndef BITARRAY_H
#define BITARRAY_H

#include <vector>
#include <string>
#include <stdexcept>


// Класс BitArray представляет динамический битовый массив,
// позволяющий выполнять различные побитовые операции.
class BitArray {
private:
	std::vector<unsigned char> bits; // Вектор для хранения битов в виде байтов.
	int num_bits; // Количество бит в массиве.
public:
	BitArray(); // конструктор по умолчанию. создаёт пустой битовый массив.
	~BitArray(); // Деструктор по умолчанию

	// Конструктор, создающий массив с заданным количеством бит.
	// Параметр value используется для инициализации первых sizeof(long) бит.
	explicit BitArray(int num_bits, unsigned long value = 0);

	// Конструктор копирования.
	BitArray(const BitArray& other);

	// Метод для обмена значений двух битовых массивов.
	void swap(BitArray& other);

	// Оператор присваивания.
	BitArray& operator=(const BitArray& other);

	// Тесты операций с массивом

	// Изменяет размер битового массива. Новые биты инициализируются значением value.
	void resize(int new_num_bits, bool value = false);
	void clear(); // Очищает битовый массив.
	void push_back(bool bit); // Добавляет новый бит в конец массива.


	//Битовые операции над массивами.
	//Работают только на массивах одинакового размера.

	// Оператор побитового И с присваиванием (&=).
	BitArray& operator&=(const BitArray& other);
	// Оператор побитового ИЛИ с присваиванием (|=).
	BitArray& operator|=(const BitArray& other);
	// Оператор побитового исключающего ИЛИ с присваиванием (^=).
	BitArray& operator^=(const BitArray& other);

	// Операторы битовый сдвига с заполнением нулями.

	BitArray& operator<<=(int n); // Оператор сдвига влево с присваиванием (<<=).
	BitArray& operator>>=(int n); // Оператор сдвига вправо с присваиванием (>>=).
	BitArray operator<<(int n) const; // Оператор сдвига влево без изменения исходного массива (<<).
	BitArray operator>>(int n) const; // Оператор сдвига вправо без изменения исходного массива (>>).

	// Установление состояния.

	BitArray& set(int n, bool val = true); // Устанавливает бит с индексом n в значение val.
	BitArray& set(); // Заполняет весь массив единичными битами (истина).
	BitArray& reset(int n); // Сбрасывает бит с индексом n (устанавливает его в ложь).
	BitArray& reset(); // Заполняет весь массив нулями (ложь).

	// Считывание состояния.
	
	bool any() const; // Возвращает true, если в массиве есть хотя бы один бит, равный истине.
	bool none() const; // Возвращает true, если все биты в массиве равны лжи.

	BitArray operator~() const; // Оператор побитовой инверсии (~).

	int count() const; // Подсчитывает количество битов, равных единице.

	bool operator[](int n) const; // Оператор доступа к биту по индексу (читает значение бита).

	int size() const; // Возвращает количество бит в массиве.

	bool empty() const; // Проверяет, пустой ли массив (количество бит равно 0).

	std::string to_string() const; // Возвращает строковое представление битового массива (например, "101010").

	// Дружественные функции для сравнения массивов.
	friend bool operator==(const BitArray& a, const BitArray& b);
	friend bool operator!=(const BitArray& a, const BitArray& b);
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

