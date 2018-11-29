

#ifndef Player_h
#define Player_h

#include "ofMain.h"
#include "ofxBox2dCircle.h"
#include "ofxBox2d.h"
#include "collider.h" 
#include "Item.h"
#include "Controller.h"
#include <vector>
using namespace std;
class Player {
public:

	//constructor
	Player(string portNumber, int x, int y);

	//var and methods
	int getX(), getY(), getRadius(), speed, runningNum, idleNum,jumpNum, radius, size; 
	int x, y;
	string portName;
	ofVec2f getPosition();
	float getXVelocity(), getYVelocity(), jumpForce, blink, speedMultiplier, jumpCount;
	bool leftOriented, running, isFlipped, inAir, moveInAir, doubleJump, holdingItem;
	bool jumpState;
	void setup();
	void update();
	void draw();
	void setX(float x);
	void setY(float y);
	void setVelocity(float x, float y); 
	void flipImages();
	void runningHandler(); 
	void jumpHandler();
	void orientPlayer();
    void idleHandler();
    void controllerInput(char key);

	//list of players
	static vector<Player*> playerList;
    

    //Item vars and methods
    int x_Slot;
    int y_Slot;
	int count;
    bool hasItem;
    int getX_Slot();
    int getY_Slot(); 
	Item *item;
	//Consumable *consumable;
    void useItem();
    void throwItem();
	Item* closestUsableItem(int x, int y);
	double distance(int x1, int x2, int y1, int y2);
	Item* getItem();
    void equipItem(Item *item);
    
    //Controller Logic
    Controller *controller;
    
	vector<ofImage> runningAnimation;
	vector<ofImage> idleAnimation;
	vector<ofImage> jumpAnimation;
	vector<shared_ptr<ofxBox2dBaseShape>> playerColliders;
	shared_ptr<ofxBox2dCircle> playerCollider; 
	collider *ob; 
    
};
#endif /* Player_h */


