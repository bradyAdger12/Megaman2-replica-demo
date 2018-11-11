#include "ofApp.h"  
#include "collider.h"
#include <cmath>
#include "Player.h"
shared_ptr<ofxBox2dRect> ground;  
shared_ptr<ofxBox2dCircle> obstacle;  
vector<shared_ptr<ofxBox2dBaseShape>> collider::objectList;
Player *p1;
float rot = 0;
//--------------------------------------------------------------
void ofApp::setup(){

	//world setup
	background.load("images/background.jpg");
	world.init(); 
	world.setFPS(60.0); 
	world.setGravity(0, 30);  


	//create player
	p1 = new Player();
	p1->setup(); 

	//create ball
	collider *ob2 = new collider();
	obstacle = ob2->Circle(ofGetWidth()/2, 100, 25, 2, .60, 2.0);
	soccerBall.load("images/ball.png"); 
	
	//create ground
	collider *ob3 = new collider();
	ground = ob3->Rectangle(0, ofGetHeight() - 20, ofGetWidth()*2, 20, 0 , 0, 8);  
	
}

//--------------------------------------------------------------
void ofApp::update(){ 
	 
	//keep obstacle in bounds
	if (obstacle.get()->getPosition().x + obstacle.get()->getRadius() >= ofGetWidth()) {
		obstacle.get()->setVelocity(obstacle.get()->getVelocity().x * -1, obstacle.get()->getVelocity().y);	
	}
	else if (obstacle.get()->getPosition().x - obstacle.get()->getRadius() <= 0) {
		obstacle.get()->setVelocity(obstacle.get()->getVelocity().x * -1, obstacle.get()->getVelocity().y);
	}

	//update world
	world.update();
	obstacle.get()->update();


	//update player
	p1->update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//draw world 
	world.draw();  

	//draw background
	background.draw(0, 0, ofGetWidth(), ofGetHeight());

	//draw and rotate ball 
	ofSetColor(0);
	obstacle.get()->draw();
	ofSetColor(255);
	ofPushMatrix(); 
	ofTranslate(obstacle.get()->getPosition().x, obstacle.get()->getPosition().y, 0);
	soccerBall.setAnchorPercent(0.5f, 0.5f);
	ofRotate(obstacle.get()->getRotation()); 
	soccerBall.draw(0, 0, 50, 50);	
	ofPopMatrix();

	//draw player 
	p1->draw();
	
	  
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	p1->keyPressed(key);
	if (key == 'g') {
		obstacle.get()->addForce(ofVec2f(0, obstacle.get()->getPosition().y), -5);
	}
	if (key == 'r') {
		obstacle.get()->setPosition(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
	}
    if(key == 't'){ //bypass user Key pressed so we can pass item to player from main
        if(p1->hasItem){
            p1->useItem();
        }else{
            p1->equipItem(closestUsableItem(p1->getX(), p1->getY()));
        }
    }

}

Item* ofApp::closestUsableItem(int x, int y){
    Item *closest;
    double dist;
    double closest_dist = 40;
    if(items.size() > 0){                      //if there are items
        for(int i = 0; i < items.size(); i++){ //check all
            if(!items[i]->hasParent()){        //without parent
                dist = distance(x, items[i]->getX(), y, items[i]->getY());
                if(dist < closest_dist){ //within distance
                    closest = items[i];
                    closest_dist = dist;
                }
            }
        }
    }
    return closest;
}

//Returns distance between 2 pts
double ofApp::distance(int x1,int x2,int y1,int y2){
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	p1->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
