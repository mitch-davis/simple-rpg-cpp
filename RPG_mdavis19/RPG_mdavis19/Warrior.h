#pragma once
#include "Hero.h"
#include <iostream>
class Warrior: public Hero
{
public:
	Warrior();
	~Warrior();

	std::string useSkill(Entity*);
	std::string Warrior::getSkill();
	std::string fireBreath(std::vector<Entity*>);
};

