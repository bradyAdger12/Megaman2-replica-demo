#include "Environment.h"
#include "ofApp.h"   
vector<Environment*> Environment::ladders;
vector<Environment*> Environment::spikes;
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
	eCollider->setData(this);
	ofApp::collisionObjects.insert(make_pair(this, tag));
	if (tag == "ladder") {
		eCollider.get()->body->SetActive(false);
		ladders.push_back(this);
	}
	if (tag == "spikes") { 
		spikes.push_back(this);
	}
} 
void Environment::setup() {  

}
void Environment::update() { 
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

int Environment::getWidth() {
	return width;
}

int Environment::getId() {
	return id;
}

string Environment::getTag() {
	return tag;
}
