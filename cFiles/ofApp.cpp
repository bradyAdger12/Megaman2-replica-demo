#include "ofApp.h"  
#include "collider.h"
#include <cmath>
#include "Player.h"
#include "MultiPlayerManager.h"
shared_ptr<ofxBox2dRect> ground;
vector<shared_ptr<ofxBox2dBaseShape>> collider::objectList;
Player *p1; 
Player *p2;
Item *i1;   
//--------------------------------------------------------------
void ofApp::setup(){ 
    mpm = new MultiPlayerManager();
    
	//world setup
	background.load("images/background.jpg");
	world.init(); 
	world.enableEvents();
	world.setFPS(60.0); 
	world.setGravity(0, 30);  

	// register the listener so that we get the events
	ofAddListener(world.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(world.contactEndEvents, this, &ofApp::contactEnd);

	//create player(s)
	p1 = new Player("COM3", 50, ofGetHeight() - 100);
	p1->setup(); 
	collisionObjects.insert(make_pair(p1, "player1"));
	p2 = new Player("COM6", ofGetWidth() - 100, ofGetHeight() - 100);
	p2->setup();
	collisionObjects.insert(make_pair(p2, "player2"));

	//images for items
	soccerBall.load("images/bomb.png");
	block.load("images/goldBlock.png");


    
	//create circular item
	i1 = new Item("circle", 300, 300, 20, 0, soccerBall);
	items.push_back(i1); 
	i1->setup();
	collisionObjects.insert(make_pair(i1, "item1"));

	//create blocks
	/*
	for (int i = 0; i < 8; i++) {
		Item *it;
		it = new Item("square", ofRandom(1500), 175, 20, 0, block);
		items.push_back(it);
		it->setup();
	}*/
	 

	//create ground
	collider *ob3 = new collider();
	ground = ob3->Rectangle(0, ofGetHeight() - 20, ofGetWidth()*2, 20, 0 , 0, 8);  
	collisionObjects.insert(make_pair(ob3, "ground"));

	//load font
	controlFont.load("fonts/controlFont.ttf", 30);
	
}

//--------------------------------------------------------------
void ofApp::update(){ 

	//update world
	world.update();  

	//item update
	
	for (int i = 0; i < 1; i++) {
		items[i]->update();
	}

	//update player
	p1->update(); 
	p2->update();
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){


	//draw world 
	world.draw(); 

	//draw background
	background.draw(0, 0, ofGetWidth(), ofGetHeight());


	//draw player  
	p1->draw(); 
	p2->draw();
	

	//item draw 
	
	for (int i = 0; i < 1; i++) {
		items[i]->draw();
	}

	//draw font
	controlFont.drawString("SQUARE -> pick up/throw item", 50, 50);
	controlFont.drawString("X -> jump", 50, 90); 
	controlFont.drawString("L3 -> sprint", 50, 130);
	controlFont.drawString("L -> run", 50, 170); 
	
	  

	
}
//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {
	if (e.a != NULL && e.b != NULL) {
		// if we collide with the ground we do not
		// want to play a sound. this is how you do that
		if (e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
			string a_type;
			string b_type;

			itr = collisionObjects.find(e.a->GetBody()->GetUserData());//seach collision object address map
			if (itr == collisionObjects.end()) {

			}
			else {
				a_type = itr->second;
			}
			itr = collisionObjects.find(e.b->GetBody()->GetUserData());//seach collision object address map
			if (itr == collisionObjects.end()) {

			}
			else {
				b_type = itr->second;
			}

			std::cout << e.a->GetBody()->GetUserData() << endl;
			std::cout << e.b->GetBody()->GetUserData() << endl;

			std::cout << a_type << endl;
			std::cout << b_type << endl;

		}
	}
}
//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
	if (e.a != NULL && e.b != NULL) {
	}
}
void ofApp::keyPressed(int key) { 
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
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
