#ifndef GENERIC_CREATURE_HPP
#define GENERIC_CREATURE_HPP

class GenericCreature {
protected:
	GenericCreature() = default;

public:
	void exist() const; // Общее поведение для всех существ
};

#endif // GENERIC_CREATURE_HPP
