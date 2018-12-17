

#ifndef Player_h
#define Player_h

#include "ofMain.h"
#include "ofxBox2dCircle.h"
#include "ofxBox2d.h"
#include "collider.h" 
#include "Item.h"
#include "ShootingHandler.h"
#include "Controller.h"
#include "Environment.h"
#include <vector>
#include "ShootingHandler.h"
using namespace std;
class Player {
public:

	//constructor
	Player(string portNumber, int x, int y, bool playerOne, int id);


	//var and methods
	int getX(), getY(), getRadius(), runningNum, idleNum, jumpNum, climbingNum, shootingNum, spawningNum, dyingNum, radius, size, pauseCount, getOrientation(), getHealth(), score;
	int x, y, health, id;
    int lastJumpFrame;
	b2Timer shootingTimer;
	string portName;
	ofVec2f getPosition();
	float getXVelocity(), getYVelocity(), jumpForce, blink, speedMultiplier, jumpCount;
	double speed;
	bool leftOriented, running, isFlipped, inAir, moveInAir, doubleJump, holdingItem, climbing, climbingPaused, firingPosition, randClimbPic, canClimb, ladder, dead, justDied, spawning, win, justWon;
	bool reset, canJump;
    bool cPress = false;
	bool shooting = false;
	bool jumpState;
	bool playerOne;
	void isWin();
	void setup();
	void update();
	void draw();
	void setX(float x);
	void setY(float y);
	void setVelocity(float x, float y); 
	void flipImages();
	void runningHandler(); 
	void jumpHandler();
	void spawnHandler();
	void climbingHandler();
	void shootingAnimationHandler();
	void dyingHandler();
	void orientPlayer();
    void idleHandler();
	void keyPressed(int key);
	void keyReleased(int key);
    void controllerInput(char key);
    void applyDamage(int dmg);

	//list of players
	static vector<Player*> playerList;
    
	//ladder logic 
	Environment *eLadder;  
	void getLadderSpecs(Environment *e);
	void findClosestLadder();

	//sounds
	ofSoundPlayer playerDeath;
	

    //Item vars and methods
    int x_Slot;
    int y_Slot;
	int count;
    bool hasItem;
    int getX_Slot();
    int getY_Slot();  
	double distance(int x1, int x2, int y1, int y2); 

    
    //Controller Logic
    Controller *controller;
	//shooting logic
	ShootingHandler* shootingHandler;
    
	//images
	vector<ofImage> runningAnimation;
	vector<ofImage> idleAnimation;
	vector<ofImage> jumpAnimation; 
	vector<ofImage> climbingAnimation;
	vector<ofImage> shootingAnimation;
	vector<ofImage> bulletAnimation;
	vector<ofImage> spawnAnimation;
	vector<ofImage> dyingAnimation;
	ofImage idleShoot;

	shared_ptr<ofxBox2dCircle> playerCollider; 
	collider *ob; 
	
	//timers
	b2Timer deathTimer;
	b2Timer winTimer;
    
};
#endif /* Player_h */


