#include "stdafx.h"
#include "Cleric.h"

//Cleric hero class for Dungeon++ game; written by Mitch Davis

Cleric::Cleric()
{
	name = "Cleric";

	speed = 65; //above avg. speed
	strength = 20; //low strength
	intelligence = 60; //avg. intelligence 
	attack = 20; //low attack
	defense = 60; //average defense

	hitPoints = 1000;
	skillPoints = 100;
	isNPC = false;
	isDefending = false;
	isBleeding = false;
	isInspired = false;
}


Cleric::~Cleric()
{
}

//Cleric unique skill is to heal a fellow hero (including itself)
std::string Cleric::useSkill(Entity* target) {
	
	//seed the RNG
	clock_t seed;
	seed = clock();
	srand(seed);
	
	isDefending = false;
	skillPoints -= 10;
	std::string result;
	int healAmount = 0;

	//string stream to concatenate result string with the amount healed
	std::string healAmountToString;
	std::stringstream sStream;

	healAmount = (intelligence + strength)*((rand() % 5) + 1); //healing amount will be a random value [1,5] multiplied by the sum of cleric's intelligence and strength

	target->setHitPoints(target->getHitPoints() + healAmount); //increase the target's hitpoints by the final calculated healing amount
	sStream << healAmount; //inject the string stream with the healing amount integer
	result = "\n" + name + " used heal on " + target->getName() + ". Healed " + sStream.str() + " points.\n";
	return result;                                                             //convert to string
}

std::string Cleric::getSkill() {
	return "heal hero";
}

std::string Cleric::fireBreath(std::vector<Entity*>) {
	return "This class may not use fire breath";
}
