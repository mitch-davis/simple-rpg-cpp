#include "stdafx.h"
#include "RPGDisplay.h"

//A quick and dirty way of displaying turn based RPG combat with up to
//3 enemies versus up to 3 heroes
//made for use in CS3060 by Christopher Malec

const int CONSOLE_WIDTH = 80; //average console size
const int MAX_NAME_SIZE = 20; //maximum number of chars for a line of Information

//defaultConstructor
RPGDisplay::RPGDisplay()
{
	//TODO: default parameters
}

//constructor
RPGDisplay::RPGDisplay(std::vector<Entity*> myHeroes, std::vector<Entity*> myEnemies)
{
	heroes = myHeroes;
	enemies = myEnemies;

}


RPGDisplay::~RPGDisplay()
{
}

void RPGDisplay::display()
{
	//clear before updating
	refresh();
	displayEnemies();
	std::cout << std::string(5, '\n'); //spaces out enemies and players
	displayHeroes();

}
//Clears console window by printing a bunch of lines
void RPGDisplay::refresh()
{
	for (int i = 0; i < 100; i++) {
		std::cout << std::endl;
	}
}

//display enemies formatted based on number of enemies
void RPGDisplay::displayEnemies()
{
	int numEnemies = enemies.size();
	switch (numEnemies) {
	case 1:
		displayOneEnemy();
		break;
	case 2:
		displayTwoEnemies();
		break;
	case 3:
		displayThreeEnemies();
		break;
	default:
		std::cout << "Invalid Number of Enemies" << std::endl;
		break;

	}

}

//displays the heroes formatted based on number of heroes in party
void RPGDisplay::displayHeroes()
{
	int numHeroes = heroes.size();
	switch (numHeroes) {
	case 1:
		displayOneHero();
		break;
	case 2:
		displayTwoHeroes();
		break;
	case 3:
		displayThreeHeroes();
		break;
	default:
		std::cout << "Invalid Number of Heroes" << std::endl;
		break;

	}
}

//updates the entity vectors to reflect changes from actions taken; this method written by Mitch Davis
void RPGDisplay::update(std::vector<Entity*> heroesIn, std::vector <Entity*> enemiesIn)
{
	heroes = heroesIn;
	enemies = enemiesIn;
}

//displays one enemy
void RPGDisplay::displayOneEnemy()
{

	//pad to center info
	drawLines(1);
	//display name
	drawEnemyNames(1);
	//display hitpoints
	drawEnemyHP(1);
	drawEnemySP(1);
	//bottom line
	drawLines(1);
}

//displays 2 enemies
void RPGDisplay::displayTwoEnemies()
{

	//displayTopLines
	drawLines(2);

	//display names
	drawEnemyNames(2);

	//display hitpoints
	drawEnemyHP(2);
	drawEnemySP(2);

	//display bottom lines
	drawLines(2);
}

//displays 3 enemies
void RPGDisplay::displayThreeEnemies()
{

	//displayTopLines
	drawLines(3);

	//display names
	drawEnemyNames(3);

	//display HP
	drawEnemyHP(3);
	drawEnemySP(3);

	//display Bottom Lines
	drawLines(3);
}

//displays 1 hero
void RPGDisplay::displayOneHero()
{

	//drwa top line
	drawLines(1);
	//display name
	drawHeroNames(1);
	//display hitpoints
	drawHeroHP(1);
	drawHeroSP(1);
	//bottom line
	drawLines(1);
}

//displays 2 heroes
void RPGDisplay::displayTwoHeroes()
{
	int leftPad = 15;
	int centerPad = 10;
	std::string hero0HP = "HP: " + std::to_string(heroes[0]->getHitPoints());
	std::string hero1HP = "HP: " + std::to_string(heroes[1]->getHitPoints());
	int hero0HPPad = (MAX_NAME_SIZE / 2) - (hero0HP.length() / 2);
	int hero1HPPad = (MAX_NAME_SIZE / 2) - (hero1HP.length() / 2);

	//displayTopLines
	drawLines(2);

	//display names
	drawHeroNames(2);

	//display hitpoints
	std::cout << std::string(leftPad, ' ') << '|' << std::string(hero0HPPad, ' ');
	std::cout << hero0HP;
	if (hero0HP.length() % 2 == 0)
		std::cout << ' ';
	std::cout << std::string(hero0HPPad - 1, ' ') << '|';
	std::cout << std::string(centerPad, ' ');
	std::cout << '|' << std::string(hero1HPPad, ' ');
	std::cout << hero1HP;
	if (hero1HP.length() % 2 == 0)
		std::cout << ' ';
	std::cout << std::string(hero1HPPad - 1, ' ') << '|';
	std::cout << std::endl;

	drawHeroSP(2);
	//display bottom lines
	drawLines(2);
}

//displays 3 heroes
void RPGDisplay::displayThreeHeroes()
{

	//displayTopLines
	drawLines(3);

	//display names
	drawHeroNames(3);

	//display HP
	drawHeroHP(3);
	drawHeroSP(3);

	//display Bottom Lines
	drawLines(3);
}

//draws lines for either 1, 2, or 3 enemies/heroes
void RPGDisplay::drawLines(int numberOfCharacters)
{
	int borderPadding;
	int centerPadding;
	switch (numberOfCharacters) {
	case 1:
		borderPadding = (CONSOLE_WIDTH / 2) - (MAX_NAME_SIZE / 2);
		std::cout << std::string(borderPadding, ' ');
		std::cout << std::string(MAX_NAME_SIZE + 2, '-');
		std::cout << std::endl;
		break;
	case 2:
		borderPadding = 15;
		centerPadding = 10;
		std::cout << std::string(borderPadding, ' ') << std::string(MAX_NAME_SIZE + 2, '-');
		std::cout << std::string(centerPadding, ' ') << std::string(MAX_NAME_SIZE + 2, '-');
		std::cout << std::endl;
		break;
	case 3:
		borderPadding = 5;
		std::cout << std::string(borderPadding, ' ') << std::string(MAX_NAME_SIZE + 2, '-');
		std::cout << std::string(borderPadding, ' ') << std::string(MAX_NAME_SIZE + 2, '-');
		std::cout << std::string(borderPadding, ' ') << std::string(MAX_NAME_SIZE + 2, '-');
		std::cout << std::endl;
		break;

	}
}

//builds and displays the name line of enemy party
void RPGDisplay::drawEnemyNames(int numberOfCharacters)
{
	int borderPadding;
	int nameLength;
	int namePadding;
	int centerPadding;
	switch (numberOfCharacters) {
	case 1:
		borderPadding = (CONSOLE_WIDTH / 2) - (MAX_NAME_SIZE / 2);
		nameLength = enemies[0]->getName().length();
		namePadding = (CONSOLE_WIDTH / 2) - (nameLength / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding - borderPadding, ' ');
		std::cout << enemies[0]->getName();
		std::cout << std::string(namePadding - borderPadding, ' ') << '|' << std::endl;
		break;
	case 2:
		centerPadding = 10;
		borderPadding = 15;
		namePadding = (MAX_NAME_SIZE / 2) - (enemies[0]->getName().length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding, ' ');
		std::cout << enemies[0]->getName() << std::string(namePadding, ' ') << '|';
		std::cout << std::string(centerPadding, ' ');
		namePadding = (MAX_NAME_SIZE / 2) - (enemies[1]->getName().length() / 2);
		std::cout << '|' << std::string(namePadding, ' ') << enemies[1]->getName();
		std::cout << std::string(namePadding, ' ') << '|';
		std::cout << std::endl;
		break;
	case 3:
		borderPadding = 5;
		namePadding = (MAX_NAME_SIZE / 2) - (enemies[0]->getName().length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding, ' ');
		std::cout << enemies[0]->getName();
		if (enemies[0]->getName().length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(namePadding - 1, ' ') << '|';
		namePadding = (MAX_NAME_SIZE / 2) - (enemies[1]->getName().length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding, ' ');
		std::cout << enemies[1]->getName();
		if (enemies[1]->getName().length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(namePadding - 1, ' ') << '|';
		namePadding = (MAX_NAME_SIZE / 2) - (enemies[0]->getName().length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding, ' ');
		std::cout << enemies[2]->getName();
		if (enemies[2]->getName().length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(namePadding - 1, ' ') << '|';
		std::cout << std::endl;


	}
}

//builds and displays the name line of a hero party
void RPGDisplay::drawHeroNames(int numberOfCharacters)
{
	int borderPadding;
	int nameLength;
	int namePadding;
	int centerPadding;
	switch (numberOfCharacters) {
	case 1:
		borderPadding = (CONSOLE_WIDTH / 2) - (MAX_NAME_SIZE / 2);
		nameLength = heroes[0]->getName().length();
		namePadding = (CONSOLE_WIDTH / 2) - (nameLength / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding - borderPadding, ' ');
		std::cout << heroes[0]->getName();
		if (heroes[0]->getName().length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(namePadding - borderPadding - 1, ' ') << '|' << std::endl;
		break;
	case 2:
		centerPadding = 10;
		borderPadding = 15;
		namePadding = (MAX_NAME_SIZE / 2) - (heroes[0]->getName().length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding, ' ');
		std::cout << heroes[0]->getName();
		if (heroes[0]->getName().length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(namePadding - 1, ' ') << '|';
		std::cout << std::string(centerPadding, ' ');
		namePadding = (MAX_NAME_SIZE / 2) - (heroes[1]->getName().length() / 2);
		std::cout << '|' << std::string(namePadding, ' ') << heroes[1]->getName();
		if (heroes[1]->getName().length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(namePadding - 1, ' ') << '|';
		std::cout << std::endl;
		break;
	case 3:
		borderPadding = 5;
		namePadding = (MAX_NAME_SIZE / 2) - (heroes[0]->getName().length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding, ' ');
		std::cout << heroes[0]->getName();
		if (heroes[0]->getName().length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(namePadding - 1, ' ') << '|';
		namePadding = (MAX_NAME_SIZE / 2) - (heroes[1]->getName().length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding, ' ');
		std::cout << heroes[1]->getName();
		if (heroes[1]->getName().length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(namePadding - 1, ' ') << '|';
		namePadding = (MAX_NAME_SIZE / 2) - (heroes[0]->getName().length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(namePadding, ' ');
		std::cout << heroes[2]->getName();
		if (heroes[2]->getName().length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(namePadding - 1, ' ') << '|';
		std::cout << std::endl;


	}
}

//builds and displays the HP line of the enemies
void RPGDisplay::drawEnemyHP(int numberOfCharacters)
{
	std::string hpString;
	int hpPadding;
	int borderPadding;
	int centerPad = 10;
	switch (numberOfCharacters) {
	case 1:
		hpString = "HP: " + std::to_string(enemies[0]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		borderPadding = (CONSOLE_WIDTH / 2) - (MAX_NAME_SIZE / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|' << std::endl;
		break;
	case 2:
		hpString = "HP: " + std::to_string(enemies[0]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		borderPadding = 15;

		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		std::cout << std::string(centerPad, ' ');
		hpString = "HP: " + std::to_string(enemies[1]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		std::cout << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		std::cout << std::endl;
		break;
	case 3:
		hpString = "HP: " + std::to_string(enemies[0]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		borderPadding = 5;
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		hpString = "HP: " + std::to_string(enemies[1]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		hpString = "HP: " + std::to_string(enemies[2]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		std::cout << std::endl;
		break;

	}
}

//builds and displays the HP line for the heroes
void RPGDisplay::drawHeroHP(int numberOfCharacters)
{
	std::string hpString;
	int hpPadding;
	int borderPadding;
	int centerPad = 10;
	switch (numberOfCharacters) {
	case 1:
		hpString = "HP: " + std::to_string(heroes[0]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		borderPadding = (CONSOLE_WIDTH / 2) - (MAX_NAME_SIZE / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|' << std::endl;
		break;
	case 2:
		hpString = "HP: " + std::to_string(heroes[0]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		borderPadding = 15;

		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		std::cout << std::string(centerPad, ' ');
		hpString = "HP: " + std::to_string(heroes[1]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		std::cout << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		std::cout << std::endl;
		break;
	case 3:
		hpString = "HP: " + std::to_string(heroes[0]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		borderPadding = 5;
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		hpString = "HP: " + std::to_string(heroes[1]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		hpString = "HP: " + std::to_string(heroes[2]->getHitPoints());
		hpPadding = (MAX_NAME_SIZE / 2) - (hpString.length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(hpPadding, ' ');
		std::cout << hpString;
		if (hpString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(hpPadding - 1, ' ') << '|';
		std::cout << std::endl;
		break;

	}
}

//draws and displays the SP line for the heroes
void RPGDisplay::drawHeroSP(int numberOfCharacters)
{
	std::string spString;
	int spPadding;
	int borderPadding;
	int centerPad = 10;
	switch (numberOfCharacters) {
	case 1:
		spString = "SP: " + std::to_string(heroes[0]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		borderPadding = (CONSOLE_WIDTH / 2) - (MAX_NAME_SIZE / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|' << std::endl;
		break;
	case 2:
		spString = "SP: " + std::to_string(heroes[0]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		borderPadding = 15;

		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		std::cout << std::string(centerPad, ' ');
		spString = "SP: " + std::to_string(heroes[1]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		std::cout << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		std::cout << std::endl;
		break;
	case 3:
		spString = "SP: " + std::to_string(heroes[0]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		borderPadding = 5;
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		spString = "SP: " + std::to_string(heroes[1]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		spString = "SP: " + std::to_string(heroes[2]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		std::cout << std::endl;
		break;

	}
}

//draws and displays the SP line for the heroes
void RPGDisplay::drawEnemySP(int numberOfCharacters)
{
	std::string spString;
	int spPadding;
	int borderPadding;
	int centerPad = 10;
	switch (numberOfCharacters) {
	case 1:
		spString = "SP: " + std::to_string(enemies[0]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		borderPadding = (CONSOLE_WIDTH / 2) - (MAX_NAME_SIZE / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|' << std::endl;
		break;
	case 2:
		spString = "SP: " + std::to_string(enemies[0]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		borderPadding = 15;

		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		std::cout << std::string(centerPad, ' ');
		spString = "SP: " + std::to_string(enemies[1]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		std::cout << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		std::cout << std::endl;
		break;
	case 3:
		spString = "SP: " + std::to_string(enemies[0]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		borderPadding = 5;
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		spString = "SP: " + std::to_string(enemies[1]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		spString = "SP: " + std::to_string(enemies[2]->getSkillPoints());
		spPadding = (MAX_NAME_SIZE / 2) - (spString.length() / 2);
		std::cout << std::string(borderPadding, ' ') << '|' << std::string(spPadding, ' ');
		std::cout << spString;
		if (spString.length() % 2 == 0)
			std::cout << ' ';
		std::cout << std::string(spPadding - 1, ' ') << '|';
		std::cout << std::endl;
		break;

	}
}

void RPGDisplay::drawDefense_Status(int numberOfCharacters) {
	int borderPadding;
	int centerPad = 10;
	std::string dString = "Defending";
	int dPadding;
	switch (numberOfCharacters) {
	case 1:
		//dString = "SP: " + std::to_string(enemies[0]->getSkillPoints());
		if (heroes[0]->isDefending_F()) {

			dPadding = (MAX_NAME_SIZE / 2) - (dString.length() / 2);
			borderPadding = (CONSOLE_WIDTH / 2) - (MAX_NAME_SIZE / 2);
			std::cout << std::string(borderPadding, ' ') << '|';
			std::cout << std::string(MAX_NAME_SIZE, '-') << '|';
			std::cout << std::endl << std::string(borderPadding, ' ') << '|' << std::string(dPadding, ' ');
			std::cout << dString;
			if (dString.length() % 2 == 0)
				std::cout << ' ';
			std::cout << std::string(dPadding - 1, ' ') << '|' << std::endl;
		}
		else {
			dString = "Not Defending";
			dPadding = (MAX_NAME_SIZE / 2) - (dString.length() / 2);
			borderPadding = (CONSOLE_WIDTH / 2) - (MAX_NAME_SIZE / 2);
			std::cout << std::string(borderPadding, ' ') << '|';
			std::cout << std::string(MAX_NAME_SIZE, '-') << '|';
			std::cout << std::endl << std::string(borderPadding, ' ') << '|' << std::string(dPadding, ' ');
			std::cout << dString;
			if (dString.length() % 2 == 0)
				std::cout << ' ';
			std::cout << std::string(dPadding - 1, ' ') << '|' << std::endl;
		}
		break;
	case 2:

		borderPadding = 15;

		std::cout << std::string(centerPad, ' ');

		break;
	case 3:
	
		break;

	}
}
