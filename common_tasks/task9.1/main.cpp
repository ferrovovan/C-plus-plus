#include <iostream>


void print_green(const std::string& message) {
	std::cout << "\033[0;32m" << message << "\033[0m\n";
}

class GenericCreature {
public:
	GenericCreature() {}
};

class OceanCreature : public GenericCreature {
public:
	void swim() { std::cout << "Swimming...\n"; }
};

class Amphibious : public OceanCreature {
public:
	void walk() { std::cout << "Walking...\n"; }
};

class TerrestrialCreature : public Amphibious {
public:
	void swim() = delete;
};

class Bird : public TerrestrialCreature {
public:
	void fly() { std::cout << "Flying...\n"; }
};

class Waterfowl : public Bird {
public:
	using OceanCreature::swim;
};

int main() {
	print_green("OceanCreature fish message");
	OceanCreature fish;
	fish.swim();

	print_green("Amphibious frog messages");
	Amphibious frog;
	frog.swim();
	frog.walk();

	print_green("TerrestrialCreature cat message");
	TerrestrialCreature cat;
	cat.walk();

	print_green("Bird Owl messages");
	Bird bird;
	bird.walk();
	bird.fly();

	print_green("Waterfowl duck messages");
	Waterfowl duck;
	duck.walk();
	duck.fly();
	duck.swim();

	return 0;
}

