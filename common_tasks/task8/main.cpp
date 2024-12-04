#include "waterfowl.hpp"
#include "amphibious.hpp"
#include "terrestrial_creature.hpp"
#include "ocean_creature.hpp"
#include "bird.hpp"

#include <iostream>

void print_green(const std::string& message) {
	std::cout << "\033[0;32m" << message << "\033[0m\n";
}


void GenericCreature::exist() const {
	std::cout << "I'm a generic creature. I exist." << std::endl;
}

void OceanCreature::swim() const {
	std::cout << "I'm swimming!" << std::endl;
}

void Amphibious::walk() const {
	std::cout << "I'm walking on land!" << std::endl;
}

void TerrestrialCreature::walk() const {
	std::cout << "I can only walk on land." << std::endl;
}

void Bird::fly() const {
	std::cout << "I'm flying!" << std::endl;
}

int main() {
	print_green("Waterfowl duck messages");
	Waterfowl duck;
	duck.swim();
	duck.fly();
	duck.walk();

	print_green("Amphibious frog messages");
	Amphibious frog;
	frog.walk();
	frog.swim();

	print_green("Bird Owl messages");
	Bird Owl;
	Owl.walk();
	Owl.fly();

	return 0;
}

