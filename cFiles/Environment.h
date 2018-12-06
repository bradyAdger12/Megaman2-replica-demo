#pragma once
#include "ofMain.h"
#include "collider.h"
#include "ofxBox2dRect.h"
class Environment {
public:
	string tag;
	shared_ptr<ofxBox2dRect>  eCollider;
	vector<shared_ptr<ofxBox2dBaseShape>> environmentColliders;
	void setup();
	void draw();
	void update(); 
	int getX();
	int getY();
	int getHeight();
	int getId();
	bool ladder, canClimb;
	ofTrueTypeFont ledgeId;
	double distance(int x1, int x2, int y1, int y2);
	static vector<Environment*> ladders;
	float distanceFromPlayer;
	Environment(int x, int y, int w, int h, string tag, int id);
private:
	int x, y, width, height, id, ladderId;
	
};
