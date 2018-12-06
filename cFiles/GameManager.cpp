#include "GameManager.h" 
#include "ofApp.h" 
#include "MultiPlayerManager.h"
#include "Controller.h"
#include "b2Timer.h"
vector<Controller*> Controller::controllers;
map<void*, string> ofApp::collisionObjects;  
GameManager::GameManager() {

}
void GameManager::setup()
{
	
	active = true; 
	paused = false; 
	menu = new Menu();
	menu->setup();

}

void GameManager::draw()
{
	menu->draw();
}

void GameManager::update()
{   
		Controller::controllers[0]->update();  
		controllerInput(Controller::controllers[0]->getI());
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

	if (key == 's' && !paused) {
		for (menu->selectionI = menu->selectionList.begin(); menu->selectionI != menu->selectionList.end(); menu->selectionI++) {
			if (menu->selectionI->second == true) {
				if (menu->selectionI->first == "one player") { 
					active = true;		
				}
				if (menu->selectionI->first == "two player") {
					active = true;
				}
				if (menu->selectionI->first == "controls") {
					menu->controlMenu = true;
					
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

