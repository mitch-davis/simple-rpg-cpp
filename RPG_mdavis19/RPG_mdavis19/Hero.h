#pragma once
#include <string>
#include "Entity.h"

class Hero: public Entity
{
public:
	Hero();
	~Hero();

	std::string Hero::useSkill(Entity*);
	std::string fireBreath(std::vector<Entity*>);

protected:

};
