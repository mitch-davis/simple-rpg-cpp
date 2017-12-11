#include "stdafx.h"
#include "Mage.h"

//Mage hero class for Dungeon++ game; written by Mitch Davis

Mage::Mage()
{
	name = "Mage";

	speed = 80; //very fast
	strength = 40; //below avg. strength
	intelligence = 80; //high intelligence
	attack = 80;  //high attack
	defense = 20; //low defense

	hitPoints = 1000;
	skillPoints = 100;
	isNPC = false;
	isDefending = false;
	isBleeding = false;
	isInspired = false;
}


Mage::~Mage()
{
}

//Mage's unique skill is magic blast: deals double attack damage (can combo with advantage)
std::string Mage::useSkill(Entity* target) {


	isDefending = false;
	skillPoints -= 10;

	//seed RNG
	clock_t seed;
	seed = clock();
	srand(seed);

	int damage = 0;
	std::string result = "";

	//string stream to convert damage integer to string
	std::string damageToString;
	std::stringstream sStream;

	//enemies can block this unique skill
	if (target->isDefending_F()) {
		result = "\n" + target->getName() + " blocked " + name + "'s energy blast.\n";
		return result;
	}

	if (isInspired) {
		damage = 3*attack*((rand() % 5) + 1); //damage dealt will be a random value [1,5] multiplied by 1.5* double the attacker's attack value
	}
	else {
		damage = 2*attack*((rand() % 5) + 1); //damage dealt will be a random value [1,5] multiplied by the double attacker's attack value
	}

	if (target->isInspired_F()) {
		damage -= (1.5*target->getDefense()); //reduce incoming damage by 1.5* the target's defense rating
	}
	else {
		damage -= target->getDefense(); //reduce incoming damage by the target's defense rating
	}

	if (damage < 0) { //make sure attacks wont give back health
		damage = 0;
	}
	if (damage == 0) {
		result = "\n" + name + " missed " + target->getName() + ".\n";
		return result;
	}
	if (damage > 0) {

		damage += intelligence; //add intelligence and strength as constant bonus to damage
		damage += strength;

		target->setHitPoints(target->getHitPoints() - damage); //reduce the target's hitpoints by the final calculated damage
		sStream << damage;
		result = "\n" + name + " energy blasted " + target->getName() + " for " + sStream.str() + " damage.\n";
		return result;
	}

	return "error.";
}

std::string Mage::getSkill() {
	return "energy blast";
}

std::string Mage::fireBreath(std::vector<Entity*>) {
	return "This class may not use fire breath";
}