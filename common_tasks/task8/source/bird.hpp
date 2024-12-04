#ifndef BIRD_HPP
#define BIRD_HPP

#include "terrestrial_creature.hpp"

class Bird : public TerrestrialCreature {
public:
	Bird() = default;
	void fly() const;  // Умение летать
	using TerrestrialCreature::walk; // Унаследованное умение ходить
};

#endif // BIRD_HPP
