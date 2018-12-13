#include "GameManager.h" 
#include "ofApp.h" 
#include "MultiPlayerManager.h"
#include "Controller.h"
#include "b2Timer.h"
vector<Controller*> Controller::controllers;
map<void*, string> ofApp::collisionObjects;  
b2Timer GameManager::beginGame; 
bool GameManager::go;
bool GameManager::active;
bool GameManager::paused;
bool GameManager::onePlayer;
b2Timer GameManager::spawnTimer;
Menu* menu;
GameManager::GameManager() {

}
void GameManager::setup()
{
	
	active = false; 
	paused = false; 
	usingKeyboard = false;
	go = false; 
	onePlayer = false;

	//fonts
	countdownFont.load("fonts/controlFont.ttf", 300);
	scoreFont.load("fonts/Bit-Lazy.ttf", 25);

	//menu setup
	menu = new Menu();
	menu->setup(); 

}

void GameManager::draw()
{
	if (!active && !menu->controlMenu && !paused) {
		if (usingKeyboard) {
			menu->controlFont.drawString("enabled", ofGetWidth() / 2 - 120, ofGetHeight() / 2 + 260);
			MultiPlayerManager::keyboard = true;
		}
		if (!usingKeyboard) {
			menu->controlFont.drawString("disabled", ofGetWidth() / 2 - 120, ofGetHeight() / 2 + 260);
			MultiPlayerManager::keyboard = false;
		}
	} 

	ofSetColor(255);

	//counter to begin game
	drawGameCountDown();
	
	//draw menu
	menu->draw();

	//draw user interface
	inGameUI();
}

void GameManager::update()
{   
	if (!active && !MultiPlayerManager::keyboard) {
		Controller::controllers[0]->update();
		controllerInput(Controller::controllers[0]->getI());
	}
}

//b = UP, c = DOWN, p = LEFT, a = RIGHT
void GameManager::controllerInput(char key) {  
	if (key == 'd' && !menu->isSelected) {
		menu->index++;
		menu->isSelected = true;
		menu->selectionList[menu->determineSelection[menu->index % menu->determineSelection.size()]] = true;
		for (int i = 0; i < menu->determineSelection.size(); i++) {
			if (menu->index % menu->determineSelection.size() != i) {
				menu->selectionList[menu->determineSelection[i]] = false;
			}
		}
	}

	if (key == 'u' && !menu->isSelected) {
		menu->index--;
		menu->isSelected = true;
		menu->selectionList[menu->determineSelection[menu->index % menu->determineSelection.size()]] = true;
		for (int i = 0; i < menu->determineSelection.size(); i++) {
			if (menu->index % menu->determineSelection.size() != i) {
				menu->selectionList[menu->determineSelection[i]] = false;
			}
		}
	}

	if (key == 'D' || key == 'U') {
		menu->isSelected = false;
	}

	if (key == 'c' && !paused && !active) {
		for (menu->selectionI = menu->selectionList.begin(); menu->selectionI != menu->selectionList.end(); menu->selectionI++) {
			if (menu->selectionI->second == true) {
				if (menu->selectionI->first == "one player") { 
					beginGame.Reset();
					onePlayer = true;
					active = true;
					spawnTimer.Reset();
					
				}
				if (menu->selectionI->first == "two player") {
					if (MultiPlayerManager::players.size() > 1) {
						beginGame.Reset();
						active = true;
					}		
				}
				if (menu->selectionI->first == "controls") {
					menu->controlMenu = true;		
				}
				if (menu->selectionI->first == "enableKeyboard") { 
					usingKeyboard = true;
				}
			}
		}
		 //create player(s) 
	}
	if (key == 'a' && paused) {
		active = true;
		paused = false;  
	}

	if (key == 'a' && menu->controlMenu) {
		menu->controlMenu = false;
	}
} 

void GameManager::drawGameCountDown() {
	if (beginGame.GetMilliseconds() <= 4000) {  
			if (3 - ((int(beginGame.GetMilliseconds())) / 1000) == 0) {
				countdownFont.drawString("GO!", (ofGetWidth() / 2) - 300, ofGetHeight() / 2); 
				go = true;
			}
			else {
				countdownFont.drawString(ofToString(3 - ((int(beginGame.GetMilliseconds())) / 1000)), (ofGetWidth() / 2) - 300, ofGetHeight() / 2);
			}
		} 
}

void GameManager::inGameUI() { 
	if (active) {
		if (MultiPlayerManager::players.size() > 1) {
			ofSetColor(255);
			scoreFont.drawString("P1  SCORE:   " + ofToString(MultiPlayerManager::players[0]->score), 100, 100);
			scoreFont.drawString("P2  SCORE:   " + ofToString(MultiPlayerManager::players[1]->score), ofGetWidth() - 325, 100);
		}
		else {
			scoreFont.drawString("SCORE:   " + ofToString(MultiPlayerManager::players[0]->score), ofGetWidth() / 2 - 25, 100);
			ofSetColor(0, 255, 0);
			ofSetLineWidth(15);
			ofDrawLine(ofVec2f(50, 50), ofVec2f(50*2 + MultiPlayerManager::players[0]->health*2, 50));
		}
	}
	ofSetColor(255);
}
 


