#include "ofApp.h"  
#include "collider.h"
#include <cmath>
#include "Player.h"
shared_ptr<ofxBox2dRect> ground;   
vector<shared_ptr<ofxBox2dBaseShape>> collider::objectList;
Player *p1;
Item *i1;
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

	//create item
	soccerBall.load("images/ball.png");
	i1 = new Item("circle", 300, 300, 25, 0, soccerBall);
	items.push_back(i1);
	i1->setup();
	
	//create ground
	collider *ob3 = new collider();
	ground = ob3->Rectangle(0, ofGetHeight() - 20, ofGetWidth()*2, 20, 0 , 0, 8);  
	
}

//--------------------------------------------------------------
void ofApp::update(){ 

	//update world
	world.update(); 

	//update player
	p1->update();
	
	//item update
	i1->update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//draw world 
	world.draw();  

	//draw background
	background.draw(0, 0, ofGetWidth(), ofGetHeight());

	//item draw 
	i1->draw();

	//draw player 
	p1->draw();
	
	  
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	p1->keyPressed(key);
    if(key == 't'){ //bypass user Key pressed so we can pass item to player from main
        if(p1->hasItem){  
			if (p1->getItem()->style == 0) {
				p1->throwItem();
			}
			else {
				p1->useItem();
			}
        }else{
            p1->equipItem(closestUsableItem(p1->getX(), p1->getY()));
			cout << "item equipped" << endl;
        }
    }

}

Item* ofApp::closestUsableItem(int x, int y){
    Item *closest;
    double dist;
    double closest_dist = 120;
    if(items.size() > 0){      //if there are items 
        for(int i = 0; i < items.size(); i++){ //check all
            if(!items[i]->hasParent()){        //without parent
                dist = distance(x, items[i]->getX(), y, items[i]->getY());
                if(dist < closest_dist){ //within distance 
                    closest = items[i];
                    closest_dist = dist;
                }
				else {
					closest = NULL;
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
