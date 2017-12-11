#include "stdafx.h"
#include "Warrior.h"

//Warrior hero class for Dungeon++ game; written by Mitch Davis

Warrior::Warrior()
{
	name = "Warrior";

	attack = 60; //average attack
	defense = 80; //high defense
	speed = 50; //avg. speed
	strength = 80; //high strength
	intelligence = 40; //below avg. intelligence

	hitPoints = 1000;
	skillPoints = 100;
	isNPC = false;
	isDefending = false;
	isBleeding = false;
	isInspired = false;
}


Warrior::~Warrior()
{
}

//Warrior's unique skill is to break defense and deal constant damage
std::string Warrior::useSkill(Entity* target) {
	isDefending = false;
	skillPoints -= 10;
	std::string result;

	if (isInspired) {
		target->breakDefense();
		target->setHitPoints(target->getHitPoints() - 225);
		result = "\n" + name + " used " + getSkill() + ". " + target->getName() + "'s defense was broken and took 225 damage.\n";
	}
	else {
		target->breakDefense();
		target->setHitPoints(target->getHitPoints() - 150);
		result = "\n" + name + " used " + getSkill() + ". " + target->getName() + "'s defense was broken and took 150 damage.\n";
	}
	
	return result;
}

std::string Warrior::getSkill() {
	return "shield charge";
}

std::string Warrior::fireBreath(std::vector<Entity*>) {
	return "This class may not use fire breath";
}