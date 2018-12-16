#include "Menu.h"
#include "GameManager.h" 
Menu::Menu() {

}

void Menu::setup() {


	controlMenu = false;
	index = 0;
	isSelected = false;

	//images
	controllerImage.load("images/controller.png");

	//menu options
	controls.load("fonts/controlFont.ttf", 25);
	onePlayer.load("fonts/controlFont.ttf", 25);
	quit.load("fonts/controlFont.ttf", 40);
	enableKeyboard.load("fonts/controlFont.ttf", 25);
	twoPlayer.load("fonts/controlFont.ttf", 25);
	selectionList["one player"] = true;
	selectionList["two player"] = false;
	selectionList["controls"] = false;
	selectionList["enableKeyboard"] = false;
	selectionList["quit"] = false;
	determineSelection.push_back("one player");
	determineSelection.push_back("two player");
	determineSelection.push_back("controls");
	determineSelection.push_back("enableKeyboard");
	determineSelection.push_back("quit");
	controlFont.load("fonts/controlFont.ttf", 25);
}

void Menu::update() {
}

void Menu::draw() {

	if (!GameManager::active) {
		if (GameManager::paused) {
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
					onePlayer.drawString("1 Player", ofGetWidth() / 2 - 115, ofGetHeight() / 2 + 10);
					continue;
				}
				if (selectionI->first == "two player") {
					twoPlayer.drawString("2 Player", ofGetWidth() / 2 - 115, ofGetHeight() / 2 + 45);
					continue;
				}
				if (selectionI->first == "controls") {
					controls.drawString("Controls", ofGetWidth() / 2 - 115, ofGetHeight() / 2 + 80);
					continue;
				}
				if (selectionI->first == "enableKeyboard") {
					enableKeyboard.drawString("Enable Keyboard", ofGetWidth() / 2 - 185, ofGetHeight() / 2 + 115);
					continue;
				}
				if (selectionI->first == "quit") {
				    quit.drawString("Quit", ofGetWidth() / 2 - 90, ofGetHeight() / 2 + 210);
					continue;
				}

			}
		}

		ofSetColor(255);
	}


}

void Menu::controlMenuInterface() {
	//draw font
	ofSetColor(255);
	controllerImage.draw(ofGetWidth() / 2 - 300, ofGetHeight() / 2 - 300, 600, 600);
}
