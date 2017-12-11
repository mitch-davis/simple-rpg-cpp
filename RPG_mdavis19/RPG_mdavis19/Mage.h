#pragma once
#include "Hero.h"
class Mage: public Hero
{
public:
	Mage();
	~Mage();

	std::string useSkill(Entity*);
	std::string Mage::getSkill();
	std::string fireBreath(std::vector<Entity*>);
};

