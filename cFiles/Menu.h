#pragma once 
#include "ofMain.h"
#include "Controller.h" 
#include "Player.h"
class Menu {
public:
	Menu(); 
	void setup();
	void draw();
	void update();  
	bool isSelected, controlMenu;
	int index;
	ofColor selectionColor;
	ofImage controllerImage;
	ofTrueTypeFont controls;
	ofTrueTypeFont onePlayer;
	ofTrueTypeFont quit;
	ofTrueTypeFont enableKeyboard;
	ofTrueTypeFont twoPlayer;
	ofTrueTypeFont controlFont;
	map<string, bool> selectionList;
	vector<string> determineSelection; 
	map<string, bool>::iterator selectionI;  
	void controlMenuInterface();
};

