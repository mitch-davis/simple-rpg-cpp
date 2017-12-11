#pragma once

#include <iostream>
#include <string>
#include <vector>

//user interface class
#include "RPGDisplay.h"

//enemy classes
#include "Dragon.h"
#include "Orc.h"
#include "Bandit.h"

//hero classes
#include "Cleric.h"
#include "Mage.h"
#include "Warrior.h"



class Game
{
public:
	Game();
	~Game();

	int play(); //handles the entire game process
	

private:
	
	int numLevelsWon; //increases by 1 after each battle victory
	int fileLoaded; //tracks the file from which the game was loaded (if it was loaded)
	std::string actionResult; //describes the most recent action taken by heroes or enemies
	std::vector<Entity*> enemies; //holds the pointers to the enemies
	std::vector<Entity*> heroes; //holds the pointers to the heroes
	RPGDisplay board; //encapsulates the user interface for the game instance

	int load(); //loads a previous ongoing game if it exists
	void readSave(char*, std::fstream&); //loads char array with the text of the save file
	void printSave(char*); //prints the contents of a save file
	void parseSave(char*); //loads the game member variables with the appropriate save properties
	int save(); //saves the current game stats at user request or once all heroes die
	int savesFull(); //prompts user to select save to overwrite when all save slots are full
	int partySelect(); //prompts the user to select their team of heroes
	int chooseHero(int); //prompts the user to select the hero class for the given hero slot
	int buildEncounter(); //builds a random encounter of enemies for the heroes to fight (different possibilities based on level)
	int encounter(); //runs through the battle sequence until either all enemies are defeated or all heroes have died
	int chooseTarget(std::vector<Entity*> group); //prompts user to select the target for their move
	void enemyRound(Entity*); //run's through an individual enemy's turn
	void heroRound(Entity*); //runs through an individual hero's turn
	void inspirationalVictory(); //gives the heroes an advantage for one turn (activates after defeating a group of enemies)

	std::vector<Entity*> makeNewEnemyBank(); //makes a new enemy bank to avoid loading different enemy slots with the same object pointer
	std::vector<Entity*> getTurnOrder(); //sorts the entities present in the encounter from high to low based on their speed stat
	void check_and_clearCinFail(); //user input validation
	

};

