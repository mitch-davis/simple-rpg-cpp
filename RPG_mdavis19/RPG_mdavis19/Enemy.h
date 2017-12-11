#pragma once
#include <string>
#include "Entity.h"
class Enemy: public Entity
{
public:
	Enemy();
	~Enemy();
	std::string Enemy::useSkill(Entity*);
	std::string fireBreath(std::vector<Entity*>);
private:
};
