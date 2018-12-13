#include "ofApp.h"  
#include "collider.h"
#include <cmath>
#include "Player.h" 
#include "MultiPlayerManager.h"
#include "GameManager.h"
#include "Enemy.h"
shared_ptr<ofxBox2dRect> ground;
vector<shared_ptr<ofxBox2dBaseShape>> collider::objectList;
//vector<Player*> GameManager::playerList;
//Player *p1;
//Player *p2;
Enemy *test_enemy;
ofColor color;
GameManager *gm;
int x, y, w, h, id;
int startingX, startingY;
int cameraY, yChange;
int ledgeIndex;
string s;
vector<Environment*> ofApp::eList;
vector<Item*> ofApp::items;

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

	//GameManager
	gm = new GameManager();
	gm->setup();


	//character Management
	mpm = new MultiPlayerManager(false);
	mpm->setup();
    
    enemyCount = 15;
    placeEnemies(enemyCount);
    
	//color
	color.set(255);

	//draw item image
	block.load("images/bomb.png");

	//coin sound
	coinSound.load("sounds/coin.mp3");
	coinSound.setMultiPlay(true);

	// register the listener so that we get the events
	ofAddListener(world.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(world.contactEndEvents, this, &ofApp::contactEnd);


	//create Environment Colliders
	input.open(ofToDataPath("environment/eData.txt").c_str());
	while (input >> x >> y >> w >> h >> s >> id) {  
 		Environment *e;
		x = x + (w/2);
		e = new Environment(x, y, w, h, s, id);
		eList.push_back(e);
		e->setup();
		collisionObjects.insert(make_pair(e, s));
	}
	input.close();

	//spawn items
	spawnRandomItem();

	//setup camera
	camera.setVFlip(true);
	startingX = 50;
	startingY = 1117; 
	
}

//--------------------------------------------------------------
void ofApp::update(){ 
	

	 
	
	handleCamera();

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
        
        //enemy update
        for(int i =0; i< enemies.size(); i++){
            if(enemies[i]->getHealth() <= 0){ //remove dead enemies
                //Have general animation and enemyDead(x,y); // plays till animation .size is reached
                enemies.erase(enemies.begin() + i);
            }else{
                enemies[i]->update();
            }
        }

		//item update
		
		for (int i = 0; i < items.size(); i++) {
			if (items[i]->contact) {
				coinSound.play();
				itemsToDelete.push_back(i);
			}
			else {
				items[i]->update();
				deleteItems();
			}
		}
 
		

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
        background.draw(0, 0, 5134, 1219);
        
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
        for(int i =0; i< enemies.size(); i++){
            enemies[i]->draw();
        }
        
		//item draw
		for (int i = 0; i < items.size(); i++) {
			items[i]->draw();
		}

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
			string a_type;
			string b_type;

            //Obtain collision object types
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
        
        
        if(a_type == "p_bull" && b_type == "enemy"){
            Enemy* enemy = (Enemy*)e.b->GetBody()->GetUserData();
            enemy->applyDamage(100);
        }else if(b_type == "p_bull" && a_type == "enemy" ){
            Enemy* enemy = (Enemy*)e.a->GetBody()->GetUserData();
            enemy->applyDamage(100);
        }else if(a_type == "e_bull" && b_type == "player"){
            Player* player = (Player*)e.b->GetBody()->GetUserData();
            player->applyDamage(5);
        }else if(b_type == "e_bull" && a_type == "player" ){
            Player* player = (Player*)e.a->GetBody()->GetUserData();
            player->applyDamage(5);
        }
        
//            std::cout << a_type << endl;
//            std::cout << b_type << endl;

		}
}

void ofApp::spawnRandomItem() {
    badLedges.open(ofToDataPath("environment/badLedges.txt").c_str());
    ofstream takenLedges;
    takenLedges.open(ofToDataPath("environment/takenLedges.txt").c_str());
    int bad;
    vector<int> badId;
    vector<int> takenId;
    while (badLedges >> bad) {
        badId.push_back(bad);
    }
    
    Environment *e;
    for (int i = 0; i < 50; i++) {
        int ledgeIndex = ofRandom(0, eList.size());
        e = eList[ledgeIndex];
        if (find(badId.begin(), badId.end(), e->getId()) != badId.end()) {
            int ledgeIndex = ofRandom(0, eList.size());
            e = eList[ledgeIndex];
        }
        else if (find(takenId.begin(), takenId.end(), e->getId()) != takenId.end()) {
            int ledgeIndex = ofRandom(0, eList.size());
            e = eList[ledgeIndex];
        }
        else {
            if (e->getTag() != "ladder") {
                //takenLedges << ofToString(e->getId()) << endl;
                takenId.push_back(e->getId());
                int ledgeX = e->getX();
                int ledgeY = e->getY() - (e->getHeight() / 2);
                int randLoc = ofRandom(ledgeX - e->getWidth() / 2, ledgeX + e->getWidth() / 2);
                Item *i1;
                i1 = new Item("coin", ledgeX, ledgeY - 8, 8, 0, i);
                i1->setup();
                items.push_back(i1);
            }
        }
    }
    
    badId.clear();
    takenId.clear();
    takenLedges.close();
    badLedges.close();
}


void ofApp::deleteItems() {
	for (int i = 0; i < itemsToDelete.size(); i++) {
		delete items[itemsToDelete[i]];//
		items.erase(items.begin() + itemsToDelete[i]);
	}
	itemsToDelete.clear();
}

 

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
	if (e.a != NULL && e.b != NULL) {
	}
}

//----------------------------------------------------------------
double ofApp::distance(int x1, int x2, int y1, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
//----------------------------------------------------------------
void ofApp::handleCamera() {
	if(MultiPlayerManager::players.size() > 1) {
		for (int i = 0; i < MultiPlayerManager::players.size() - 1; i++) {
			if (MultiPlayerManager::players[0]->getY() > 990) {
				MultiPlayerManager::players[i]->jumpForce = 1.3;
				MultiPlayerManager::players[i + 1]->jumpForce = 1.3;
				camera.setPosition(ofVec3f((MultiPlayerManager::players[i]->getX() + MultiPlayerManager::players[i + 1]->getX()) / 2, startingY, 180));
			}
			if (MultiPlayerManager::players[0]->getY() < 990) {
				MultiPlayerManager::players[i]->jumpForce = 1.8;
				MultiPlayerManager::players[i + 1]->jumpForce = 1.8;
				camera.setPosition(ofVec3f((MultiPlayerManager::players[i]->getX() + MultiPlayerManager::players[i + 1]->getX()) / 2, startingY - 250, 180));
			}
			if (MultiPlayerManager::players[0]->getY() < 740) {
				MultiPlayerManager::players[i]->jumpForce = 2.4;
				MultiPlayerManager::players[i + 1]->jumpForce = 2.4;
				camera.setPosition(ofVec3f((MultiPlayerManager::players[i]->getX() + MultiPlayerManager::players[i + 1]->getX()) / 2 - 20, startingY - 465, 180));
			}
			if (MultiPlayerManager::players[0]->getY() < 518) {
				MultiPlayerManager::players[i]->jumpForce = 3;
				MultiPlayerManager::players[i + 1]->jumpForce = 3;
				camera.setPosition(ofVec3f((MultiPlayerManager::players[i]->getX() + MultiPlayerManager::players[i + 1]->getX()) / 2 - 120, startingY - 700, 180));
			}
			if (MultiPlayerManager::players[0]->getY() < 280) {
				MultiPlayerManager::players[i]->jumpForce = 7;
				MultiPlayerManager::players[i + 1]->jumpForce = 7;
				camera.setPosition(ofVec3f((MultiPlayerManager::players[i]->getX() + MultiPlayerManager::players[i + 1]->getX()) / 2 - 20, startingY - 940, 180));
			}
			if (MultiPlayerManager::players[0]->getY() < 200) {
				MultiPlayerManager::players[i]->jumpForce = 9;
				MultiPlayerManager::players[i + 1]->jumpForce = 9;
			}
			if (MultiPlayerManager::players[0]->getY() < 88) {
				MultiPlayerManager::players[i]->jumpForce = 20;
				MultiPlayerManager::players[i + 1]->jumpForce = 20;
				camera.setPosition(ofVec3f((MultiPlayerManager::players[i]->getX() + MultiPlayerManager::players[i + 1]->getX()) / 2 - 20, startingY - 990, 180));
			}
			if (MultiPlayerManager::players[0]->getY() < 45) {
				MultiPlayerManager::players[i]->jumpForce = 30;
				MultiPlayerManager::players[i + 1]->jumpForce = 30;
				camera.setPosition(ofVec3f(MultiPlayerManager::players[i]->getX() + MultiPlayerManager::players[i + 1]->getX() / 2 - 20, startingY - 990, 180));
			}
			else if (camera.getY() >= 4205) {
				MultiPlayerManager::players[i]->jumpForce = 7;
				MultiPlayerManager::players[i + 1]->jumpForce = 7;
				camera.setPosition(ofVec3f(4205, startingY - 940, 180));
			}
			if (camera.getX() <= 160) {
				MultiPlayerManager::players[i]->jumpForce = 7;
				MultiPlayerManager::players[i + 1]->jumpForce = 7;
				camera.setPosition(ofVec3f(160, startingY, 180));
			}
		}
	}

	else {

		if (MultiPlayerManager::players[0]->getY() > 990) {
			MultiPlayerManager::players[0]->jumpForce = 1.3; 
			camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 90, startingY, 180));
		}
		if (MultiPlayerManager::players[0]->getY() < 990) {
			MultiPlayerManager::players[0]->jumpForce = 1.8; 
			camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 90 - 120, startingY - 250, 180));
		}
		if (MultiPlayerManager::players[0]->getY() < 740) {
			MultiPlayerManager::players[0]->jumpForce = 2.4; 
			camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 90 - 20, startingY - 465, 180));
		}
		if (MultiPlayerManager::players[0]->getY() < 518) {
			MultiPlayerManager::players[0]->jumpForce = 3; 
			camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 90 - 120, startingY - 700, 180));
		}
		if (MultiPlayerManager::players[0]->getY() < 280) {
			MultiPlayerManager::players[0]->jumpForce = 7; 
			camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 90 - 20, startingY - 940, 180));
		}
		if (MultiPlayerManager::players[0]->getY() < 200) {
			MultiPlayerManager::players[0]->jumpForce = 9; 
		}
		if (MultiPlayerManager::players[0]->getY() < 88) {
			MultiPlayerManager::players[0]->jumpForce = 20; 
			camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 90 - 20, startingY - 990, 180));
		}
		if (MultiPlayerManager::players[0]->getY() < 45) {
			MultiPlayerManager::players[0]->jumpForce = 30; 
			camera.setPosition(ofVec3f(MultiPlayerManager::players[0]->getX() + 90 - 20, startingY - 990, 180));
		}
		else if (camera.getX() >= 4205) {
			MultiPlayerManager::players[0]->jumpForce = 7; 
			camera.setPosition(ofVec3f(4205, startingY - 940, 180));
		}
		if (camera.getX() <= 160) {
			MultiPlayerManager::players[0]->jumpForce = 7; 
			camera.setPosition(ofVec3f(160, startingY, 180));
		}
	}
}

//generate enemies accross the level
void ofApp::placeEnemies(int count){
    for(int i = 0; i<count;i++){
        //Enemy::Enemy(int x, int y, int range, int dir, int speed, string patrol_path, string hit_path, string bullet_path){
        
        //make randoms for constructor
        double x = 200.0 + i * 75.0;
        double y = 1150.0 - i * 20.0;
        double patrolDist = 100.0;
        double speed = 0.5;
        
        Enemy* e = new Enemy(x ,y,patrolDist,0,0.2,"images/spider/spider_","images/megamanJumping/jump","images/spider_bullet");
        e->setup();
        enemies.push_back(e);
    }
}


//----------------------------------------------------------------
void ofApp::keyPressed(int key) { 
	for (int i = 0; i < MultiPlayerManager::players.size(); i++) {
		MultiPlayerManager::players[i]->keyPressed(key);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	for (int i = 0; i < MultiPlayerManager::players.size(); i++) {
		MultiPlayerManager::players[i]->keyReleased(key);
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
