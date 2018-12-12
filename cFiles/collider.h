#pragma once
#include "ofxBox2dCircle.h"
#include "ofxBox2dRect.h"

class collider {
public:
	collider(); 
	string name;
	shared_ptr<ofxBox2dCircle> Circle(int x, int y, float radius, float density, float bounce, float friction);
    shared_ptr<ofxBox2dCircle> Circle(double x, double y, float radius, float density, float bounce, float friction);
	shared_ptr<ofxBox2dRect> Rectangle(int x, int y, int w, int h, float density, float bounce, float friction);
	static vector<shared_ptr<ofxBox2dBaseShape>> objectList; 
private:
};
