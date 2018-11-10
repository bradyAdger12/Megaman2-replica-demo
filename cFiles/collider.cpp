#include "collider.h"
#include "ofApp.h"
ofxBox2d ofApp::world;

collider::collider() {

} 

shared_ptr<ofxBox2dCircle> collider::Circle(int x, int y, float radius, float density, float bounce, float friction) {
	shared_ptr<ofxBox2dCircle> circle;
	circle = std::make_shared<ofxBox2dCircle>();
	circle.get()->setPhysics(density, bounce , friction);
	circle.get()->setup(ofApp::world.getWorld(), x, y, radius);
	objectList.push_back(circle);
	return circle;
}


shared_ptr<ofxBox2dRect> collider::Rectangle(int x, int y, int w, int h, float density, float bounce, float friction) {
	shared_ptr<ofxBox2dRect> rect;
	rect = std::make_shared<ofxBox2dRect>(); 
	rect.get()->setPhysics(density, bounce, friction);
	rect.get()->setup(ofApp::world.getWorld(), x, y, w, h);
	objectList.push_back(rect);
	return rect;
}