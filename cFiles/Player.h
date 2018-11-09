#pragma once
#include "ofMain.h"
#include "ofxBox2dCircle.h"
#include "ofxBox2d.h"
#include "object.h"
#include <vector>

class player {
public:
	int getX(), getY(), speed, runningFrameNum; 
	float getXVelocity(), getYVelocity(), jump; 
	void setup();
	void update();
	void draw();
	void setVelocity(float x, float y);
	void keyPressed(int key);
	void keyReleased(int key);
	void flipImages();
	void runningHandler();
	ofImage idleSkin;
	vector<ofImage> runningAnimation;
	shared_ptr<ofxBox2dCircle> playerCollider;
	object *ob;
	bool leftOriented, running; 
};
