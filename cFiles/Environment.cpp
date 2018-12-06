#include "Environment.h"
#include "ofApp.h"   
vector<Environment*> Environment::ladders;
Environment::Environment(int x, int y, int w, int h, string tag, int id) {
	collider *ob = new collider();
	this->width = w;
	this->height = h;
	this->x = x;
	this->y = y;  
	this->id = id; 
	this->tag = tag;
    eCollider = ob->Rectangle(x, y, w, h, 0, 0, 8);
	ledgeId.load("fonts/controlFont.ttf", 10);
	ofApp::collisionObjects.insert(make_pair(this, tag));
	if (tag == "ladder") {
		eCollider.get()->body->SetActive(false);
		ladders.push_back(this);
	}
} 
void Environment::setup() {
	ladder = false;
	canClimb = false; 
	distanceFromPlayer = 0;
}
void Environment::update() {
	for (int i = 0; i < MultiPlayerManager::players.size(); i++) {
		if (tag == "ladder") {
			if (MultiPlayerManager::players[i]->getY() >= (y - height/2) + MultiPlayerManager::players[i]->getRadius() && MultiPlayerManager::players[i]->getY() <= y + height) {
				canClimb = true;
			}
			else {
				canClimb = false;
			}
			if (MultiPlayerManager::players[i]->getX() > x - width && MultiPlayerManager::players[i]->getX() < x + width) { 
				
				ladder = true;
			}
			else {
				ladder = false;
			}
			 
		}
	}	
}
	

	
void Environment::draw() {  
		ofSetColor(0, 0, 0, 150);
		eCollider.get()->draw();
		ofSetColor(255, 0, 0);
		ledgeId.drawString(ofToString(id), x, y + 5);

}

double Environment::distance(int x1, int x2, int y1, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int Environment::getX() {
	return x;
}

int Environment::getY() {
	return y;
}

int Environment::getHeight() {
	return height;
}

int Environment::getId() {
	return id;
}
