#pragma once
#include <string>
#include <iostream>
#include <time.h>
#include <vector>
#include <sstream>

class Entity
{
public:
	Entity();
	~Entity();


	std::string attackF(Entity*);  //carries out an attack on the given entity
	std::string defend(); //sets stance to defend, entity will block normal attacks, but skills will penetrate the defense
	virtual std::string useSkill(Entity*) = 0; //virtual function, see children classes for their skills
	virtual std::string getSkill() = 0; //virtual function, see children for their skill names
	virtual std::string fireBreath(std::vector<Entity*>) = 0; //virtual function, see dragon class for this skill
	std::string battleCry(std::vector<Entity*> enemies); //orc class skill; gives enemy team an advantage for 1 turn
	

	//accessors
	std::string getName();
	int getHitPoints();
	int getSkillPoints();
	int getDefense();
	int getSpeed();
	bool isNPC_F(); 
	bool isDefending_F();
	bool isBleeding_F();
	bool isInspired_F();
	//mutators
	void breakDefense();
	void setHitPoints(int);
	void setSkillPoints(int);
	void startBleeding();
	void stopBleeding();
	void becomeInspired();
	void inspirationFade();

	int chooseMove(); //selects a move for the NPCs

protected:
	bool isNPC;       //used for determining which type of round is to proceed
	bool isDefending; //entity blocks incoming attacks while active
	bool isBleeding; //entity takes 50 damage each turn sequence while true
	bool isInspired; //entity does 50% more base damage and defense when true

	int strength; //pairs with intelligence to give damage bonus after damage calculation (see Entity.attack())
	int intelligence; //pairs with strength to give damage bonus after damage calculation (see Entity.attack())
	int attack; //the base amount that damage is calculated by
	int defense; //the amount incoming damage will be reduced by
	int hitPoints;  //max HP for all heroes is 1000, enemies don't heal so maxHP wont factor in
	int skillPoints; //each entity starts with 100 and skills cost 10 points, dragon's fire breath costs 20. after depleted skills may not be used
	int speed; //determines turn order in the battle
	std::string name; //name of the entity
};

