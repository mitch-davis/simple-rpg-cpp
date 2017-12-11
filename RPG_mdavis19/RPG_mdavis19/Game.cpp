#include "stdafx.h"
#include "Game.h"
#include <time.h>
#include <fstream>

//Game class for Dungeon++ game; written by Mitch Davis
//handles the operations of the RPG, including party setup, encounter building, and battle sequence

Game::Game()
{
	numLevelsWon = -1; //represents the level
	fileLoaded = 0;
	board = RPGDisplay(heroes, enemies); //represents the game board
}

Game::~Game()
{
}

//handles the game sequence
int Game::play()
{
	//loop constitutes the entire game sequence. only ends at user request
	for (; ;){
	int selection = 0;
	int battleResult; //0 = win, 1 = lose

	std::cout << "\n\nWelcome to Dungeon++";
	do {
		std::cout << "\n--------------------------";
		std::cout << "\n\nPlease select an option:";
		std::cout << "\n1 - New Game";
		std::cout << "\n2 - Load Game";
		std::cout << "\n3 - Quit\n";
		std::cin >> selection;

		check_and_clearCinFail();

	} while (selection != 1 && selection != 2 && selection != 3);

	switch (selection) {
	case 1:
		heroes.clear(); //clear any heroes in the hero vector from a previous game
		partySelect(); //prompt user to build their party
		//level starts here
		do {
			numLevelsWon++;
			printf("\nLevel %d\n\n", numLevelsWon + 1);
			system("pause");
			buildEncounter(); //make a random encounter of enemies for the user to fight
			battleResult = encounter();
			if (battleResult == 0) //after each successful battle, heroes will get a one turn advantage
				inspirationalVictory();
		} while (battleResult != 1);
		break; //after all heroes die, user will be sent back to welcome screen where they can play again or quit
	case 2:
		int loadResult;
		loadResult = load(); //load a game in-progress
		if (loadResult == 1) //restart if load cancelled
			play();
		printf("\nLevel %d\n\n", numLevelsWon + 1);
		system("pause");
		battleResult = encounter(); //do first level outside of loop after load
		if (battleResult == 0) 
			inspirationalVictory();
		//then after first level, enter loop
		do {
			numLevelsWon++;
			printf("\nLevel %d\n\n", numLevelsWon + 1);
			system("pause");
			buildEncounter(); //make a random encounter of enemies for the user to fight
			battleResult = encounter();
			if (battleResult == 0) //after each successful battle, heroes will get a one turn advantage
				inspirationalVictory();
		} while (battleResult != 1);
		break; //after all heroes die, user will be sent back to welcome screen where they can play again or quit
		//TODO: add game sequence after game is loaded; need to finish writing load() first
		break;
	case 3:
		std::cout << "\n\nThanks for playing!\n";
		exit(0);
		return 0;
		break;
	}
	std::cout << "\n\nThanks for playing!\n";
	}
}

//loads a game in-progress
int Game::load() {
	//supports 3 save files
	//try opening all 3 files...
	//make 3 char pointer arrays to store the file contents respectively
	std::fstream save1;
	save1.open("Save1.txt", std::ios::in);
	char file1Contents[256];

	std::fstream save2;
	save2.open("Save2.txt", std::ios::in);
	char file2Contents[256];

	std::fstream save3;
	save3.open("Save3.txt", std::ios::in);
	char file3Contents[256];

	int saveSelect = 0;
	int numSaves; //possible [0,3] saves
	do {
		numSaves = 0;
		//check that the save file is open
		if (save1.is_open()) {
			std::cout << "\nSelect a save: ";
			std::cout << "\n1 - Save 1\n-------------------"; 
			readSave(file1Contents, save1); //read contents into a char array
			printSave(file1Contents); //print so the user can see what save contains
			std::cout << "-------------------\n";
			numSaves++; //track number of saves
		}
		if (save2.is_open()) {
			std::cout << "\n2 - Save 2\n-------------------";
			readSave(file2Contents, save2);
			printSave(file2Contents);
			std::cout << "-------------------\n";
			numSaves++;
		}
		if (save3.is_open()) {
			std::cout << "\n3 - Save 3\n-------------------";
			readSave(file3Contents, save3);
			printSave(file3Contents);
			std::cout << "\n-------------------\n";
			numSaves++;
		}
		if (numSaves != 0) {
			printf("%d - Cancel\n", (numSaves + 1)); //gives the option to cancel load
		}
		else {
			std::cout << "There are no saves to load."; //auto-correction if there are no saves to load
			return 1; //return code 1 restarts the game
		}
		
		std::cin >> saveSelect;
		check_and_clearCinFail(); //control for alpha/symbol input
		
	} while (saveSelect < 1 || saveSelect > (numSaves + 1)); //dynamic input validation based on numSaves
		
	//close the save files
	save1.close();
	save2.close();
	save3.close();
	
	if (saveSelect == numSaves + 1) {
		std::cout << "\nLoad game cancelled: returning to main menu...\n";
		return 1; //1 return code essentially restarts the game
	}
	else {

		switch (saveSelect)
		{
		case 1:
			parseSave(file1Contents); //get game instance from the file's contents and load variables
			board.update(heroes, enemies); //set board to reflect the loaded game
			fileLoaded = 1; //sets the file loaded value so if game is saved again it will automatically overwrite the same file
			break;
		case 2:
			parseSave(file2Contents);
			board.update(heroes, enemies);
			fileLoaded = 2;
			break;
		case 3:
			parseSave(file3Contents);
			board.update(heroes, enemies);
			fileLoaded = 3;
			break;
		}
		return 0;
	}
}

//reads save file into char array
void Game::readSave(char* saveContents, std::fstream& save) {

	int fileIndex = 0;
	//load the file into the char array until end of file
	while (!save.eof()) {
		save.get(saveContents[fileIndex]);
		fileIndex++;
	}
}

//prints the contents of a save file
void Game::printSave(char* saveContents) {
	int i = 0;
	std::cout << "\nLevels Won: ";
	//print the file contents until end of file (marked by !)
	do {
		std::cout << saveContents[i];
		i++;
	} while (saveContents[i] != *"!");
}

//loads the game member variables with the appropriate save properties
void Game::parseSave(char* save) {

	bool passedHyphen = false; //hyphen marks switch from heroes to enemies in the save file
	int hp = 0;
	int sp = 0;
	int saveIndex = 0;
	numLevelsWon = 0;
	heroes.clear(); //clear the entity vectors to prepare them for the new parties
	enemies.clear();
	
	//step through the levelsWon field to find the magnitude of the value
	//then backtrack and use the magnitude to get 10^n*index, decreasing on each passthrough until magnitude reaches 0
	//process is the same for each integer value to be parsed from save file
	int levelsMagnitude = 0;
	for (int i = 0; ; i++) {
		if (save[i] == *"\n") {
			for (int j = (i - levelsMagnitude); ; j++) {
				if (save[j] == *"\n") {
					break;
				}
				numLevelsWon += ((save[j] - 48)*pow(10, levelsMagnitude - 1)); //ASCII value - 48 gives integer
				levelsMagnitude--;
			}
			saveIndex = (i + 1);
			break;
		}

		levelsMagnitude++;
	}

	//i is the hero/enemy vector index, j is the entity name field, k is the hp field, and l is the sp field, saveIndex tracks where in the file we left off
	for (int i = 0;; i++) {
		hp = 0; //reset the hp and sp on each iteration
		sp = 0;
		std::string entityName = ""; //reset the entity name on each iteration

		if (save[saveIndex] == *"!") //stop at the end of file
			break;
		if (save[saveIndex] == *"-") { //switch to "enemy loading mode" after the hyphen
			i = 0; //reset the vector index
			saveIndex += 2; //pass -\n characters
			passedHyphen = true;
		}
		
		for (int j = saveIndex;; j++) {
			if (save[j] == *" ") {
				saveIndex = (j + 1);
				break;
			}
			entityName += save[j];
		}
		
		//load the appropriate entity into the appropriate entity vector
		if (entityName == "Bandit") {
			Bandit* b = new Bandit();
			Entity *bandit = b;
			enemies.push_back(bandit);
		}
		if (entityName == "Cleric") {
			Cleric* c = new Cleric();
			Entity *cleric = c;
			heroes.push_back(cleric);
		}
		if (entityName == "Dragon") {
			Dragon* d = new Dragon();
			Entity *dragon = d;
			enemies.push_back(dragon);
		}
		if (entityName == "Mage") {
			Mage* m = new Mage();
			Entity *mage = m;
			heroes.push_back(mage);
		}
		if (entityName == "Orc") {
			Orc* o = new Orc();
			Entity *orc = o;
			enemies.push_back(orc);
		}
		if (entityName == "Warrior") {
			Warrior* w = new Warrior();
			Entity *warrior = w;
			heroes.push_back(warrior);
		}
		
		//get hp value
		int hpMagnitude = 0;
		for (int k = saveIndex; ; k++) {
			if (save[k] == *" ") {
				for (int h = (k - hpMagnitude); ; h++) {
					if (save[h] == *" ") {
						break;
					}
					hp += ((save[h] - 48)*pow(10, hpMagnitude - 1));
					hpMagnitude--;
				}
				saveIndex = (k + 1);
				break;
			}
			
			hpMagnitude++;
		}
		//get sp value
		int spMagnitude = 0;
		for (int l = saveIndex; ; l++) {
			if (save[l] == *"\n") {
				for (int h = (l - spMagnitude); ; h++) {
					if (save[h] == *"\n") {
						break;
					}
					sp += ((save[h] - 48)*pow(10, spMagnitude - 1));
					spMagnitude--;
				}
				saveIndex = (l + 1);
				break;
			}

			spMagnitude++;
		}

		//load the entity's hp and sp fields, after checking if they are an enemy or hero
		if (passedHyphen == false) {
			heroes[i]->setHitPoints(hp);
			heroes[i]->setSkillPoints(sp);
		}
		else {
			enemies[i]->setHitPoints(hp);
			enemies[i]->setSkillPoints(sp);
		}

	}
}

//will save a game in-progress
int Game::save() {

	int overwrite;
	std::fstream SaveFile; //file strem for the file to be written to
	std::fstream FileCheck; //checks that a file exists to control for 3 save slots

	FileCheck.open("Save1.txt", std::ios::in); //start by checking for save1

	//when save is open and it wasn't loaded from...
	if (FileCheck.is_open() && fileLoaded != 1) {
		FileCheck.close(); //...close the file stream...
		//... open save2 to check for save2...continue process for 3 saves if necessary
		FileCheck.open("Save2.txt", std::ios::in);
		if (FileCheck.is_open() && fileLoaded != 2) {
			FileCheck.close();
			FileCheck.open("Save3.txt", std::ios::in);
			if (FileCheck.is_open() && fileLoaded != 3) {
			
				overwrite = savesFull();//if all 3 save slots are full and none were loaded from, let user choose one to overwrite or to cancel saving

				switch (overwrite) {
				case 1:
					SaveFile.open("Save1.txt", std::ios::out);
					break;
				case 2:
					SaveFile.open("Save2.txt", std::ios::out);
					break;
				case 3:
					SaveFile.open("Save3.txt", std::ios::out);
					break;
				}
			}
			else {
				FileCheck.close();
				SaveFile.open("Save3.txt", std::ios::out);
			}
		}
		else {
			FileCheck.close();
			SaveFile.open("Save2.txt", std::ios::out);
		}
	}
	else {
		FileCheck.close();
		SaveFile.open("Save1.txt", std::ios::out);
	}

	//save format:  levelswon
	//              heroname  hp sp
	//              -
	//              enemyname hp sp
	//              !
	SaveFile << numLevelsWon << '\n';

	for (int i = 0; i < heroes.size(); i++) {
		SaveFile << heroes[i]->getName() << ' ' << heroes[i]->getHitPoints() << ' ' << heroes[i]->getSkillPoints() << '\n';
	}

	SaveFile << "-\n"; //- marks barrier between heroes and enemies 

	for (int i = 0; i < enemies.size(); i++) {
			SaveFile << enemies[i]->getName() << ' ' << enemies[i]->getHitPoints() << ' ' << enemies[i]->getSkillPoints() << '\n';
	}

	SaveFile << "!"; //! marks end of file

	SaveFile.close(); //close the file stream once no longer needed

	return 0;
}

//activates if all 3 save slots are used; prompts user to overwrite or cancel save
int Game::savesFull() {

	//open the file streams of the 3 saves, make char array pointers to store their contents
	std::fstream save1;
	save1.open("Save1.txt", std::ios::in);
	char file1Contents[256];

	std::fstream save2;
	save2.open("Save2.txt", std::ios::in);
	char file2Contents[256];

	std::fstream save3;
	save3.open("Save3.txt", std::ios::in);
	char file3Contents[256];


	int overwrite; //the file # to be overwritten
	
	do {
		//print the contents of the saves so that user knows what they are overwriting
		std::cout << "\n1 - Save 1\n-------------------";
		readSave(file1Contents, save1);
		printSave(file1Contents);
		std::cout << "-------------------\n";
		
		std::cout << "\n2 - Save 2\n-------------------";
		readSave(file2Contents, save2);
		printSave(file2Contents);
		std::cout << "-------------------\n";
		
		std::cout << "\n3 - Save 3\n-------------------";
		readSave(file3Contents, save3);
		printSave(file3Contents);
		std::cout << "\n-------------------\n";
		
		std::cout << "\nSAVE SLOTS FULL!\n";
		std::cout << "\nSelect a save to overwrite: ";

		std::cin >> overwrite;
		check_and_clearCinFail();
	} while (overwrite != 1 && overwrite != 2 && overwrite != 3 && overwrite != 4);

	if (overwrite == 4) {
		do {
			std::cout << "\nAll progress from this game will be lost. Continue?\n1 - Yes\n2 - No\n"; //double check since game data will be lost
			std::cin >> overwrite;
			check_and_clearCinFail();
		} while (overwrite != 1 && overwrite != 2);

		if (overwrite == 1) {
			exit(0); //close program
		}
		else {
			save(); //if user changes their mind, try saving again
		}
	}

	return overwrite; //return the file number to be overwritten
}

//gets the hero party from the user
int Game::partySelect() {

	//get number of heroes from user
	int partySize = 0;
	do {
		std::cout << "\nHow many heroes would you like to be in your party? (1, 2, or 3)\n";
		std::cin >> partySize;
		check_and_clearCinFail();
	} while (partySize < 1 || partySize > 3);

	//prompt user to select their hero classes
	switch (partySize) {
	case 1:
		chooseHero(1);
		break;
	case 2:
		chooseHero(1);
		chooseHero(2);
		break;
	case 3:
		chooseHero(1);
		chooseHero(2);
		chooseHero(3);
		break;
	}

	return 0;
}

//build a random group of enemies to fight, based on level
int Game::buildEncounter() {

	//seed RNG
	srand(time(0));
	std::vector<Entity*> enemyBank;
	enemies.clear();

	int randEnemy = 0; //0 = bandit, 1 = orc, 2 = dragon
	int numEnemies = 0; //1, 2, or 3

	if (numLevelsWon < 4)   //Levels 0-3: just one enemy, bandit or orc
	{
		numEnemies = 1;

		for (int i = 0; i < numEnemies; i++) {
			enemyBank = makeNewEnemyBank();
			randEnemy = (rand() % 2);
			enemies.push_back(enemyBank[randEnemy]);
			
		}
		enemyBank.erase(enemyBank.begin(), enemyBank.begin() + 2); //delete enemy bank to clear memory
	}
	if (numLevelsWon > 3 && numLevelsWon < 8) {  //Levels 4-7: up to two enemies, bandit or orc
		numEnemies = (rand() % 2) + 1;

		for (int i = 0; i < numEnemies; i++) {
			enemyBank = makeNewEnemyBank();
			randEnemy = (rand() % 2);
			enemies.push_back(enemyBank[randEnemy]);
		}
		enemyBank.erase(enemyBank.begin(), enemyBank.begin() + 2); //delete enemy bank to clear memory
	}
	if (numLevelsWon == 8) {
		enemyBank = makeNewEnemyBank();  //Level 8: 1 dragon
		enemies.push_back(enemyBank[2]);
		enemyBank.erase(enemyBank.begin(), enemyBank.begin() + 2); //delete enemy bank to clear memory
	}
	if (numLevelsWon > 8 && numLevelsWon < 13) {    //Level 9-12: any combo of up to 3 enemies
		numEnemies = (rand() % 3) + 1;

		for (int i = 0; i < numEnemies; i++) {
			enemyBank = makeNewEnemyBank();
			randEnemy = (rand() % 3);
			enemies.push_back(enemyBank[randEnemy]);
		}
		enemyBank.erase(enemyBank.begin(), enemyBank.begin() + 2); //delete enemy bank to clear memory
	}
	if (numLevelsWon > 12 && numLevelsWon < 16) {    //Level 13-15: any combo of up to 3 enemies; guarantee 2 enemies
		numEnemies = (rand() % 2) + 2;

		for (int i = 0; i < numEnemies; i++) {
			enemyBank = makeNewEnemyBank();
			randEnemy = (rand() % 3);
			enemies.push_back(enemyBank[randEnemy]);
		}
		enemyBank.erase(enemyBank.begin(), enemyBank.begin() + 2); //delete enemy bank to clear memory
	}
	if (numLevelsWon == 16)  //Level 16: 2 dragons
	{
		enemyBank = makeNewEnemyBank();
		enemies.push_back(enemyBank[2]);
		enemyBank = makeNewEnemyBank();
		enemies.push_back(enemyBank[2]);
		enemyBank.erase(enemyBank.begin(), enemyBank.begin() + 2); //delete enemy bank to clear memory
	}
	if (numLevelsWon > 16) {    //Level 17 and beyond: any combo of guarantee 3 enemies
		numEnemies = 3;

		for (int i = 0; i < numEnemies; i++) {
			enemyBank = makeNewEnemyBank();
			randEnemy = (rand() % 3);
			enemies.push_back(enemyBank[randEnemy]);
		}
		enemyBank.erase(enemyBank.begin(), enemyBank.begin() + 2); //delete enemy bank to clear memory
	}

	board.update(heroes, enemies); //update the board with the new enemies

	return 0;
}

//handles the battle sequence
int Game::encounter() {

	board.display(); //start by showing the board

	std::vector<Entity*> turnOrder;
	turnOrder = getTurnOrder(); //sort entities by speed (high to low)

	//print the turn order
	std::cout << "\nTurn Order:\n";
	for (unsigned int i = 0; i < turnOrder.size(); i++) {
		printf("%d:", (i + 1));
		std::cout << turnOrder[i]->getName();
		std::cout << std::endl;
	}

	//constitutes the turn sequence, ends when all enemies defeated or all heroes defeated or user quits
	for (;;) {
		for (unsigned int i = 0; i < turnOrder.size(); i++) {
			
			//check for valid battle matchup
			if (enemies.size() == 0 || heroes.size() == 0) {
				break;
			}
			//computer turn
			if (turnOrder[i]->isNPC_F()) {
				enemyRound(turnOrder[i]);
			}
			//player turn
			else {
				heroRound(turnOrder[i]);
			}
			//update board with changes
			board.update(heroes, enemies);
			//display changes
			if (enemies.size() > 0 && heroes.size() > 0) {
				board.display();
			}
			//show results of last move
			std::cout << actionResult << std::endl;
			
			system("Pause");

			//remove fallen enemies or heroes from the turn sequence
			for (unsigned int j = 0; j < turnOrder.size(); j++) {
				if (turnOrder[j]->getHitPoints() < 1) {
					turnOrder.erase(turnOrder.begin() + j);
				}
			}
			
		}
		if (enemies.size() == 0 || heroes.size() == 0) {
			break;
		}
	}

	//battle results
	if (enemies.size() == 0) {
		std::cout << "\nYou defeated all of the enemies...\nLoading new battle.\n\n";
		system("pause");
		return 0;
	}
	if (heroes.size() == 0) {
		std::cout << "\nAll of your heroes have fallen... YOU LOSE.\n\n";
		return 1;
	}

	return 0; 
}

//plays through an enemy turn
void Game::enemyRound(Entity* enemy) {
	
	//seed RNG
	srand(time(0));
	//enemy chooses a move and a target
	unsigned int moveSelection = enemy->chooseMove();
	unsigned int targetSelection = (rand() % heroes.size());

	std::cout << "\nIt is " << enemy->getName() << "'s turn.\n";
	system("pause");
	
	//1 = attack, 2 = defend, 3 = skill, 4 (dragon only) = fire breath
	switch (moveSelection) {
	case 1:
		actionResult = enemy->attackF(heroes[targetSelection]);
		break;
	case 2:
		actionResult = enemy->defend();
		break;
	case 3:
		if (enemy->getName() == "Orc") {
			actionResult = enemy->battleCry(enemies);
			return;
		}
		else {
			actionResult = enemy->useSkill(heroes[targetSelection]);
		}
		break;
	case 4:
		actionResult = enemy->fireBreath(heroes);
	}

	//delete heroes if they are killed by the action
	if (heroes[targetSelection]->getHitPoints() < 1) {
		heroes.erase(heroes.begin() + targetSelection);
	}
	//disable advantage at end of turn if it is active
	if (enemy->isInspired_F()) {
		enemy->inspirationFade();
	}
}

//plays through a hero turn
void Game::heroRound(Entity* hero) {

	unsigned int moveSelection = 0;
	unsigned int targetSelection = 0;
	actionResult = "";

	//check if hero is bleeding and apply appropriate damage
	if (hero->isBleeding_F()) {
		srand(time(0));
		hero->setHitPoints(hero->getHitPoints() - 50); //costs 50 hp for each turn bleeding
		int clotChance = (rand() % 3 + 1);
		//66% chance to stop bleeding
		if (clotChance == 1 || clotChance == 2) {
			hero->stopBleeding();
			actionResult += ("\n" + hero->getName() + " took 50 bleed damage. Bleeding has stopped.\n");
			
		}
		//33% chance to keep bleeding for another turn
		else {
			actionResult += ("\n" + hero->getName() + " took 50 bleed damage.\n");
		}
	}

	//get hero's action from user; 1 = attack, 2 = defend, 3 = skill, 4 = quit
	do {
		std::cout << "\nIt is " << hero->getName() << "'s turn. What would you like to do?";
		std::cout << "\n--------------------------";
		std::cout << "\n1 - Attack";
		std::cout << "\n2 - Defend";
		std::cout << "\n3 - Special Move (" << hero->getSkill() << " [costs 10 skill points])";
		std::cout << "\n4 - Save and Quit\n"; //after save() is finished, this will be save and quit, user can resume from this battle
		std::cin >> moveSelection;

		check_and_clearCinFail();

	} while (moveSelection != 1 && moveSelection != 2 && moveSelection != 3 && moveSelection != 4);

	//defend and quit dont need target selections so defaults to enemies[0]
	if (moveSelection == 2 || moveSelection == 4) {
		targetSelection = 1;
	}
	else {
		//cleric's valid targets for skill are fellow heroes
		if (hero->getName() == "Cleric" && moveSelection == 3) {
			targetSelection = chooseTarget(heroes);
		}
		//prompt user to select an enemy target
		else {
			targetSelection = chooseTarget(enemies);
		}
	}
	//carry out move on the selected target
	switch (moveSelection) {
	case 1:
		actionResult += hero->attackF(enemies[targetSelection-1]);
		break;
	case 2:
		actionResult += hero->defend();
		break;
	case 3:
		if (hero->getName() == "Cleric" && moveSelection == 3) {
			actionResult += hero->useSkill(heroes[targetSelection - 1]);
		}
		else {
			actionResult += hero->useSkill(enemies[targetSelection - 1]);
		}
		break;
	case 4:
		int quit;
		//confirm quit
		do {
			std::cout << "\nAre you sure you want to quit?\n";
			std::cout << "--------------------------\n1 - Yes\n2 - No\n";
			std::cin >> quit;
			check_and_clearCinFail();
		} while (quit != 1 && quit != 2);
		if(quit == 1)
		{
			save();
			exit(0);
		}
		else
		{
			//retry turn for same hero
			heroRound(hero);
		}
		break;
	}

	//erase defeated enemies
	if (((hero->getName() == "Cleric") && (moveSelection != 3) && (enemies[targetSelection-1]->getHitPoints() < 1)) || ((hero->getName() != "Cleric") && (enemies[targetSelection - 1]->getHitPoints() < 1))) {
		enemies.erase(enemies.begin() + (targetSelection - 1));
	}
	//cancel adavantage after turn if active
	if (hero->isInspired_F()) {
		hero->inspirationFade();
	}

}

//prompts user to select a target
int Game::chooseTarget(std::vector<Entity*> group) {
	int targetSelection;
	do {
		std::cout << "\nChoose the target: ";
		std::cout << "\n--------------------------";
		for (unsigned int i = 0; i < group.size(); i++) {
			printf("\n%d: ", i + 1);
			std::cout << group[i]->getName();
		}
		std::cout << std::endl;
		std::cin >> targetSelection;
		check_and_clearCinFail();
	} while (targetSelection < 1 || targetSelection > group.size());

	return targetSelection;
}

//makes and returns a new bank of enemies for encounter creation
std::vector<Entity*> Game::makeNewEnemyBank() {

	std::vector<Entity*> enemyBank;

	Bandit* b = new Bandit();
	Entity* bandit = b;

	Orc* o = new Orc();
	Entity* orc = o;

	Dragon* d = new Dragon();
	Entity* dragon = d;

	enemyBank.push_back(bandit);
	enemyBank.push_back(orc);
	enemyBank.push_back(dragon);

	return enemyBank;
}

//sorts all entities by speed from high to low using bubble sort
std::vector<Entity*> Game::getTurnOrder() {

	std::vector<Entity*> turnOrder;

	//push all present entities onto the turnorder vector
	for (unsigned int i = 0; i < heroes.size(); i++) {
		turnOrder.push_back(heroes[i]);
	}
	for (unsigned int i = 0; i < enemies.size(); i++) {
		turnOrder.push_back(enemies[i]);
	}

	//bubble sort (high to low)
	unsigned int i = 0;
	Entity *temp;
	do {
		for (unsigned int j = 0; j < (turnOrder.size() - 1); j++)
		{
			if (turnOrder[j]->getSpeed() < turnOrder[j + 1]->getSpeed())
			{
				temp = turnOrder[j];
				turnOrder[j] = turnOrder[j + 1];
				turnOrder[j + 1] = temp;
			}
		}
		i++;
	} while (i < turnOrder.size());

	//return the sorted vector
	return turnOrder;
}

//prevents an infinite loop from occuring when user gives character inputs to an int
void Game::check_and_clearCinFail() {

	//check for cin error: if non-integers are given, this will prevent spiraling into infinite loop
	if (std::cin.fail()) {
		std::cout << "\n\nPlease enter a valid option.\n\n----------------------------";
		std::cin.clear(); //clear the error state
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //flush the input stream
	}

}

//prompts user to select an individual hero class to go into the hero vector
int Game::chooseHero(int heroNum)
{
	Warrior* w = new Warrior();
	Entity *warrior = w;
	Mage* m = new Mage();
	Entity *mage = m;
	Cleric* c = new Cleric();
	Entity *cleric = c;

	int heroSelection = 0;
	do {
		printf("\nChoose the class of hero %d:", heroNum);
		std::cout << "\n--------------------------";
		std::cout << "\n1 - Warrior | Average damage (physical) ; high defense ";
		std::cout << "\n2 - Mage    | High damage (magical) ; low defense ";
		std::cout << "\n3 - Cleric  | Low damage (holy) ; average defense\n";
		std::cin >> heroSelection;
		check_and_clearCinFail();
	} while (heroSelection != 1 && heroSelection != 2 && heroSelection != 3);
	
	switch (heroSelection) {
	case 1:
		heroes.push_back(warrior);
		break;
	case 2:
		heroes.push_back(mage);
		break;
	case 3:
		heroes.push_back(cleric);
		break;
	}


	return 0;
}

//gives the heroes an advantage for the first turn of the next round
void Game::inspirationalVictory() {
	std::cout << "\nInvigorated by the previous victory, your team becomes inspired for the first \nturn of the next battle! (50% extra damage and defense)\n";
	for (int i = 0; i < heroes.size(); i++) {
		heroes[i]->becomeInspired();
	}
}