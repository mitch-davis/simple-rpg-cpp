#pragma once
#include "Hero.h"
class Cleric: public Hero
{
public:
	Cleric();
	~Cleric();
	std::string Cleric::useSkill(Entity*);
	std::string Cleric::getSkill();
	std::string fireBreath(std::vector<Entity*>);
};

