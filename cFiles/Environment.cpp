#include "Environment.h"
#include "ofApp.h"  
bool Environment::ladder;
Environment::Environment(int x, int y, int w, int h, string tag, int id) {
	collider *ob = new collider();
	this->width = w;
	this->height = h;
	this->x = x;
	this->y = y;  
	this->id = id;
	ladder = false;
	this->tag = tag;
    eCollider = ob->Rectangle(x, y, w, h, 0, 0, 8);
	ofApp::collisionObjects.insert(make_pair(this, tag));
	if (tag == "ladder") {
		eCollider.get()->body->SetActive(false);
	}
} 
void Environment::setup() {

}
void Environment::update() {  
	for (int i = 0; i < MultiPlayerManager::players.size(); i++) {
		if (tag == "ladder") {
			if (distance(MultiPlayerManager::players[0]->getX(), x, MultiPlayerManager::players[0]->getY(), y) <= width) {
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
