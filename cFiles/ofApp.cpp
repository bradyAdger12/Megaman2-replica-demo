#include "ofApp.h"  
#include "collider.h"
#include <cmath>
#include "Player.h" 
#include "MultiPlayerManager.h"
#include "GameManager.h"  
shared_ptr<ofxBox2dRect> ground;
vector<shared_ptr<ofxBox2dBaseShape>> collider::objectList;
//vector<Player*> GameManager::playerList;
//Player *p1;
//Player *p2;
Item *i1;
ofColor color;
GameManager *gm;
int x, y, w, h, id;
string s;
//--------------------------------------------------------------
void ofApp::setup(){ 

	//world setup
    //ofLoadImage(p, "images/bombManStage.png");
//    background.allocate(4355, 1187, OF_IMAGE_UNDEFINED);
    background.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
	background.load("images/bombManStage.png");
	menuBackground.load("images/titleBackground.jpg");
	world.init();
	world.enableEvents();
	world.setFPS(60.0);
	world.setGravity(0, 30);  

	//sounds
	TitleScreenMusic.load("sounds/TitleScreen.mp3");
	TitleScreenMusic.setLoop(true);
	inGameSound.load("sounds/inGame.mp3");
	inGameSound.setLoop(true);

	//character Management
	mpm = new MultiPlayerManager();
	mpm->setup();
    
	//GameManager
	gm = new GameManager();
	gm->setup();

	//color
	color.set(255);

	// register the listener so that we get the events
	ofAddListener(world.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(world.contactEndEvents, this, &ofApp::contactEnd);

	//images for items
	soccerBall.load("images/bomb.png");
	block.load("images/goldBlock.png");

	////create circular item
	//i1 = new Item("circle", 300, 300, 10, 0, soccerBall);
	//items.push_back(i1); 
	//i1->setup();
	//collisionObjects.insert(make_pair(i1, "item1"));

	//create Environment Colliders
	input.open(ofToDataPath("environment/eData.txt").c_str());
	while (input >> x >> y >> w >> h >> s >> id) { 
		cout << "(" << x << "," << y << ")" << " Width: " << w << "  Height: " << h << "  Tag: " << s << "  ID: " << id << endl;
 		Environment *e;/*
		if (x + w > ofGetWidth()/2 || x > ofGetWidth()/2) {
			e = new Environment(x+w/2, y + 25, w, h, s, id);
		}
		else {*/
		x = x + (w/2);
		e = new Environment(x, y+9, w, h, s, id);
		eList.push_back(e);
		e->setup();
		collisionObjects.insert(make_pair(e, "ledge"));
	}

	//setup camera 
	camera.setVFlip(true); 
}

//--------------------------------------------------------------
void ofApp::update(){
	camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 155, MultiPlayerManager::players[0]->getY() - 70, 180));
	//camera.setPosition(100, 1000, 400);
	//game UI
	gm->update();

	if (!gm->active) {
		if (!TitleScreenMusic.isPlaying()) {
			TitleScreenMusic.play(); 
		}
	}

	if (gm->active) {
		 

		//in game sound
		if (!inGameSound.isPlaying()) {
			inGameSound.play();
		}

		//character management
		mpm->update();

		//stop title music
		if (TitleScreenMusic.isPlaying()) {
			TitleScreenMusic.stop();
		}
		//update world
		world.update();
		 
		//item update
		/*for (int i = 0; i < 1; i++) {
			items[i]->update();
		}*/
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//title background 
	menuBackground.draw(0, 0, ofGetWidth(), ofGetHeight());
	camera.begin();

	if (gm->active || gm->paused) {

		//draw in game background
		ofSetColor(color);
		background.draw(0, 0, 4355, 1187);
		
		//player management
		mpm->draw();
		
		if (gm->paused) {
			color.set(180);
		}
		else {
			color.set(255);
		}
		//draw world 
		world.draw();

		//item draw
		/*for (int i = 0; i < 1; i++) {
			items[i]->draw();
		}*/

		for (int i = 0; i < eList.size(); i++) {
			eList[i]->draw();
		}
		
	}

	camera.end();
	//draw game UI
	gm->draw();
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
