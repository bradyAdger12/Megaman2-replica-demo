#include "ofApp.h"  
#include "collider.h"
#include <cmath>
#include "Player.h"
shared_ptr<ofxBox2dRect> ground;
vector<shared_ptr<ofxBox2dBaseShape>> collider::objectList;
Player *p1;
Item *i1;
Item *i2;
Item *i3;

float rot = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    //serial.listDevices();
    //serial.setup("cu.usbmodemFD131", 9600);
    
	//world setup
	background.load("images/background.jpg");
	world.init();
    world.enableEvents();
    world.setFPS(60.0);
	world.setGravity(0, 30);  

    // register the listener so that we get the events
    ofAddListener(world.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(world.contactEndEvents, this, &ofApp::contactEnd);
    
    
	//create player
	p1 = new Player();
	p1->setup(); 
    collisionObjects.insert(make_pair(p1, "player1"));

    
	//create circular item
	soccerBall.load("images/ball.png");
	i1 = new Item("circle", 300, 300, 20, 0, soccerBall);
	items.push_back(i1);
	i1->setup();
    collisionObjects.insert(make_pair(i1, "item1"));

    
	//create square item
	block.load("images/goldBlock.png");
	i2 = new Item("square", 700, 150, 20, 0, block);
	items.push_back(i2);
	i2->setup();
    collisionObjects.insert(make_pair(i2, "item2"));

    
	//create another square
	block2.load("images/goldBlock.png");
	i3 = new Item("square", 950, 175, 20, 0, block);
	items.push_back(i3);
	i3->setup();
    collisionObjects.insert(make_pair(i3, "item3"));

	
	//create ground
	collider *ob3 = new collider();
	ground = ob3->Rectangle(0, ofGetHeight() - 20, ofGetWidth()*2, 20, 0 , 0, 8);  

	//load font
	controlFont.load("fonts/controlFont.ttf", 30);
	
}

//--------------------------------------------------------------
void ofApp::update(){ 

	//update world
	world.update(); 

	//update player
	p1->update();
	
	//item update
	for (int i = 0; i < items.size(); i++) {
		items[i]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	//draw world 
	world.draw();  

	//draw background
	background.draw(0, 0, ofGetWidth(), ofGetHeight());

	//item draw
	for (int i = 0; i < items.size(); i++) {
		items[i]->draw();
	}

	//draw player 
	p1->draw();

	//draw font
	controlFont.drawString("D -> right", 50, 50);
	controlFont.drawString("A -> left", 50, 90);
	controlFont.drawString("Space -> jump", 50, 130);
	controlFont.drawString("K -> sprint", 50, 170);
	controlFont.drawString("E -> pick up/throw item (Hold to throw further)", 50, 210);
	
	  
	
}
//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        // if we collide with the ground we do not
        // want to play a sound. this is how you do that
        if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
            string a_type;
            string b_type;
            
            itr =collisionObjects.find(e.a->GetBody()->GetUserData());//seach collision object address map
            if(itr == collisionObjects.end()){
                
            }else{
               a_type = itr->second;
            }
            itr =collisionObjects.find(e.b->GetBody()->GetUserData());//seach collision object address map
            if(itr == collisionObjects.end()){
                
            }else{
                b_type = itr->second;
            }
         
            std::cout << e.a->GetBody()->GetUserData() << endl;
            std::cout << e.b->GetBody()->GetUserData() << endl;
            
            std::cout<<a_type<<endl;
            std::cout<<b_type<<endl;

        }
    }
}
//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
    }
}





//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	p1->keyPressed(key);
    if(key == 'e'){ //bypass user Key pressed so we can pass item to player from main
        if(p1->hasItem){  
			if (p1->getItem()->style == 0) { 
				p1->getItem()->tossForce *= p1->getItem()->multiplier;
			}
			else {
				p1->useItem();
			}
        }else{
            p1->equipItem(closestUsableItem(p1->getX(), p1->getY()));
        }
    }
}

Item* ofApp::closestUsableItem(int x, int y){
    Item *closest;
    double dist;
    double closest_dist = 120;
	if (items.size() > 0) {      //if there are items  
		for (int i = 0; i < items.size(); i++) { //check all
			if (!items[i]->hasParent()) {        //without parent
				dist = distance(x, items[i]->getX(), y, items[i]->getY());
				if (dist < closest_dist) { //within distance
					return items[i]; 
				}  
			}
		}
	}
	return NULL;
}

//Returns distance between 2 pts
double ofApp::distance(int x1,int x2,int y1,int y2){
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	p1->keyReleased(key);
	if (key == 'e') { //bypass user Key pressed so we can pass item to player from main
		if (p1->hasItem) {
			p1->getItem()->count++;
			if (p1->getItem()->style == 0) {
				if (p1->getItem()->count == 2) {
					cout << "Thow Force: " << p1->getItem()->tossForce << endl;
					p1->throwItem();
				}
			}
		}
	}
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
