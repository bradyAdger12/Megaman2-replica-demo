#include "GameManager.h"
#include "Controller.h"   
#include "ofApp.h"
#include "Player.h"
map<void*, string> ofApp::collisionObjects; 
GameManager::GameManager() {

}
void GameManager::setup()
{
	isSelected = false;
	active = false;
	createController = true;
	createPlayerController = false;
	paused = false;
	controlMenu = false;
	index = 0;

	//images
	controllerImage.load("images/controller.png");

	//menu options
	controls.load("fonts/controlFont.ttf", 60);
	onePlayer.load("fonts/controlFont.ttf", 60);
	twoPlayer.load("fonts/controlFont.ttf", 60); 
	selectionList["one player"] = true;
	selectionList["two player"] = false; 
	selectionList["controls"] = false;
	determineSelection.push_back("one player");
	determineSelection.push_back("two player");
	determineSelection.push_back("controls");

	controlFont.load("fonts/controlFont.ttf", 60);
	 
}

void GameManager::draw()
{
	if (!active) {
		if (paused) {
			ofSetColor(255);
			controlFont.drawString("PAUSED", ofGetWidth() / 2 - 120, ofGetHeight() / 2 + 20);
		}
		else if (controlMenu) {
			controlMenuInterface();
		}
		else {
			for (selectionI = selectionList.begin(); selectionI != selectionList.end(); selectionI++) {
				if (selectionI->second == false) {
					selectionColor.set(255);
				}
				else {
					selectionColor.set(255, 0, 0);
				}
				ofSetColor(selectionColor);
				if (selectionI->first == "one player") {
					onePlayer.drawString("1 Player", ofGetWidth() / 2 - 120, ofGetHeight() / 2 - 60);
					continue;
				}
				if (selectionI->first == "two player") {
					twoPlayer.drawString("2 Player", ofGetWidth() / 2 - 120, ofGetHeight() / 2 + 20);
					continue;
				}
				if (selectionI->first == "controls") { 
					controls.drawString("Controls", ofGetWidth() / 2 - 120, ofGetHeight() / 2 + 100);
					continue;
				}

			}
		}
		 
		ofSetColor(255);
	}

	
}

void GameManager::update()
{  
	
	if (!active) {
		if (createController) { 
			controller = new Controller("COM3", 9600);
			controller->setup();
			createController = false;
		}
		controller->update(); 
		controllerInput(controller->getI());
	}
}

//b = UP, c = DOWN, p = LEFT, a = RIGHT
void GameManager::controllerInput(char key) {  
	if (key == 'd' && !isSelected) {
		index++;
		isSelected = true;
		selectionList[determineSelection[index % determineSelection.size()]] = true;
		for (int i = 0; i < determineSelection.size(); i++) {
			if (index % determineSelection.size() != i) {
				selectionList[determineSelection[i]] = false;
			}
		}
	}

	if (key == 'u' && !isSelected) {
		index--;
		isSelected = true;
		selectionList[determineSelection[index % determineSelection.size()]] = true;
		for (int i = 0; i < determineSelection.size(); i++) {
			if (index % determineSelection.size() != i) {
				selectionList[determineSelection[i]] = false;
			}
		}
	}

	if (key == 'D' || key == 'U') {
		isSelected = false;
	}

	if (key == 'c' && !paused) {
		for (selectionI = selectionList.begin(); selectionI != selectionList.end(); selectionI++) {
			if (selectionI->second == true) {
				if (selectionI->first == "one player") { 
					createPlayers(1); 
				}
				if (selectionI->first == "two player") { 
					createPlayers(2);
				}
				if (selectionI->first == "controls") {  
					controlMenu = true;	
				}
			}
		}
		 //create player(s) 
	}
	if (key == 'b' && paused) { 
		active = true;
		paused = false; 
		createPlayerController = true;
		delete(controller);
	}

	if (key == 'a' && controlMenu) { 
		controlMenu = false;
	}
}

void GameManager::createPlayers(int num) {
	delete(controller);
	if (num == 1) {
		Player *player = new Player("COM3", 50, ofGetHeight() - 100);
		player->setup();
		ofApp::collisionObjects.insert(make_pair(player, "player1"));
		playerList.push_back(player);
		active = true;
	}
	else {
		Player *player = new Player("COM3", 50, ofGetHeight() - 100);
		player->setup();
		ofApp::collisionObjects.insert(make_pair(player, "player1"));
		playerList.push_back(player);
		Player *player2 = new Player("COM5", ofGetWidth() - 100, ofGetHeight() - 100);
		player2->setup();
		ofApp::collisionObjects.insert(make_pair(player2, "player2"));
		playerList.push_back(player2);
		active = true;
	}
}


void GameManager::controlMenuInterface() {
	//draw font
	ofSetColor(255);
	controllerImage.draw(ofGetWidth() / 2 - 300, ofGetHeight() / 2 - 300, 600, 600); 
}
