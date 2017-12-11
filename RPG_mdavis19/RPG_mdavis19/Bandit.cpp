#include "stdafx.h"
#include "Bandit.h"

//Bandit enemy class for Dungeon++ game; written by Mitch Davis

Bandit::Bandit()
{
	name = "Bandit";

	speed = 60; //above avg. speed
	strength = 60; //avg speed
	intelligence = 20; //low intelligence
	attack = 30; //low attack
	defense = 20; //low defense

	hitPoints = 200; //low HP
	skillPoints = 100;
	isNPC = true;
	isDefending = false;
	isInspired = false;
}


Bandit::~Bandit()
{
}

//Bandit's unique skill is to attack its target twice
std::string Bandit::useSkill(Entity* target) {
	isDefending = false;
	skillPoints -= 10;
	std::string result;

    result = "\n" + name + " used " + getSkill() + " on " + target->getName() + ".\n" + name + " gets to attack " + target->getName() + " twice.\n\n1st attack: ";
	result += attackF(target); //1st attack
	result += "\n2nd attack: ";
	result += attackF(target); //2nd attack
	result += "\n";
	 
	return result;
}

std::string Bandit::getSkill() {
	return "berserk";
}

std::string Bandit::fireBreath(std::vector<Entity*>) {
	return "This class may not use fire breath";
}