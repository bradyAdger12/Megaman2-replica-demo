#include "ofApp.h"  
#include "object.h"
#include <cmath>
#include "player.h"
shared_ptr<ofxBox2dRect> ground;  
shared_ptr<ofxBox2dCircle> obstacle;  
vector<shared_ptr<ofxBox2dBaseShape>> object::objectList;
player *p1;

//--------------------------------------------------------------
void ofApp::setup(){

	//world setup
	background.load("images/background.jpg");
	world.init(); 
	world.setFPS(60.0); 
	world.setGravity(0, 15);  

	//create player
	p1 = new player();
	p1->setup(); 

	//create ball
	object *ob2 = new object();
	obstacle = ob2->Circle(50, 100, 15, 2, .60, 2.0);
	soccerBall.load("images/ball.png");

	object *ob3 = new object();
	ground = ob3->Rectangle(0, ofGetHeight() - 20, ofGetWidth()*2, 20, 0 , 0, 0);  
	
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


	//falling obstacle
	obstacle.get()->draw();
	soccerBall.draw(obstacle.get()->getPosition().x - 15, obstacle.get()->getPosition().y - 15, 30, 30);

	//draw player 
	p1->draw();
	
	  
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ 
	p1->keyPressed(key);
	 
	if (key == 'g') {
		obstacle.get()->addImpulseForce(ofVec2f(obstacle.get()->getPosition() + 10), ofVec2f(0, -5));
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
