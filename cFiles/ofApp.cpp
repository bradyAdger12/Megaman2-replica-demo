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
int cameraY, yChange;
string s;
vector<Environment*> ofApp::eList;

//--------------------------------------------------------------
void ofApp::setup(){ 

    
	//world setup  
	background.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	background.load("images/bombManStage2.png"); 
	menuBackground.load("images/titleBackground.jpg"); 
	world.init(); 
	world.enableEvents();
	world.setFPS(30.0); 
	world.setGravity(0, 7);  

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

	//create Environment Colliders
	input.open(ofToDataPath("environment/eData.txt").c_str());
	while (input >> x >> y >> w >> h >> s >> id) { 
		cout << "(" << x << "," << y << ")" << " Width: " << w << "  Height: " << h << "  Tag: " << s << "  ID: " << id << endl;
 		Environment *e;
		x = x + (w/2);
		e = new Environment(x, y+9, w, h, s, id);
		eList.push_back(e);
		e->setup();
		collisionObjects.insert(make_pair(e, s));
	}

	//setup camera  
	camera.setVFlip(true);
	camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 90, MultiPlayerManager::players[0]->getY() - 50, 180));//
	cameraY = camera.getPosition().y;
	
}

//--------------------------------------------------------------
void ofApp::update(){   
	
	camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 90, cameraY, 180)); 

	//camera.setPosition(200, 1000, 500); 
	//game UI
	gm->update();

	if (!gm->active && !gm->paused) {
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
		  
		//update environment collider info
		for (int i = 0; i < eList.size(); i++) {
			eList[i]->update();
		}	 
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
		
		if (gm->paused) {
			color.set(180);
		}
		else {
			color.set(255);
		}
		//draw world 
		world.draw();

        //player management
        mpm->draw();
        
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
		if (e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle || e.b->GetType() == b2Shape::e_circle && e.a->GetType() == b2Shape::e_polygon) {
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
