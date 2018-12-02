#pragma once
#include "ofMain.h"
#include "collider.h"
#include "ofxBox2dRect.h"
class Environment {
public:
	int tag;
	shared_ptr<ofxBox2dRect>  eCollider;
	vector<shared_ptr<ofxBox2dBaseShape>> environmentColliders;
	void setup();
	void draw();
	void update();
	Environment(int x, int y, int w, int h, string tag, int id);
private:
	int x, y, width, height, id;
	
};
