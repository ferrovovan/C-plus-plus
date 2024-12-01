#include <iostream>
#include <string> // task_wrapper
/* контейнеры */
#include <vector>
#include <list>
#include <deque>
/**/
#include <memory> // Для умных указателей
#include "Time.hpp"


void echo_green(const std::string& text) {
	std::cout << "\033[0;32m" << text << "\033[0m" << std::endl;  // Вывод текста с зелёным цветом
}

// Обёртка для выполнения задачи
void task_wrapper(void (*task)(), const std::string& message) {
	echo_green("Начало " + message);
	task();
	echo_green("Конец "  + message);
}

// 1. Создание объекта в динамической памяти
void base_usage() {
	// 1.1 Создание одного объекта через new
	Time* single_time = new Time();
	delete single_time; // Удаление для вызова деструктора

	// 1.2 Создание массива объектов через new[]
	Time* time_array = new Time[3];
	delete[] time_array; // Удаление массива

	// 1.3 Рукотворная утечка памяти
	// single_time = new Time();
}

// 2. Создание стандартных контейнеров с объектами типа Time
void vector_usage() {
	Time t1(1, 2, 3);
	Time t2(2, 3, 4);
	std::cout << "До создания контейнера\n";
	// Создание вектора объектов Time
	std::vector<Time> time_vector; // Три объекта создаются автоматически
	std::cout << "Контейнер создан\n";
	time_vector.push_back(t1);
	std::cout << "Добавлен элемент 1\n";
	time_vector.push_back(t2);
	std::cout << "Добавлен элемент 2\n";
	time_vector.push_back(Time(2, 2, 2));
	std::cout << "Добавлен элемент 3\n";

	// Деструкторы вызываются автоматически
}

void list_usage() {
	Time t1(1, 2, 3);
	Time t2(2, 3, 4);
	std::cout << "До создания списка\n";
	// Создание списка объектов Time
	std::list<Time> time_list;
	std::cout << "Список создан\n";
	time_list.push_back(t1);
	std::cout << "Добавлен элемент 1\n";
	time_list.push_back(t2);
	std::cout << "Добавлен элемент 2\n";
	time_list.push_back(Time(3, 3, 3));
	std::cout << "Добавлен элемент 3\n";

	// Деструкторы вызываются автоматически
}

void deque_usage() {
	Time t1(1, 2, 3);
	Time t2(2, 3, 4);
	std::cout << "До создания очереди\n";
	// Создание дека объектов Time
	std::deque<Time> time_deque;
	std::cout << "Очередь создана создан\n";
	time_deque.push_back(t1);
	std::cout << "Добавлен элемент в конец 1\n";
	time_deque.push_front(t2);
	std::cout << "Добавлен элемент в начало 2\n";
	time_deque.push_back(Time(3, 3, 3));
	std::cout << "Добавлен элемент в конец 3\n";

	// Деструкторы вызываются автоматически
}

// 3. Создание умных указателей
void smart_pointers_usage() {
	// Создание unique_ptr
	std::unique_ptr<Time> unique_time = std::make_unique<Time>();

	// Создание shared_ptr
	std::shared_ptr<Time> shared_time = std::make_shared<Time>();

	// Создание shared_ptr на массив
	std::shared_ptr<Time[]> shared_array(new Time[4]); // Не поддерживает make_shared с массивом

	// Умные указатели освободят память автоматически
}

// 4. Объяснение вывода
int task_4() {
	/*
	При использовании стандартных контейнеров и умных указателей освобождение ресурсов происходит автоматически:
	
	+ Для std::vector и std::list деструкторы вызываются для всех элементов при выходе контейнера из области видимости.
	+ Умные указатели (unique_ptr, shared_ptr) вызывают деструктор, как только теряют владельца. Для shared_ptr важно учитывать, что объект освобождается только при снижении счётчика ссылок до нуля.
	
	Важно:
	+ Всегда ли требуется delete или delete[]?
	Нет, если используются умные указатели или стандартные контейнеры. В противном случае вызов delete и delete[] обязателен.
	*/
	return 0;
}

int main() {
	
	task_wrapper(base_usage, "базового использования");
	
	task_wrapper(vector_usage, "использования std::vector");
	task_wrapper(list_usage, "использования std::list");
	task_wrapper(deque_usage, "использования std::deque");
	
	task_wrapper(smart_pointers_usage, "использование умных указателей");
	return 0; // Умные указатели освободят память автоматически
}
