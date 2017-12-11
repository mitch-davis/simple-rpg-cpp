#pragma once
#include "Enemy.h"

class Orc: public Enemy
{
public:
	Orc();
	~Orc();
	std::string Orc::useSkill(std::vector<Entity*> enemies);
	std::string Orc::getSkill();
	std::string fireBreath(std::vector<Entity*>);
};

