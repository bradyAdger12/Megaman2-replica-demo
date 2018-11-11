#pragma once
#include "ofMain.h"
<<<<<<< HEAD
#include "ofxBox2dCircle.h"
=======
#include "ofxBox2dCircle.h"
>>>>>>> dev
#include "ofxBox2d.h"
#include "collider.h"
#include <vector>

class player {
public: 
	int getX(), getY(), speed, runningNum, idleNum,jumpNum, radius, size; 
	float getXVelocity(), getYVelocity(), jumpForce, blink, lastY, y; 
	void setup();
	void update();
	void draw();
	void setX(float x);
	void setY(float y);
	void setVelocity(float x, float y);
	void keyPressed(int key);
	void keyReleased(int key);
	void flipImages();
	void runningHandler(); 
	void jumpHandler();
	void orientPlayer();
	void idleHandler();
	vector<ofImage> runningAnimation;
	vector<ofImage> idleAnimation;
	vector<ofImage> jumpAnimation;
	vector<shared_ptr<ofxBox2dBaseShape>> playerColliders;
	shared_ptr<ofxBox2dCircle> playerCollider;
	collider *ob;
	bool leftOriented, running, isFlipped, inAir, moveInAir; 
	bool jumpState;
};
