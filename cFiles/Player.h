#pragma once
#include "ofMain.h"
#include "ofxBox2dCircle.h"
#include "ofxBox2d.h"
#include "collider.h"
#include <vector>

class player {
public:
	int getX(), getY(), speed, runningNum, idleNum, radius, size; 
	float getXVelocity(), getYVelocity(), jumpForce, blink; 
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
	void idleHandler();
	vector<ofImage> runningAnimation;
	vector<ofImage> idleAnimation;
	vector<shared_ptr<ofxBox2dBaseShape>> playerColliders;
	shared_ptr<ofxBox2dCircle> playerCollider;
	collider *ob;
	bool leftOriented, running, isFlipped; 
};
