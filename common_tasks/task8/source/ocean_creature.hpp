#ifndef OCEAN_CREATURE_HPP
#define OCEAN_CREATURE_HPP

#include "generic_creature.hpp"

class OceanCreature : public GenericCreature {
protected:
	OceanCreature() = default;

public:
	void swim() const; // Умение плавать
};

#endif // OCEAN_CREATURE_HPP
