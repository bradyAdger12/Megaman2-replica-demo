#include "ofApp.h"  
#include "collider.h"
#include <cmath>
#include "player.h"
shared_ptr<ofxBox2dRect> ground;  
shared_ptr<ofxBox2dCircle> obstacle;  
vector<shared_ptr<ofxBox2dBaseShape>> collider::objectList;
player *p1;
float rot = 0;
//--------------------------------------------------------------
void ofApp::setup(){

	//world setup
	background.load("images/background.jpg");
	world.init(); 
	world.setFPS(60.0); 
	world.setGravity(0, 30);  


	//create player
	p1 = new player();
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
	if (obstacle.get()->getPosition().x - obstacle.get()->getRadius() <= 0) {
		obstacle.get()->setVelocity(obstacle.get()->getVelocity().x * -1, obstacle.get()->getVelocity().y);
	}

	//update world
	world.update();
	obstacle.get()->update();
	ground.get()->enableGravity(true);


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
