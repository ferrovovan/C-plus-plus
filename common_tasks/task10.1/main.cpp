#include <iostream>
#include <vector>


void print_green(const std::string& message) {
	std::cout << "\033[0;32m" << message << "\033[0m\n";
}

class GenericCreature {
public:
	/* task 2 */
	// virtual void eat() = 0;
	virtual void eat() { std::cout << "Simple eating...\n"; }
};

class OceanCreature : public virtual GenericCreature {
public:
	void swim() { std::cout << "Swimming...\n"; }
	void eat() override { std::cout << "OceanCreature Eating!\n"; }
};

class TerrestrialCreature : public virtual GenericCreature{
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
	print_green("OceanCreature the fish messages:");
	OceanCreature fish;
	fish.swim();
	fish.eat();

	print_green("Amphibious the frog messages:");
	Amphibious frog;
	frog.swim();
	frog.walk();
	frog.eat();

	print_green("TerrestrialCreature the cat messages:");
	TerrestrialCreature cat;
	cat.walk();
	cat.eat();

	print_green("Bird the owl messages:");
	Bird owl;
	owl.walk();
	owl.fly();
	owl.eat();

	print_green("Waterfowl the duck messages:");
	Waterfowl duck;
	duck.walk();
	duck.fly();
	duck.swim();
	duck.eat();
}

void task_4() {
	print_green("\nTask 4\n");
	/* array elements */
	GenericCreature creatures_array[] = {
		OceanCreature(),
		TerrestrialCreature(),
		Amphibious(),
		Amphibious(), // второй раз
		Bird(),
		Waterfowl()
	};
	for (int i = 0; i < 6; ++i) {
		creatures_array[i].eat();
	}
	
	/* pointers */
	GenericCreature* creatures_pointers[] = {
		new OceanCreature,
		new TerrestrialCreature,
		new Amphibious,
		new Amphibious, // второй раз
		new Bird,
		new Waterfowl
	};
	int size = 6;
	
	// do work
	for (int i = 0; i < size; ++i) {
		creatures_pointers[i]->eat();
	}
	// clear_pointers
	for (int i = 0; i < size; ++i) {
		delete creatures_pointers[i];
	}
}

void task_5() {
	print_green("\nTask 5\n");
	std::vector<GenericCreature*> creatures;
	creatures.push_back(new OceanCreature);
	creatures.push_back(new TerrestrialCreature);
	creatures.push_back(new Amphibious);
	creatures.push_back(new Bird);
	creatures.push_back(new Waterfowl);

	for (GenericCreature* creature : creatures) {
		creature->eat();
	}

	for (GenericCreature* creature : creatures) {
		delete creature;
	}

	OceanCreature ocean1;
	TerrestrialCreature terr1;
	GenericCreature* gen_ptr;
	gen_ptr = &ocean1;
	gen_ptr->eat();
}


int main() {
	task_3();
	task_4();
	task_5();
	return 0;
}

