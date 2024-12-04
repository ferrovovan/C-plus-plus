#ifndef TERRESTRIAL_CREATURE_HPP
#define TERRESTRIAL_CREATURE_HPP

#include "generic_creature.hpp"

class TerrestrialCreature : public GenericCreature {
protected:
	TerrestrialCreature() = default;

public:
	void walk() const; // Умение ходить
};

#endif // TERRESTRIAL_CREATURE_HPP
