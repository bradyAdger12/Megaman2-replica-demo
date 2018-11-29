#pragma once
#include "ofMain.h"
#include "Controller.h"
#include "b2Timer.h"
#include "Player.h"
#include "Menu.h"
class GameManager {
public:
	GameManager(); 
	void setup();
	void draw();
	void update();
	Controller *controller; 
	static bool createController, paused, active, createPlayerController;
	static vector <Player*> playerList;
	Menu *menu;


private:   
	vector<Controller*> controllerList; 
	void createPlayers(int num);
	void controllerInput(char key); 
};
