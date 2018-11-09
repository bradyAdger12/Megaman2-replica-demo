#include "object.h"
#include "ofApp.h"
ofxBox2d ofApp::world;

object::object() {

} 

shared_ptr<ofxBox2dCircle> object::Circle(int x, int y, float radius, float density, float bounce, float friction) {
	shared_ptr<ofxBox2dCircle> circle;
	circle = std::make_shared<ofxBox2dCircle>();
	circle.get()->setPhysics(density, bounce , friction);
	circle.get()->setup(ofApp::world.getWorld(), x, y, radius);
	objectList.push_back(circle);
	return circle;
}

//rectangle.get()->setup(world.getWorld(), 0, ofGetHeight()-20, ofGetWidth() * 2, 20);
shared_ptr<ofxBox2dRect> object::Rectangle(int x, int y, int w, int h, float density, float bounce, float friction) {
	shared_ptr<ofxBox2dRect> rect;
	rect = std::make_shared<ofxBox2dRect>(); 
	rect.get()->setPhysics(density, bounce, friction);
	rect.get()->setup(ofApp::world.getWorld(), x, y, w, h);
	objectList.push_back(rect);
	return rect;
}