#include "stdafx.h"
#include "Orc.h"

//Orc enemy class for Dungeon++ game; written by Mitch Davis

Orc::Orc()
{
	name = "Orc";

	

	speed = 50; //medium speed
	strength = 80; //high strength
	intelligence = 10; //very low intelligence
	attack = 60; //average attack
	defense = 80; //high defense
	
	hitPoints = 500; //medium HP
	skillPoints = 100;
	isNPC = true;
	isDefending = false;
	isInspired = false;
}


Orc::~Orc()
{
}

//Orc's skill is defined in Entity.cpp
std::string Orc::useSkill(std::vector<Entity*> enemies) {
	return "";
}

std::string Orc::getSkill() {
	return "battle cry";
}

std::string Orc::fireBreath(std::vector<Entity*>) {
	return "This class may not use fire breath";
}