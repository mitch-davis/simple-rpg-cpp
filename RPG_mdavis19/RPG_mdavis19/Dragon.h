#pragma once
#include "Enemy.h"

class Dragon: public Enemy
{
public:
	Dragon();
	~Dragon();
	std::string Dragon::useSkill(Entity*);
	std::string Dragon::getSkill();
	std::string fireBreath(std::vector<Entity*>);
};

