#include "stdafx.h"
#include "Hero.h"
#include "Entity.h"

//Hero general class for Dungeon++ game; written by Mitch Davis

Hero::Hero()
{
	hitPoints = 1000;
	skillPoints = 100;
	name = "Hero";
}


Hero::~Hero()
{
}

std::string Hero::useSkill(Entity*) {

	std::string result;
	result = "\n" + name + " used " + getSkill() + ".\n";
	return result;
}

std::string Hero::fireBreath(std::vector<Entity*>) {
	return "This class may not use fire breath";
}


