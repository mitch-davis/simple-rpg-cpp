#include "stdafx.h"
#include "Dragon.h"
#include <iostream>

//Dragon enemy class for Dungeon++ game; written by Mitch Davis

Dragon::Dragon()
{
	name = "Dragon";

	speed = 10; //extremely slow
	strength = 80; //high strength
	intelligence = 80; //high intelligence
	attack = 90; //very high attack
	defense = 90; //very high defense

	hitPoints = 1000;
	skillPoints = 100;
	isNPC = true;
	isDefending = false;
	isInspired = false;
}

Dragon::~Dragon()
{
}

//Dragon's unique skill is claw swipe; does constant damage and causes target to start taking bleed damage
std::string Dragon::useSkill(Entity* target) {
	isDefending = false;
	skillPoints -= 10;
	std::string result;

	//does 150 damage when "buffed" by battle cry
	if (isInspired) {
		target->setHitPoints(target->getHitPoints() - 150); //reduce target's hp by 150
		target->startBleeding(); //target starts to bleed (does damage on each turn)

		result = "\n" + name + " used " + getSkill() + " on " + target->getName() + ". " + target->getName() + " took 150 damage and has started to take bleed damage.\n";
		return result;
	}
	//does 100 damage normally
	else {
		target->setHitPoints(target->getHitPoints() - 100);
		target->startBleeding();

		result = "\n" + name + " used " + getSkill() + " on " + target->getName() + ". " + target->getName() + " took 100 damage and has started to take bleed damage.\n";
		return result;
	}
}

//Dragon gets a bonus skill: fire breath. damages each hero in the fight
std::string Dragon::fireBreath(std::vector<Entity*> heroes) {

	skillPoints -= 20; //costs double skill points to use
	std::string result;

	//1.5 damage when "buffed" by battle cry
	if (isInspired) {
		result = "Dragon breathed fire on: \n";

		//damage all heroes on the board for 300 points
		for (unsigned int i = 0; i < heroes.size(); i++) {
			heroes[i]->setHitPoints(heroes[i]->getHitPoints() - 300);
			result += heroes[i]->getName() + "\n"; //add affected heroes names to the result string
		}

		result += ", dealing 300 damage to each.\n";
		return result;
	}
	else {
		result = "Dragon breathed fire on: \n";

		//damage all heroes on the board for 200 points (20% of max hp)
		for (unsigned int i = 0; i < heroes.size(); i++) {
			heroes[i]->setHitPoints(heroes[i]->getHitPoints() - 200);
			result += heroes[i]->getName() + "\n";
		}

		result += ", dealing 200 damage to each.\n";
		return result;
	}

}

std::string Dragon::getSkill() {
	return "claw swipe";
}

