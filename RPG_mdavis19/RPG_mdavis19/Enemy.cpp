#include "stdafx.h"
#include "Enemy.h"
#include "Entity.h"

//Enemy class for Dungeon++ game; written by Mitch Davis

Enemy::Enemy()
{
	name = "Dragon";
	hitPoints = 2500;
}


Enemy::~Enemy()
{
}

std::string Enemy::useSkill(Entity*) {

	std::string result;
	result = "\n" + name + " used " + getSkill() + ".\n";
	return result;
}

std::string Enemy::fireBreath(std::vector<Entity*>) {
	return "This class may not use fire breath";
}


