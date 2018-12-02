#include "Environment.h"
#include "ofApp.h"
//map<void*, string> ofApp::collisionObjects;
float dx, dy;
Environment::Environment(int x, int y, int w, int h, string tag, int id) {
	collider *ob = new collider();
	this->width = w;
	this->height = h;
	this->x = x;
	this->y = y;  
	this->id = id;
    eCollider = ob->Rectangle(x, y, w, h, 0, 0, 8);
} 
void Environment::setup() {

}
void Environment::update() {   
	
}
void Environment::draw() {  
		/*ofSetColor(0, 0, 0, 150);
		eCollider.get()->draw();*/
}
