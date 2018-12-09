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
	controls.load("fonts/controlFont.ttf", 60);
	onePlayer.load("fonts/controlFont.ttf", 60);
	enableKeyboard.load("fonts/controlFont.ttf", 60);
	twoPlayer.load("fonts/controlFont.ttf", 60);
	selectionList["one player"] = true;
	selectionList["two player"] = false;
	selectionList["controls"] = false;
	selectionList["enableKeyboard"] = false;
	determineSelection.push_back("one player");
	determineSelection.push_back("two player");
	determineSelection.push_back("controls");
	determineSelection.push_back("enableKeyboard");
	controlFont.load("fonts/controlFont.ttf", 60);
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
				if (selectionI->first == "enableKeyboard") {
					enableKeyboard.drawString("Enable Keyboard", ofGetWidth() / 2 - 300, ofGetHeight() / 2 + 180);
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