#include "Environment.h"
#include "ofApp.h"   
bool Environment::ladder;
bool Environment::canClimb;
Environment::Environment(int x, int y, int w, int h, string tag, int id) {
	collider *ob = new collider();
	this->width = w;
	this->height = h;
	this->x = x;
	this->y = y;  
	this->id = id; 
	this->tag = tag;
    eCollider = ob->Rectangle(x, y, w, h, 0, 0, 8);
	ofApp::collisionObjects.insert(make_pair(this, tag));
	if (tag == "ladder") {
		eCollider.get()->body->SetActive(false);
	}
} 
void Environment::setup() {
	ladder = false;
	canClimb = false;
}
void Environment::update() {  
	for (int i = 0; i < MultiPlayerManager::players.size(); i++) {
		if (tag == "ladder") {
			if (distance(MultiPlayerManager::players[i]->getX(), x, MultiPlayerManager::players[i]->getY(), y + height) <= height + (MultiPlayerManager::players[i]->getRadius() * 2)) {
				canClimb = true;
			}
			else {
				canClimb = false;
			}
			if (MultiPlayerManager::players[i]->getX() + MultiPlayerManager::players[i]->getRadius() > x && MultiPlayerManager::players[i]->getX() + MultiPlayerManager::players[i]->getRadius() < x + width) {
				ladder = true; 		
			}  
			else {
				ladder = false;
			}
		}
	} 
}
void Environment::draw() {  /*
		ofSetColor(0, 0, 0, 150);
		eCollider.get()->draw();*/
}

double Environment::distance(int x1, int x2, int y1, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
