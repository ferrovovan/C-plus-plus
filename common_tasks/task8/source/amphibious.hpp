#ifndef AMPHIBIOUS_HPP
#define AMPHIBIOUS_HPP

#include "ocean_creature.hpp"

class Amphibious : public OceanCreature {
public:
	Amphibious() = default;
	using OceanCreature::swim; // Унаследованное умение плавать
	void walk() const;         // Умение ходить
};

#endif // AMPHIBIOUS_HPP
