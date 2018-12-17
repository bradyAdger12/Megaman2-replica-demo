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
    static bool paused, active, onePlayer;
	bool usingKeyboard;
	static b2Timer beginGame, spawnTimer;
    static b2Timer* timer;
	static bool go;

    
    
private:
    vector<Controller*> controllerList;
    void controllerInput(char key);

	//countdown logic
	void drawGameCountDown(); 

	//fonts
	ofTrueTypeFont countdownFont;
	ofTrueTypeFont scoreFont;

	//score logic
	void inGameUI();
	void resetGame();

	//health
	ofColor critical;
	ofColor healthy;

	//sounds
	ofSoundPlayer victory;
	ofSoundPlayer TitleScreenMusic;
	ofSoundPlayer inGameSound;
};
