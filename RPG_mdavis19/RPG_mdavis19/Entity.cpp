#include "stdafx.h"
#include "Entity.h"
#include <stdio.h> 
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sstream>

//Entity base class for all heroes and enemies for Dungeon++ game; written by Mitch Davis

Entity::Entity()
{
	hitPoints = 1000;
	skillPoints = 100;
	name = "Entity";
}


Entity::~Entity()
{
}

std::string Entity::getName()
{
	return name;
}

int Entity::getHitPoints()
{
	return hitPoints;
}



int Entity::getSkillPoints()
{
	return skillPoints;
}

int Entity::getDefense() {
	return defense;
}

int Entity::getSpeed() {
	return speed;
}

bool Entity::isNPC_F() {
	return isNPC;
}

bool Entity::isDefending_F() {
	return isDefending;
}

bool Entity::isBleeding_F() {
	return isBleeding;
}

bool Entity::isInspired_F() {
	return isInspired;
}

void Entity::breakDefense() {
	isDefending = false;
}

void Entity::setHitPoints(int newHP) {
	//max hp is 1000
	if (newHP > 1000) {
		hitPoints = 1000;
	}
	else {
		hitPoints = newHP;
	}
}

void Entity::setSkillPoints(int newSP) {
	//max sp is 100
	if (newSP > 100) {
		skillPoints = 100;
	}
	else {
		skillPoints = newSP;
	}
}

void Entity::startBleeding() {
	isBleeding = true;
}

void Entity::stopBleeding() {
	isBleeding = false;
}

void Entity::becomeInspired() {
	isInspired = true;
}

void Entity::inspirationFade() {
	isInspired = false;
}

//selects a move for the enemy to do on its turn (move probabilities are weighted)
int Entity::chooseMove() {
	//seed RNG
	srand(time(0));
	int roll = ((rand() % 11) + 1); //[1-10]

	//10% chance for dragon to fire breathe, 10% chance for normal skill (claw swipe)
	if (name == "Dragon" && roll == 10 && skillPoints > 0) {
		return 4;
	}

	//50% chance to attack
	if (roll < 6) { 
		return 1;
	}
	//30% chance to defend
	if (roll > 5 && roll < 9) {
		return 2;
	}
	//20% chance to use skill
	if (roll > 8 && skillPoints > 0) {
		return 3;
	}

	return 1; //defaults to attack if out of skill points and skill is attempted

}

//carries out an attack on the given target
std::string Entity::attackF(Entity* target)
{
	//seed RNG
	clock_t seed;
	seed = clock();
	srand(seed);

	isDefending = false;
	int damage = 0;
	std::string result = "";

	//string stream to convert damage integer to string
	std::string damageToString;
	std::stringstream sStream;
	
	//defensive position blocks incoming attacks
	if (target->isDefending_F()) {
		result = "\n" + target->getName() + " blocked " + name + "'s attack.\n";
		return result;
	}

	//if attacker has advantage, 1.5 base damage dealt; if target has advantage, 1.5 damage reduced
	if (isInspired) {
		damage = 1.5*attack*((rand() % 5) + 1); //damage dealt will be a random value [1,5] multiplied by 1.5* the attacker's attack value
	}
	else {
		damage = attack*((rand() % 5) + 1); //damage dealt will be a random value [1,5] multiplied by the attacker's attack value
	}

	if (target->isInspired_F()) {
		damage -= (1.5*target->getDefense()); //reduce incoming damage by 1.5* the target's defense rating
	}
	else {
		damage -= target->getDefense(); //reduce incoming damage by the target's defense rating
	}

	//make sure attacks wont give back health
	if (damage < 0) { 
		damage = 0;
	}
	//0 damage counts as a "miss"
	if (damage == 0) {
		result = "\n" + name + " missed " + target->getName() + ".\n";
		return result;
	}
	if (damage > 0) {

		damage += intelligence; //add intelligence and strength as constant bonus to damage
		damage += strength;

		target->setHitPoints(target->getHitPoints() - damage); //reduce the target's hitpoints by the final calculated damage
		sStream << damage;
		result = "\n" + name + " attacked " + target->getName() + " for " + sStream.str() + " damage.\n";
		return result;
	}

	return result;
	
}

//change entities battle stance to defensive; incoming attacks will be blocked for the next turn
std::string Entity::defend() {

	isDefending = true;
	return name + " defended.\n";
}

//Orc unique skill (requires definition here since enemy vector is made up of Entity*); battle cry: gives all enemies a 1.5 bonus to attacks and defense for 1 turn
std::string Entity::battleCry(std::vector<Entity*> enemies) {
	isDefending = false;
	skillPoints -= 10;
	std::string result;

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->becomeInspired();
	}

	result = "\n" + name + " used " + getSkill() + ". All enemies are inspired for the next turn and will do 50% more damage and block 50% more damage\n";
	return result;
}


