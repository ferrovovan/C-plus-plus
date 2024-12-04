#ifndef WATERFOWL_HPP
#define WATERFOWL_HPP

#include "bird.hpp"
#include "ocean_creature.hpp"

class Waterfowl final : public Bird, public OceanCreature {
public:
	Waterfowl() = default;

	using Bird::walk;   // Умение ходить
	using Bird::fly;    // Умение летать
	using OceanCreature::swim; // Умение плавать
};

#endif // WATERFOWL_HPP
