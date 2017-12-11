#pragma once
#include "Enemy.h"
class Bandit: public Enemy
{
public:
	Bandit();
	~Bandit();
	std::string Bandit::useSkill(Entity*);
	std::string Bandit::getSkill();
	std::string fireBreath(std::vector<Entity*>); 
};

