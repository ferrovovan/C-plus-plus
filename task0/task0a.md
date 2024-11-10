# Задача 0a - Раздельная компиляция и пространства имен (namespaces)
## Формулировка задания
Рассмотрим программу:
**File module1.h:**
```
#include <string>

namespace Module1{	std::string getMyName();}
```
**File module1.cpp:**
```
#include "module1.h"

namespace Module1 {
    std::string getMyName()	{
		std::string name = "John";
		return name;
	}
}
```
**File module2.h:**
```
#include <string>

namespace Module2{	std::string getMyName();}
```
**File module2.cpp:**
```
#include "module2.h"

namespace Module2 {
	std::string getMyName() {
		std::string name = "James";
		return name;
	}
}
```
**File main.cpp:**
```
#include "module1.h"
#include "module2.h"
#include <iostream>

int main(int argc, char** argv)
{
	std::cout <<  "Hello world!" << "\n";
	
	std::cout << Module1::getMyName() << "\n";
	std::cout << Module2::getMyName() << "\n";

	using namespace Module1;
	std::cout << getMyName() << "\n"; // (A)
	std::cout << Module2::getMyName() << "\n";

	//using namespace Module2; // (B)
	//std::cout << getMyName() << "\n"; // COMPILATION ERROR (C)

	using Module2::getMyName;
	std::cout << getMyName() << "\n"; // (D)

}
```
**Вопросы:**
  1. Объяснить, что выведется при выполнении строк с комментариями (А) и (D) в `main.cpp`
  2. Убедиться, что раскомментирование строк (B) и (C) в `main.cpp` приводит к ошибке компиляции.  
  Объяснить, почему эта ошибка происходит, и предложить пути её устранения.
  3. Объяснить, как можно избавиться от необходимости писать std::cout и вместо этого писать просто cout.

## Ответы на вопросы
### 1. Объяснение вывода при выполнении строк (A) и (D):  
  - В строке `(A)` используется `using namespace Module1`, что приводит к тому, что все имена из пространства имен `Module1` становятся доступными напрямую, без необходимости указания пространства имен. Таким образом, вызов `getMyName()` в строке `(A)` соответствует функции `Module1::getMyName()`, и она выводит: `John`.
  - В строке `(D)` используется `using Module2::getMyName`, что приводит к тому, что конкретно эта функция из пространства `Module2` становится доступной напрямую. Таким образом, вызов `getMyName()` соответствует функции `Module2::getMyName()`, которая выводит: `James`.
### 2. Почему строки (B) и (C) приводят к ошибке компиляции?
  - При раскомментировании строки `(B)` — `using namespace Module2;` — происходит конфликт имен. Это связано с тем, что в пространстве имен `Module1` и `Module2` находятся функции с одинаковым именем `getMyName()`.  
  Когда оба пространства имен используются одновременно, компилятор не может однозначно определить, какую именно функцию `getMyName()` вызывать, что и приводит к ошибке компиляции. Ошибка заключается в неоднозначности вызова.
  - Чтобы устранить ошибку, можно обернуть блок, с включением сторонней области видимости (`using namespace Module1;`), во внутреннюю область видимости:
```
{
    using namespace Module1;
    std::cout << getMyName() << "\n"; // (A)
}
std::cout << Module2::getMyName() << "\n";
```

### 3. Как избавиться от необходимости писать `std::cout` и вместо этого использовать просто `cout`?
  - Чтобы не писать `std::cout` каждый раз, можно добавить строку:
```cpp
using std::cout;
```
Это приведет к тому, что имя `cout` из пространства имен `std` будет доступно напрямую, и можно будет писать просто `cout` без необходимости указывать `std::`.

