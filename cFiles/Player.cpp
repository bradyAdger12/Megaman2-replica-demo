
#include "Player.h" 
#include "Controller.h"
#include "ofApp.h"
#include "GameManager.h" 
bool GameManager::active; 
bool GameManager::paused; 
vector<Item*> ofApp::items; 
b2Timer* GameManager::timer;

Player::Player(string portName, int x, int y, bool playerOne){
	this->portName = portName;
	this->playerOne = playerOne;
	this->x = x;
	this->y = y;
	//playerList.push_back(this);
}
void Player::setup()
{
	//player states
	running = false;
	leftOriented = false;
	jumpState = false;
	inAir = false;  
	isFlipped = false;
	doubleJump = false;
	hasItem = false;  
	climbing = false; 
	climbingPaused = false;
	firingPosition = false; 
	
	//setup player attributes
	speed = 2;  //speed of player
	speedMultiplier = 1.20; //sprint at 120%
	jumpCount = 0; //used to keep track of double jump
	runningNum = 0;  //used to index running sprites
	idleNum = 0;  //index idle sprites
	jumpNum = 0;  //index jump sprites
	climbingNum = 0; //index climbing sprites
	shootingNum = 0; //index shhoting sprites
	blink = 0;    //random between 0 and 1
	radius = 11;  //radius of circle collider
	jumpForce = 0; 
	size = radius * 2.4;  //size of character image is based of size of collider 

	//pause logic
	pauseCount = 0;

	//create playerCollider 
	ob = new collider();
	playerCollider = ob->Circle(x, y, radius, 25, 0, 0);
	controller = new Controller(portName, 9600);
	controller->setup();

	//item vars
	count = 0; //used to determine when item is throwable

	//load jumping animation
	for (int i = 1; i < 2; i++) {
		string file = "images/megamanJumping/jump" + ofToString(i) + ".png";
		ofImage jump;
		jump.load(file);
		jumpAnimation.push_back(jump); 
	}

	//load shooting animation
	for (int i = 2; i < 5; i++) {
		string file = "images/megamanShooting/shoot" + ofToString(i) + ".png";
		ofImage shoot;
		shoot.load(file);
		shoot.mirror(false, true);
		shootingAnimation.push_back(shoot);
	}

	//load idle animation
	for (int i = 1; i < 4; i++) {
		string file = "images/megamanIdle/idle" + ofToString(i) + ".png";
		ofImage idle; 
		idle.load(file);
		idleAnimation.push_back(idle);
	}

	//load climbing animation 
	for (int i = 1; i < 3; i++) {
		string file = "images/megamanClimbing/climbing" + ofToString(i) + ".png";
		ofImage climb;
		climb.load(file);
		climbingAnimation.push_back(climb);
	}

	//load running animation
	for (int i = 1; i < 4; i++) {
		string file = "images/megamanRunning/running" + ofToString(i) + ".png";
		ofImage runner;
		runner.load(file);
		runningAnimation.push_back(runner);
	}
    
    //Load Bullet animation
    //TODO:
    //Player* player, int speed, int damage, float fireRate, int size,vector<ofImage> images
    shootingHandler = new ShootingHandler(this, 20, 5, 0.2, 3, bulletAnimation);
	playerCollider->setData(this);
}
//********************** ITEM LOGIC **********************************************
int Player::getX_Slot(){
    return x_Slot;
}
int Player::getY_Slot(){
    return y_Slot;
}
void Player::useItem(){
    if(hasItem){
        item->use();
    }
}
void Player::throwItem(){
    item->toss();
    hasItem = false; 
}

void Player::equipItem(Item *item){
    if(item){
        this->item=item;
        hasItem = true; 
        this->item->setParent(this);
    }
}
Item* Player::getItem() {
	if (hasItem) {
		return this->item;
	}
	return NULL;
}

//********************** ITEM LOGIC **********************************************



void Player::update()  { 

	//find closest ladder
	for (int i = 0; i < Environment::ladders.size(); i++) {
		Environment::ladders[i]->distanceFromPlayer = distance(getX(), Environment::ladders[i]->getX(), getY(), Environment::ladders[i]->getY());
		if (i == Environment::ladders.size() - 1) {
			bubbleSort();  
		}
	}


	//controller input
	/*controller->update();
	controllerInput(controller->getI());*/

	if (!eLadder->ladder) {
		climbingPaused = false;
		climbing = false;
		if (abs(getYVelocity() <= 0)) {
			inAir = false;
		}
	}

	//shooting handler
	shootingHandler->update();

	//update collider
	playerCollider.get()->update();	  

	//handle running
	if (running && !jumpState && !shooting) { 
		runningHandler();
	}

	//handle jumping
	else if (jumpState && !climbing) {
		jumpHandler(); 
	} 

	else if (shooting && running) {
		shootingAnimationHandler();
	}

	else if (!shooting && running && shootingTimer.GetMilliseconds() < 1500) {
		shootingAnimationHandler();
	} 

	else if (climbing) {
		climbingHandler();
	}

	//handle idle
	else {
		idleHandler(); 
	} 
    //get controller input
    controllerInput(controller->getI());
 
    shootingHandler->update();
    //NEED TO UPDATE x & y slot positions

}

void Player::draw() 
{ 
	/*ofSetColor(0, 0, 0, 150);
	playerCollider.get()->draw();*/

	//set back to white 
	ofSetColor(255);

	//orient images based on player state/direction
	orientPlayer(); 
	 
	//running drawing handler
	if (running && !jumpState && !shooting) {
		runningAnimation[runningNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		runningAnimation[runningNum].draw(getX() - radius, getY() - 14, size, size);
	}


	//running shooting drawing
	else if (shooting && running) {
		shootingAnimation[shootingNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		shootingAnimation[shootingNum].draw(getX() - radius, getY() - 14, size, size);
	}

	else if (!shooting && running && shootingTimer.GetMilliseconds() < 3000) {
		shootingAnimation[shootingNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		shootingAnimation[shootingNum].draw(getX() - radius, getY() - 14, size, size);
	}


	//idle shooting drawing
	else if (shooting && !running) {
		idleShoot.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		idleShoot.draw(getX() - radius, getY() - 14, size, size);
	}

	else if (!shooting && !running && shootingTimer.GetMilliseconds() < 1500 && !climbing) {
		idleShoot.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		idleShoot.draw(getX() - radius, getY() - 14, size, size);
	}

	//jump drawing handler
	else if (jumpState && !climbing) {
		if (abs(getYVelocity()) > 0) {
			jumpAnimation[jumpNum].draw(getX() - radius, getY() - 14, size, size);
			if (ofGetFrameNum() % 25 == 0) {
				if (jumpNum == jumpAnimation.size() - 1) {
					jumpAnimation[jumpAnimation.size() - 1].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
					jumpAnimation[jumpAnimation.size() - 1].draw(getX() - radius, getY() - 14, size, size);
				}
			}
		}
	}

	else if (climbing) {
		climbingAnimation[climbingNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		climbingAnimation[climbingNum].draw(getX() - radius, getY() - 14, size, size);
	} 

	else if (climbingPaused && eLadder->ladder) {
		climbingAnimation[climbingNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		climbingAnimation[climbingNum].draw(getX() - radius, getY() - 14, size, size);
	}

	//idle drawing handler
	else {
		if (idleNum == 1 && blink > .35) {
			idleAnimation[0].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
			idleAnimation[0].draw(getX() - radius, getY() - 14, size, size);
		}
		else {
			idleAnimation[idleNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
			idleAnimation[idleNum].draw(getX() - radius, getY() - 14, size, size);
		}
	}
    
    //Draw bullets
    shootingHandler->draw();
}
//b = UP, c = DOWN, p = LEFT, a = RIGHT
void Player::controllerInput(char key){
    //std::cout << key << endl;
	switch (key) { 

	//sprint 
	case 's':
		if (running && !inAir) {
			if (getXVelocity() > 0) {
				setVelocity(speed * speedMultiplier, getYVelocity());
			}
			else {
				setVelocity(-speed * speedMultiplier, getYVelocity());
			}
		}
		break;


		//run right
	case 'r': {
		playerCollider.get()->body->SetActive(true);
		running = true;
		setVelocity(speed, getYVelocity());
		break;
	}
	case 'R': {
		running = false;
		setVelocity(0, getYVelocity());
		break;
	}

			  //run left
	case 'l': {
		playerCollider.get()->body->SetActive(true);
		running = true;
		setVelocity(-speed, getYVelocity());
		break;
	}
	case 'L': {
		running = false;
		setVelocity(0, getYVelocity());
		break;
	}


			  //grab items (left button) 
	case 'p':
		playerCollider.get()->body->SetActive(true);
		if (hasItem) {
			if (getItem()->style == 0) {
				getItem()->tossForce *= getItem()->multiplier;
				if (getItem()->tossForce >= getItem()->maxTossForce) {
					getItem()->tossForce = getItem()->maxTossForce;
				}

			}
			else {
				useItem();
			}
		}
		else {
			equipItem(closestUsableItem(getX(), getY()));
		}
		break;

	case 'P':
		playerCollider.get()->body->SetActive(true);
		if (hasItem && getItem()->tossForce > getItem()->scale + .25) {
			throwItem();
		}
		break;

	case 'b':
		playerCollider.get()->body->SetActive(true);
		if (playerOne) {
			GameManager::active = false;
			GameManager::paused = true;
		}
		break;


		//used for climbing
	case 'u':
		if (eLadder->ladder && eLadder->canClimb) {
			jumpState = false;
			climbing = true;
			if (climbing) {
				playerCollider.get()->body->SetActive(true);
				setVelocity(getXVelocity(), -speed / 1.6); 
			}
		}
		break;

	case 'U':
		if (eLadder->ladder) {
			climbing = false;
			climbingPaused = true;
			climbingNum = 0;
			playerCollider.get()->body->SetActive(false);
		}

		break;

	case 'd':
		if (eLadder->ladder && eLadder->canClimb) {
			jumpState = false;
			climbing = true;
			if (climbing) {
				playerCollider.get()->body->SetActive(true);
				setVelocity(getXVelocity(), speed / 1.6); 
			}
		}
		break;

	case 'D':
		if (eLadder->ladder) {
			climbing = false;
			climbingPaused = true;
			climbingNum = 0;
			playerCollider.get()->body->SetActive(false);
		}
		break;
	}
	//jump
	if (key == 'c') {
		if (!inAir && !climbing) {  
				jumpForce = 1.3;  
				jumpState = true;
				jumpNum = 0;
				if (!climbing) {
					playerCollider.get()->addForce(ofVec2f(0, getY()), -jumpForce); 
				}
				else {
					playerCollider.get()->addForce(ofVec2f(0, getY()), -jumpForce/1.4);
				}
			}
	}
    if(key == 'a'){
        shooting = true;
        shootingHandler->setShooting(true);
    }
    if(key == 'A'){
        shooting = false;
        shootingHandler->setShooting(false);
        shootingHandler->resetDeltaTime();
    }
}



//flip images whenever turned to the left
void Player::flipImages() {
	isFlipped = true;
	for (int i = 0; i < runningAnimation.size(); i++) {
		runningAnimation[i].mirror(false, true);
	}
	for (int i = 0; i < idleAnimation.size(); i++) {
		idleAnimation[i].mirror(false, true);
	}
	for (int i = 0; i < jumpAnimation.size(); i++) {
		jumpAnimation[i].mirror(false, true);
	}
	for (int i = 0; i < shootingAnimation.size(); i++) {
		shootingAnimation[i].mirror(false, true);
	}
	idleShoot.mirror(false, true);
}

void Player::orientPlayer() {
	if (running) {
		if (leftOriented && getXVelocity() < 0) {
			flipImages();
			leftOriented = false;
		}
		if (!leftOriented && getXVelocity() > 0) {
			leftOriented = true;
			if (isFlipped) {
				flipImages();
			}
		}
	}
}

void Player::runningHandler() {
	if (ofGetFrameNum() % 7 / 2 == 0) {
		runningNum++;
		runningNum = runningNum % runningAnimation.size();
	}
}

void Player::shootingAnimationHandler() {
	if (ofGetFrameNum() % 7 / 2 == 0) {
		shootingNum++;
		shootingNum = shootingNum % shootingAnimation.size();
	}
}

void Player::climbingHandler() {
	if (ofGetFrameNum() % 7 == 0 && abs(getYVelocity()) > .01) {
		climbingNum++;
		climbingNum = climbingNum % climbingAnimation.size();
	}
}


void Player::jumpHandler() {

	//if in the air 
	if (abs(getYVelocity()) > 0) {
		inAir = true;
		if (ofGetFrameNum() % 25 / 2 == 0) {
			if (jumpNum != jumpAnimation.size() - 1) {
				jumpNum++;
			}
			jumpNum = jumpNum % jumpAnimation.size();
		}
	}

	//reset after falling to the ground
	else {
		inAir = false;
		jumpState = false;
		jumpCount = 0;
		jumpNum = 0;  //reset to first jump images whenever you hit the ground 
	}
}

void Player::idleHandler() {
	if (ofGetFrameNum() % 17 == 0) {
		idleNum++;
		idleNum = idleNum % idleAnimation.size();
		//deteermines if model blinks or not
		blink = ofRandom(0, 1);
	}
}


int Player::getX()
{
	return playerCollider.get()->getPosition().x;
}

int Player::getY()
{
	return playerCollider.get()->getPosition().y;
}

int Player::getRadius()
{
	return playerCollider.get()->getRadius();
}

ofVec2f Player::getPosition()
{
	return ofVec2f(getX(), getY());
}

float Player::getXVelocity()
{
	return playerCollider.get()->getVelocity().x;
}

float Player::getYVelocity()
{
	return playerCollider.get()->getVelocity().y;
}

void Player::setX(float x)
{
	playerCollider.get()->setPosition(x, playerCollider.get()->getPosition().y);
}

void Player::setY(float y)
{
	playerCollider.get()->setPosition(playerCollider.get()->getPosition().x, y);
}

void Player::setVelocity(float x, float y)
{
	return playerCollider.get()->setVelocity(x, y);
}

Item* Player::closestUsableItem(int x, int y) {
	Item *closest;
	double dist;
	double closest_dist = radius * 2;
	if (ofApp::items.size() > 0) {      //if there are items  
		for (int i = 0; i < ofApp::items.size(); i++) { //check all
			if (!ofApp::items[i]->hasParent()) {        //without parent
				dist = distance(x, ofApp::items[i]->getX(), y, ofApp::items[i]->getY());
				if (dist < closest_dist) { //within distance
					return ofApp::items[i];
				}
			}
		}
	}
	return NULL;
}

//Returns distance between 2 pts
double Player::distance(int x1, int x2, int y1, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
int Player::getOrientation(){
    if(leftOriented){
        return 1;
    }else{
        return 0;
    }
}
 
