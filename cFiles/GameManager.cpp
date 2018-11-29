#include "GameManager.h" 
#include "ofApp.h" 
map<void*, string> ofApp::collisionObjects; 
GameManager::GameManager() {

}
void GameManager::setup()
{
	
	active = false;
	createController = true;
	createPlayerController = false;
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

	if (key == 'c' && !paused) {
		for (menu->selectionI = menu->selectionList.begin(); menu->selectionI != menu->selectionList.end(); menu->selectionI++) {
			if (menu->selectionI->second == true) {
				if (menu->selectionI->first == "one player") {
//                    createPlayers(1);
				}
				if (menu->selectionI->first == "two player") {
//                    createPlayers(2);
				}
				if (menu->selectionI->first == "controls") {
					menu->controlMenu = true;
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

	if (key == 'a' && menu->controlMenu) {
		menu->controlMenu = false;
	}
}

//void GameManager::createPlayers(int num) {
//    delete(controller);
//    if (num == 1) {
//        Player *player = new Player("COM3", 50, ofGetHeight() - 100);
//        player->setup();
//        ofApp::collisionObjects.insert(make_pair(player, "player1"));
//        playerList.push_back(player);
//        active = true;
//    }
//    else {
//        Player *player = new Player("COM3", 50, ofGetHeight() - 100);
//        player->setup();
//        ofApp::collisionObjects.insert(make_pair(player, "player1"));
//        playerList.push_back(player);
//        Player *player2 = new Player("COM5", ofGetWidth() - 100, ofGetHeight() - 100);
//        player2->setup();
//        ofApp::collisionObjects.insert(make_pair(player2, "player2"));
//        playerList.push_back(player2);
//        active = true;
//    }
//}
