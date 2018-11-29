#pragma once
#include "ofMain.h"
#include "Controller.h"
#include "b2Timer.h"
#include "Player.h"
class GameManager {
public:
	GameManager();
	static bool active;
	void setup();
	void draw();
	void update();
	Controller *controller; 
	static bool createController, paused, createPlayerController;
	
	static vector <Player*> playerList;

private:
	bool isSelected, controlMenu;
	int index;
	ofColor selectionColor;
	ofImage controllerImage;
	ofTrueTypeFont controls;
	ofTrueTypeFont onePlayer;
	ofTrueTypeFont twoPlayer;
	ofTrueTypeFont controlFont;
	map<string, bool> selectionList;
	vector<string> determineSelection;
	vector<Controller*> controllerList;
	map<string, bool>::iterator selectionI;
	void createPlayers(int num);
	void controllerInput(char key);
	void controlMenuInterface();
};
