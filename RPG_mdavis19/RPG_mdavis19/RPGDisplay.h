#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Hero.h"
#include "Enemy.h"

class RPGDisplay
{
public:
	RPGDisplay();
	RPGDisplay(std::vector<Entity*>, std::vector <Entity*>);
	~RPGDisplay();
	void display();
	void refresh();
	void displayEnemies();
	void displayHeroes();
	void update(std::vector<Entity*>, std::vector <Entity*>);
private:
	std::vector<Entity*> heroes;
	std::vector<Entity*> enemies;
	void displayOneEnemy();
	void displayTwoEnemies();
	void displayThreeEnemies();
	void displayOneHero();
	void displayTwoHeroes();
	void displayThreeHeroes();
	void drawLines(int numberOfCharaters);
	void drawEnemyNames(int numberOfCharacters);
	void drawHeroNames(int numberOfCharacters);
	void drawEnemyHP(int numberOfCharacters);
	void drawEnemySP(int numberofCharacters);
	void drawHeroHP(int numberOfCharacters);
	void drawHeroSP(int numberOfCharacters);
	void RPGDisplay::drawDefense_Status(int numberOfCharacters);

};
