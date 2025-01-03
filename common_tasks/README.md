## Описание
Базовые задачи от семинариста. Для освоения основ `C++`.

## Запуск
Чтобы проверить задание, нужно перейти в папку `task$i` и:
* Для номеров с 1 по 4:
```shell
./scripts/run.sh
```
* Для остальный (с `CMakeLists.txt`):
```
./scripts/build.sh
./scripts/run.sh
```

## Условия задач:
### 1. Квадратное уравнение
Написать и вызвать функцию, решающую квадратное уравнение.

### 2. Общие буквы слов
Вам даны слова (вводите сами). Выведите в алфавитном порядке список общих букв всех слов.
**Формат входных данных:**
По одному слову в строке. Слова состоят из маленьких букв латинского алфавита.

**Формат выходных данных:**
Вывести в алфавитном порядке без пробелов список букв, которые присутствуют в каждом слове.

**Пример 1:**

**Вход:**  
`apple`  
`peach`  
`orange`

**Выход:**  
`ae`



### 3. Определение )объявление( Класса Time
**Исходный код:**
```
#include <iostream>

class Time {
private:
	int hours, minutes, seconds;
public:
	Time(){}; // defaults
	Time(int h, int m, int s): hours(h), minutes(m), seconds(s){}
	Time(const Time&); // конструктор копирования
	// делегирование конструктора
	Time(const Time& t): Time(t.hours, t.minutes, t.seconds){}

	Time& operator = (const Time& other){
		this->hours = other.hours; // явное указания на член класса
		minutes = other.minutes;   // неявное указание
		seconds = other.seconds;
		return *this;
	}

	Time& operator += (int s) {
		seconds += s;
		// Normalize();
		return *this;
	}

//    Time operator + (int s) const { // вариант "член класса"
//        return Time(hours, minutes, seconds + s);
//    } // Позволяет только "Time + int". Но имеет доступ к приватным полям объекта напрямую.

	Time operator + (const Time& t, int s) {  // вариант "внешняя функция"
		return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
	} // Этот оператор позволяет только "Time + int", так как аргументы жёстко определены: первым должен быть объект Time, а вторым — int
	
	Time operator + (int s, const Time& t) {  // вариант "внешняя функция"
		return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
	} // Добавление поддержки "int + Time"

	~Time(){} // деструктор

	int GetHours() const { return hours; }
	int GetMinutes() const { return minutes; }
	int GetSeconds() const { return seconds; }

	// void Normalize(); // реализовать
	// int ToSeconds() const; // реализовать

	void PrintTime(){
		std::cout << "H:" << this->GetHours()
			<< " M:" << this->GetMinutes()
			<< " S:" << this->GetSeconds()
			<< std::endl;
	}
};
```

**Задание:**  
Дополнить класс `Time`:
- методом `Normalize()`, нормализующим данные в классе `Time`, то есть приводя время в диапазон от `00:00:00` до `23:59:59`. Значения вне  диапазона младшего разряда изменяют значения старшего разряда.
- методом `ToSeconds()`, переводящим хранящееся значение времени в количество секунд. 
- операторами “-”, “-=” (по аналогии с “+” и “+=”) и “==”.

### 4. Расширение класса Time
1. Добавить в реализацию класса Time (см. предыдущее задание) счётчик созданных объектов. При создании объекта класса Time (конструкторы) счётчик увеличивается, в деструкторе - уменьшается.
2. Добавить в конструкторы (и деструктор) вывод сообщения о вызове данного конструктора. Дополнительно к наименованию конструктора вывести текущее количество (после создания конструктором или уничтожения деструктором) объектов данного класса (см. пункт 1).
3. Проанализировать сообщения выводимые следующей функцией:
```  
int main()
{
	Time t;
	t.SetHours(1);
	Time t2 = t;
	t2.SetHours(2);
	t2.PrintTime();
	{
		t2.SetHours(12);
		t2.PrintTime();
		Time t2(22, 22, 22);
		t2.PrintTime();
	}
	t2.PrintTime();
	Time t3(3, 3, 3);
	t3 = t;
	t3.SetHours(3);
	t3.PrintTime();
}
```
*Примечание:* Это буквально проверка добавленных возможностей.

### 5. Использование CMake и GTest
Продолжение работы с классом Time:
1. Собрать с использованием CMake.
2. Добавить тестирование (через GoogleTest ) на каждый конструктор, оператор и функцию (от 3 групп тестов). Сделать намеренно несколько тестов провальными.
3. Организовать возможность сборки без тестов (выбор на этапе конфигурации)

### 6.1. Создание объектов класса Time в динамической памяти:
#### Теория  
**Классическая работа с памятью**  
Операторы:
- Освобождение - `delete`, `delete[]`
- Создание - `new`, `new[]`  
Потенциальные проблемы:
- Утечка объектов (`new` без `delete`)
- Преждевременное удаление
- Двойное удаление

**Современный подход с использованием RAII**  
В отличие от классической работы с памятью, где управление ресурсами возлагается на программиста,  
идиома RAII (Resource Acquisition Is Initialization) автоматизирует этот процесс,  
связывая жизненный цикл ресурса с жизненным циклом объекта.  

Ключевые принципы:  
- Захват ресурса при создании объекта (конструктор) и его освобождение при уничтожении (деструктор), что исключает утечки памяти и двойное освобождение.  
- Управление ресурсами ограничивается областью видимости, что снижает риск преждевременного удаления.  

Более удачные названия идиомы (по Бьярне Страуструпу):  
- CADR (Constructor Acquires, Destructor Releases) — конструктор захватывает, деструктор освобождает.  
- SBRM (Scope-Bound Resource Management) — управление ресурсами с привязкой к области видимости.  


**Примеры использования**
- Единоличный "умный" указатель `std::unique_ptr`  
Только один объект может владеть этим указателем и управлять ресурсом.
```
#include <memory> // для умных указателей
int main() {
	int* ptr = new int(17); // обычный указатель
	delete ptr; // важно не забыть!
	
	// А это — умный указатель
	std::unique_ptr<int> smart = std::make_unique<int>(17); // вместо new int(17)
	//эквивалентно  std::unique_ptr<int> smart { std::make_unique<int>(17) };

	// Можно работать как с обычным указателем — у него перегружены соответствующие операторы:
	std::cout << *smart << "\n"; // 17
	// auto ptr2 = ptr1; // копирование запрещено
	// ptr.reset(); // устанавливает nullptr
	
	unsigned n{5}; // размер массива
	auto pnumbers { std::make_unique<int[]>(n) }; // массив {0, 0, 0, 0, 0}    
	pnumbers[1] = 11; // изменяем значение
}
// вызывать delete не надо, выделенная память освободится при выходе из блока
```

- Общий "умный" указатель `std::shared_ptr`  
Предоставляет совместное владение ресурсом, где несколько указателей могут одновременно владеть одним объектом.  
Освобождение ресурса происходит автоматически, когда последний `std::shared_ptr`, связанный с этим объектом, уничтожается или переназначается.
```
#include <iostream> // для ввода-вывода
#include <memory> // для умных указателей
int main() {
	std::shared_ptr<int> ptr1 = std::make_shared<int>(17);
	std::cout << *ptr1 << "\n"; // 17
	std::cout << ptr1.use_count() << "\n"; // 1
	auto ptr2 = ptr1; // копирование разрешено!
	std::cout << *ptr1 << "\n"; // 17
	std::cout << *ptr2 << "\n"; // 17 — это всё тот же объект
	std::cout << ptr1.use_count() << "\n"; // 2
	std::cout << ptr2.use_count() << "\n"; // 2
	std::shared_ptr<int> ptr3;
	std::cout << ptr3.use_count() << "\n"; // 0
	
	ptr3 = ptr1; // присваивание тоже разрешено!
	std::cout << *ptr3 << "\n"; // 17
	std::cout << ptr1.use_count() << "\n"; // 3
	std::cout << ptr2.use_count() << "\n"; // 3
	std::cout << ptr3.use_count() << "\n"; // 3
}
```
*Примечание:* Для подключения умных указателей использовать `#include <memory>`.

#### Задания  
Проследить жизненный цикл экземпляров в различных контейнерах.
1. Дополнительно создать объекты класса `Time` в динамической памяти ( с помощью `new` и `new[]`)(как один экземпляр, так и массив небольшого размера).
2. Создать стандартные контейнеры (`std::vector`, `std::list`, `std::deque` и другие), содержащие объекты типа `Time`.
3. Создать умные указатели (*shared* и *unique*) на объекты класса `Time`.
4. Изучить и объяснить вывод сообщений конструкторов и деструкторов. Обратить внимание на необходимость (всегда ли?) вызова `delete` и/или `delete[]`.


### 6.2. Обработка ошибок
#### Теория
Блок ловли исключений
```
try {
	инструкции, которые могут вызвать исключение
}
catch(объявление_исключения) {
	обработка исключения
}
```
Вводный пример
```
#include <iostream>
double divide(int a, int b) {
	if (b)
		return a / b;
	throw std::string{"Division by zero!"};
}

int main() {
	int x{500};
	int y{};
	try {
		double z {divide(x, y)};
		std::cout << z << std::endl;
	}
	// catch (std::string error_message)
	catch (const std::string& error_message)
	{
		std::cout << error_message << std::endl;
	}
	std::cout << "The End..." << std::endl;
}
// Division by zero!
// The End...
```
Пример обработки нескольких видов исключений
```
#include <iostream>
double divide(int a, int b){
	if(!b) { throw 0; } // если b == 0
	if(b > a) { throw "The second number is greater than the first one"; }
	return a / b;
}

void test(int a, int b) {
	try {
		double result {divide(a, b)};
		std::cout << result << std::endl;
	}
	catch (int code) {  
		std::cout << "Error code: " << code << std::endl;
	}
	catch (const char* error_message) {
		std::cout << error_message << std::endl;
	}
}

int main() {
	test(100, 20); // 5
	test(100, 0); // Error code: 0
	test(100, 1000); // The second number is greater than the first one
}
```
Использование специального объекта для исключения.  
В данном примере - структуры `struct`.
```
#include <iostream>
struct WrongAgeException {
	int age;
	WrongAgeException(int age): age(age){};
};
int ReadAge() {
	int age;
	std::cin >> age;
	if (age < 0 || age >= 128) { throw WrongAgeException(age); }
	return age;
}
int main(){
	try {
		int age = ReadAge(); // может сгенерировать исключение
	} catch (const WrongAgeException& ex) { // ловим объект исключения
		std::cerr << "Age is not correct: " << ex.age << "\n";
		return 1; // выходим из функции main с ненулевым кодом возврата
	}
}
```
Использование стандартного потока ошибок 
```
int ReadAge() {
	std::cin.exceptions(std::istream::failbit);
	int age;
	std::cin >> age;
	return age;
}

int main() {
	try {
		age = ReadAge(); // может сгенерировать исключения разных типов
	} catch (const std::istream::failure& ex) {
		std::cerr << "Failed to read age: " << ex.what() << "\n";
		return 1;
	} catch (...) {
		std::cerr << "Some other exception\n";
		return 1;
	}
}
```
**Уровни Гарантии безопасности исключений**
|   Уровень                         | Инструменты                                                 |
|-----------------------------------|-------------------------------------------------------------|
| 1. Гарантия отсутствия сбоев.     | Только инструменты, обеспечивающие отсутствие исключений.   |
| 2. Строгая гарантия безопасности. | 1 + инструменты для атомарности (копии, транзакции).        |
| 3. Базовая гарантия безопасности. | 1 + 2 + базовые операции с гарантией корректного состояния. |
| 4. Отсутствие гарантий.           | Всё что угодно.                                             |


#### Задания
Научиться обрабатывать свой вид ошибок.
Дополнение класса `Time` генерацией исключений:
1. Определить, какие функции и конструкторы должны генерировать исключения.  
* Например, исключение может создавать стандартный поток вывода `std::cout`.
2. функции не вызывающие исключения отметить ключевым словом `noexcept`.
(Хотя компилятор проставляет ключевые слова сам, где необходимо.)
3. Реализовать генерацию исключений и их обработку в `main()`.
4. Намеренно создать исключение. Проанализировать вывод сообщений конструкторов/деструктора.


### 7.1. Дружественные функции и классы
#### Теория
Ключевое слово `friend` открывает доступ к "приватным" полям класса.   
Вводный пример 
```
#include <iostream>
class Temperature {
private:
	int m_temp { 0 };
public:
	explicit Temperature(int temp) : m_temp { temp } { }
	friend void printWeather(const Temperature& temperature); // объявление friend функции
};

void printWeather(const Temperature& temperature) {
	std::cout << "The temperature is " << temperature.m_temp << std::endl; // использование приватного поля
}
int main() {
	Temperature temp { -2 };
	printWeather(temp);
	return 0;
}
```
Альтернативное объявление
```
class Temperature {
	...
	// friend функция, объясленная внутри класса, не является членом класса
	friend void printWeather(const Temperature& temperature){
		std::cout << "The temperature is " << temperature.m_temp << std::endl;
	}
	...
};
```
Дружественный класс
```
#include <iostream>
class Temperature{
private:
	int m_temp { 0 };
public:
	explicit Temperature(int temp) : m_temp { temp } { }
	int getTemperature() const { return m_temp; }
	friend class WeatherStation; // объявление дружественного класса
};

class WeatherStation{
private:
	int ws_temp {-273};
public:
	WeatherStation(int t): ws_temp(t){}
	void ShowWeather(const Temperature& temp){
		// Прямой доступ к приватному полю m_temp
		std::cout << temp.m_temp << std::endl;
	}
};

int main() {
	Temperature temp {-2} ;
	WeatherStation ws {20};
	ws.ShowWeather(temp);  // Вывод: -2
	return 0;
}
```
Чтобы добавить дружественную функцию, для разделённых заголовочными файлами (`.hpp`) классов, важно:   
1. В класс, где будет *friend* включить `.hpp` друга. Нужна **полная** реализация.
2. Во *friend* класс добавить *forward declaration*. В переводе "Предварительное объявление".
```
// WATCH_HPP
class Time; // forward declaration
class Watch {
	...
	static void showTime(const Time& time);
};
#endif // WATCH_HPP
```
```
// TIME_HPP
#include "Watch.hpp"
class Time {
	...
	friend void Watch::showTime(const Time& time);
};
```

#### Задания
1. Спроектировать и реализовать дружественный к классу `Time` класс `SimpleWatch`, который:
+ может показывать время, содержащееся в `private` переменных объекта класса `Time`.
+ может устанавливать (менять) значение времени в переданном ему объекте класса `Time`,
также через прямой доступ к `private` членам класса `Time`.
2. Реализовать класс `Watch`, который содержит __функции__ члены класса
__дружественные к классу Time__, реализующие просмотр и установку времени
(см. предыдущий пункт) в объекте класса `Time`, который передается им как параметр.
3. Оба класса `Watch` должны реализовывать возможность изменять формат выводимого времени (12/24),
путем установления значения внутренней переменной класса `Watch`.


### 7.2. "Агрегирование и композиция" и "Введение в Наследование"
#### Теория
* Композиция: “Часть” является частью объекта, причем только одного. Объект управляет созданием и разрушением “части”.
* Агрегация: “Часть” является частью объекта, причем не обязательно одного. Объект НЕ управляет созданием и разрушением “части”.  

Основы Наследования
```
class A {
private:
	int x;
public:
	A(){ std::cout << "A\n"; }
};

class B : public A {
private:
	int y;
public:
	B(){ std::cout << "B\n"; }
};
```

#### Задания
##### 1. Иерархия классов
Продумать и реализовать иерархию классов различных часов для возможности создания объектов разных классов.  
Обязательные для реализации классы:
* часы с кукушкой (`cuckoo_clock`),
* настенные часы (`wall_clock`),
* наручные часы (`watch`),
* смарт-часы (`smart_watch`).

Обязательно наличие одного общего родителя для всех классов.
##### 2. Ответы конструкторов/деструкторов
Добавить сообщение о вызове определённых конструкторов/деструкторов
(с указанием имени класса и конструктора)
для каждого класса иерархии `watch`/`clock`.

**Примечание**: Класс Time может быть использован как поле класса.
Все элементы классов, где это необходимо для простоты, могут быть `public`.
##### Цель задания
Демонстрация жизненного цикла объектов, при использовании цепочки наследования.


### 8. Наследование: основы
#### Теория
Конструктор копирования и Деструкторы
```
class Person{
public:
	Person(const Person& person){  // Конструктор копирования
		name = person.name;
		age = person.age;
	}
	Person(std::string name, unsigned age) : name(name), age(age){
		std::cout << "Init contruct Person" << std::endl;
	}
	~Person(){ std::cout << "Destructor Person" << std::endl; }

	void print() const{
		std::cout << "Name: " << name << "\tAge: " << age << std::endl;
	}
private:
	std::string name; // имя
	unsigned age;     // возраст
};

class Student: public Person{
public:
	Student(std::string name, unsigned age, std::string uni):
		Person(name, age), uni(uni) { }

	Student(const Student& student): Person(student){
		uni=student.uni;
	}
	~Student(){ std::cout << "Destructor Student" << std::endl; }

private:
	std::string uni; // университет 
};

int main() {
	Student stud1 {"Mik", 20, "MIT"};
	Student stud2 {stud1};
	stud2.print();
}
// Init contruct Person
// Init constructor Student
// Name: Mik	Age: 20
// Destructor Student
// Destructor Person
```
`final` - запрет наследования.
```
class Retiree final: public Person { ... };
// class Cadaver: public Retiree{};
// Ошибка!
```
Доступ до членов класса:  
* `public` - есть доступ у всех.  
* `private` - нет доступа ни у кого, кроме членов класса.  
* `protected` - есть доступ только у наследников (не доступен не членам класса)

#### Задание
##### 8.1. Эволюция (первый вариант)
Создать <ins>последовательную</ins> иерархию наследования существ:
1. generic creature - общий родитель
2. ocean creature - наследник умеющий плавать
3. amphibious - наследник умеющий плавать и ходить
4. terrestrial creature - не умеет плавать, но умеет ходить
5. bird - умеет ходить и летать
6. waterfowl - водоплавающая птица. Умеет ходить, летать и плавать.

Используя только модификаторы доступа (без виртуальных функций).  
**Примечание**: нужно использовать `using`, `public`, `protected`.


### 9. Наследование: продолжение
#### Теория: "Добавление и сокрытие функционала"
Использование функционала
Из производного класса
```
class Person{
public:
	Person(std::string name, unsigned age): name(name), age(age){}
	void print() const{
		std::cout << "Person Name: " << name << "\tAge: " << age << "\n";
	}
private:
	unsigned age;
	std::string name;
};
class Student: public Person{
public:
	Student(std::string name, unsigned age, std::string uni): Person(name, age), uni(uni){}
	void print() const{
		std::cout << "Student attends " << uni << std::endl;
	}
private:
	std::string uni;
};


int main() {
Person pers {"Tom", 30};
	pers.print();
	// Person Name: Tom Age: 30
	Student student {"Mik", 20, "MIT"};
	student.print();
	// Student attends MIT
}
```

Добавление функционала
```
class Student: public Person{
public:
	void print() const{
		Person::print(); // print(); // Нельзя просто print()!!!
		std::cout << "Student attends " << uni << std::endl;
	}
};
```

#### Теория: "Множественное наследование"
##### Пример 1
Определяем основу примера
```
#include <iostream>
class Person{
public:
	Person(std::string name, unsigned age): name(name), age(age){
		std::cout << "Init contruct Person" << std::endl;
	}
	~Person(){ std::cout << "Destructor Person" << std::endl;}
	void print() const{
		std::cout << "Person Name: " << name << " Age: " << age << "\n";
	}
private:
	unsigned age;
	std::string name;
};
class Student: public Person{
public:
	Student(std::string name, unsigned age, std::string uni): Person(name, age), uni(uni){
		std::cout << "Init constructor Student" << std::endl;
	}
	~Student(){ std::cout << "Destructor Student" << std::endl; }
	void print() const{
		std::cout << "Student attends " << uni << std::endl;
	}
private:
	std::string uni;
};

class Worker {
public:
	Worker(std::string company): company(company){
		std::cout << "Init constructor Worker" << std::endl;
	}
	~Worker(){ std::cout << "Destructor Worker" << std::endl; }
	void print() const{
		std::cout << "Works in " << company << std::endl;
	}
private:
	std::string company;
};
```
Производный класс
```
class StudentWorker: public Student, public Worker{
public:
	StudentWorker(std::string name, unsigned age, std::string uni, std::string company) : Student(name, age, uni), Worker(company) {
		std::cout << "Init constructor StudentWorker" << std::endl;
	}
	~StudentWorker(){ std::cout << "Destructor StudentWorker" << std::endl; }
	void print() const{
		std::cout << "StudentWorker: " << std::endl;
		Person::print();
		Student::print();
		Worker::print();
	}
};
```
Точка входа
```
int main() {
	Person pers {"Tom", 30};
	pers.print(); // (1)
	Student student {"Mik", 20, "MIT"};
	student.print(); // (2)
	Worker worker {"Company"};
	worker.print(); // (3)
	StudentWorker student_worker {"Vasya", 23, "NSU", "The galley"};
	student_worker.print(); // (4)
}
/*
(1) Person Name: Tom Age: 30
(2) Student attends MIT
(3) Works in Company
(4) StudentWorker:
   Person Name: Vasya Age: 23
   Student attends NSU
   Works in The galley
*/
```

#### Задания
##### 9.1. Эволюция (второй вариант)
1. Создать <ins>последовательную</ins> иерархию наследования существ:
   1. generic creature - общий родитель
   2. ocean creature - наследник умеющий плавать
   3. amphibious - наследник умеющий плавать и ходить
   4. terrestrial creature - не умеет плавать, но умеет ходить
   5. bird - умеет ходить и летать
   6. waterfowl - водоплавающая птица. Умеет ходить, летать и плавать.
2. Использовать только добавление и сокрытие функционала (без изменения модификаторов доступа наследования).
3. Не использовать множественное наследование.
4. Не переопределять функции.
5. Одним `.cpp` файлом.  

**Примечание**: Нужно использовать:
   * `delete` для стирания
   * `using` для добавления
   возможностей предыдущих классов.

##### 9.2. Эволюция (третий вариант)
1. Создать иерархию наследования существ:
   1. generic creature - общий родитель
   2. ocean creature - наследник умеющий плавать
   3. amphibious - наследник умеющий плавать и ходить
   4. terrestrial creature - не умеет плавать, но умеет ходить
   5. bird - умеет ходить и летать
   6. waterfowl - водоплавающая птица. Умеет ходить, летать и плавать.
2. <ins>Обязательно использовать множественное наследование.</ins>
3. Не переопределять функции.

### 10. Полиморфизм
#### Теория: Виртуальные функции
* Функции объявленные virtual являются virtual и в потомках (но не наоборот).
* Сигнатура функции в потомках должна полностью совпадать
* override используется для явного указания на
переопределение (в случае отсутствия в базовом
классе функции с идентичной сигнатурой,
компилятор будет генерировать ошибку).
* Никогда не вызывайте виртуальные функции в
конструкторах и деструкторах (важен порядок
создания/удаления).  

Использование:  
* vitrual - в базовом классе;
* override - в наследниках.

#### Задание
##### 10.1. Эволюция (полиморфизм)
1. Создать иерархию наследования существ:
   1. generic creature - общий родитель
   2. ocean creature - наследник умеющий плавать
   3. amphibious - наследник умеющий плавать и ходить
   4. terrestrial creature - не умеет плавать, но умеет ходить
   5. bird - умеет ходить и летать
   6. waterfowl - водоплавающая птица. Умеет ходить, летать и плавать.
2. Обязательно использовать <ins>абстрактный класс</ins> с чистой виртуальной функцией `void eat()`.
3. Переопределить (virtual) функцию поглощения пищи `eat()` в каждом классе (уникальное поведение).
4. Создать массив `generic_creature` и массив указателей на `generic_creature` такие, чтобы объект каждого класса встречался не менее одного раза.
5. Проиллюстрировать полиморфное (а также не полиморфное) поведение (показать существенные отличия, необходимые для реализации полиморфного поведения).

