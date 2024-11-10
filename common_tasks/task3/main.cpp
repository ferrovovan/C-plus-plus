#include "Time.h"

void echo_green(const std::string& text) {
	std::cout << "\n\033[0;32m" << text << "\033[0m" << std::endl;  // Вывод текста с зелёным цветом
}

/* начало блока с перегрузкой ввода-вывода */
std::ostream& operator << (std::ostream& out, const Time& t) {
	out << t.GetHours() << ":" << t.GetMinutes() << ":" << t.GetSeconds();
	return out;
}

std::istream& operator >> (std::istream& in, Time& t) {
	int h, m, s;
	char tmp;
	// Считываем число и любой непробельный символ за ним
	in >> h >> tmp;
	in >> m >> tmp;
	in >> s >> tmp;

	t = Time(h, m, s);
	return in;
}

void test_read_and_print() {
	echo_green("Проверка чтения и ввода:");
	Time t;  // создаём экземпляр класса Time
	std::cout << "Введите время в формате час \\n минуты \\n секунды \\n\n";
	std::cin >> t; // Считываем время в формате hh:mm:ss
	std::cout << "Введённое вами время: " << t << "\n";  // печатаем время в формате hh:mm:ss
}
/* конец  блока с перегрузкой ввода-вывода */

void test_normalization() {
	echo_green("Проверка нормализации:");
	int h = 30, m = -120, s = 61;
	std::cout << "Вводное время: "
			<< "H=" << h
			<< " M=" << m
			<< " S=" << s
			<< std::endl;
	Time t(h, m, s);
	std::cout << "Результат: ";
	t.PrintTime();
}

void test_subtraction() {
	echo_green("Проверка вычитания:");
	Time t1(23, 0, 0);
	t1.PrintTime();
	std::cout << "Минус\n";
	Time t2(3, 1, 1);
	t2.PrintTime();
	Time t3 = t1 - t2;
	std::cout << "Равно\n";
	t3.PrintTime(); // Результат вычитания
}

void test_ToSeconds() {
	echo_green("Проверка перевода в секунды:");
	Time t(1, 2, 1);
	std::cout << "Вводное время: ";
	t.PrintTime();
	std::cout << "Seconds since start of the day: " << t.ToSeconds() << "\n";
}

int main() {
	// test_read_and_print();

	test_normalization();
	test_ToSeconds();
	test_subtraction();

	return 0;
}
