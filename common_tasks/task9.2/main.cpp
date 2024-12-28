#include <iostream>
#include <string>

void print_green(const std::string& message) {
	std::cout << "\033[0;32m" << message << "\033[0m\n";
}

// Базовый класс
class GenericCreature {
protected:
	std::string name;
public:
	GenericCreature(const std::string& name) : name(name) {}
	virtual void sound() const = 0;
	virtual ~GenericCreature() = default;
};

// Виртуальное наследование
class OceanCreature : virtual public GenericCreature {
public:
	OceanCreature(const std::string& name) : GenericCreature(name) {}
	void swim() const { std::cout << name << " is swimming...\n"; }
	void sound() const override { std::cout << name << " makes water sounds!\n"; }
};

class TerrestrialCreature : virtual public GenericCreature {
public:
	TerrestrialCreature(const std::string& name) : GenericCreature(name) {}
	void walk() const { std::cout << name << " is walking...\n"; }
	void sound() const override { std::cout << name << " makes terrestrial sounds!\n"; }
};

// Классы с комбинированным поведением
class Amphibious : public OceanCreature, public TerrestrialCreature {
public:
	Amphibious(const std::string& name)
		: GenericCreature(name), OceanCreature(name), TerrestrialCreature(name) {}

	void sound() const override {
		std::cout << name << " has both water and terrestrial sounds!\n";
	}
};

class Bird : public TerrestrialCreature {
public:
	Bird(const std::string& name) : GenericCreature(name), TerrestrialCreature(name) {}
	void fly() const { std::cout << name << " is flying...\n"; }
	void sound() const override { std::cout << name << " chirps!\n"; }
};

class Waterfowl : public Bird, public OceanCreature {
public:
	Waterfowl(const std::string& name)
		: GenericCreature(name), Bird(name), OceanCreature(name) {}

	void sound() const override {
		std::cout << name << " combines chirping and water sounds!\n";
	}
};

int main() {
	print_green("OceanCreature fish message");
	OceanCreature fish("Fish");
	fish.swim();
	fish.sound();

	print_green("Amphibious frog messages");
	Amphibious frog("Frog");
	frog.swim();
	frog.walk();
	frog.sound();

	print_green("TerrestrialCreature cat message");
	TerrestrialCreature cat("Cat");
	cat.walk();
	cat.sound();

	print_green("Bird Owl messages");
	Bird owl("Owl");
	owl.walk();
	owl.fly();
	owl.sound();

	print_green("Waterfowl duck messages");
	Waterfowl duck("Duck");
	duck.walk();
	duck.fly();
	duck.swim();
	duck.sound();

	return 0;
}

