#include <iostream>
#include <vector>

void print_green(const std::string& message) {
	std::cout << "\033[0;32m" << message << "\033[0m\n";
}

/*
1. Для полиморфного поведения необходимо использовать указатель или ссылку на базовый класс.
2. В базовом классе должны быть определены виртуальные функции, которые могут быть переопределены в производных классах.
3. Производные классы должны переопределить виртуальные функции базового класса.
4. Использование виртуального наследования для правильной работы с базовым классом в сложных иерархиях наследования.
*/

class GenericCreature {
public:
	GenericCreature() {}
	virtual void eat() { std::cout << "Simple eating...\n"; }
	virtual ~GenericCreature() = default;
};

class OceanCreature : public virtual GenericCreature {
public:
	void swim() { std::cout << "Swimming...\n"; }
	void eat() override { std::cout << "OceanCreature Eating!\n"; }
};

class TerrestrialCreature : public virtual GenericCreature {
public:
	void walk() { std::cout << "Walking...\n"; }
	void eat() override { std::cout << "TerrestrialCreature Eating!\n"; }
};

class Amphibious : public OceanCreature, public virtual TerrestrialCreature {
public:
	void eat() override { std::cout << "Amphibious Eating!\n"; }
};

class Bird : public TerrestrialCreature {
public:
	void fly() { std::cout << "Flying...\n"; }
	void eat() override { std::cout << "Bird Eating!\n"; }
};

class Waterfowl : public Bird, public OceanCreature {
public:
	void eat() override { std::cout << "Waterfowl Eating!\n"; }
};

void task_3() {
	print_green("\nTask 3\n");
	print_green("OceanCreature fish messages:");
	OceanCreature fish;
	fish.swim();
	fish.eat();

	print_green("Amphibious frog messages:");
	Amphibious frog;
	frog.swim();
	frog.walk();
	frog.eat();

	print_green("TerrestrialCreature cat messages:");
	TerrestrialCreature cat;
	cat.walk();
	cat.eat();

	print_green("Bird owl messages:");
	Bird owl;
	owl.walk();
	owl.fly();
	owl.eat();

	print_green("Waterfowl duck messages:");
	Waterfowl duck;
	duck.walk();
	duck.fly();
	duck.swim();
	duck.eat();
}

void task_4() {
	print_green("\nTask 4\n");

	// 1. При использовании массива объектов полиморфное поведение отсутствует.
	GenericCreature creatures_array[] = {
		OceanCreature(),
		TerrestrialCreature(),
		Amphibious(),
		Bird(),
		Waterfowl()
	};
	for (int i = 0; i < 5; ++i) {
		creatures_array[i].eat();
	}

	// 2. Использование указателей позволяет добиться полиморфного поведения.
	GenericCreature* creatures_pointers[] = {
		new OceanCreature,
		new TerrestrialCreature,
		new Amphibious,
		new Bird,
		new Waterfowl
	};
	for (int i = 0; i < 5; ++i) {
		creatures_pointers[i]->eat(); // Вызов соответствующей версии функции eat().
	}
	for (int i = 0; i < 5; ++i) {
		delete creatures_pointers[i];
	}
}

void task_5() {
	print_green("\nTask 5\n");
	std::vector<GenericCreature*> creatures = {
		new OceanCreature,
		new TerrestrialCreature,
		new Amphibious,
		new Bird,
		new Waterfowl
	};
	for (GenericCreature* creature : creatures) {
		creature->eat(); // Полиморфный вызов.
	}
	for (GenericCreature* creature : creatures) {
		delete creature;
	}

	// Полиморфное поведение при использовании указателя на базовый класс.
	GenericCreature* gen_ptr;
	OceanCreature ocean1;
	TerrestrialCreature terr1;

	gen_ptr = &ocean1;
	gen_ptr->eat(); // Вызов OceanCreature::eat()

	gen_ptr = &terr1;
	gen_ptr->eat(); // Вызов TerrestrialCreature::eat()
}

int main() {
	task_3();
	task_4();
	task_5();
	return 0;
}

