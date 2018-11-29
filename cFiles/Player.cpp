
#include "Player.h" 
#include "Controller.h"
#include "ofApp.h"
b2Timer timer;
vector<Item*> ofApp::items;
Player::Player(string portName, int x, int y){
	this->portName = portName;
	this->x = x;
	this->y = y;
	playerList.push_back(this);

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

	
	//setup player attributes
	speed = 12;  //speed of player
	speedMultiplier = 1.60; //sprint at 160%
	jumpCount = 0; //used to keep track of double jump
	runningNum = 0;  //used to index running sprites
	idleNum = 0;  //index idle sprites
	jumpNum = 0;  //index jump sprites
	blink = 0;    //random between 0 and 1
	radius = 65;  //radius of circle collider
	size = radius * 2.2;  //size of character image is based of size of collider
	jumpForce = radius * 3.2;   //set jumpForce to size*2 because size adds mass, thus a greater jumpForce is needed

	//create playerCollider 
	ob = new collider();
	playerCollider = ob->Circle(x, y, radius, 25, 0, 0);
	controller = new Controller(portName, 9600);
	controller->setup();

	//item vars
	count = 0; //used to determine when item is throwable

	//load jumping animation
	for (int i = 1; i < 4; i++) {
		string file = "images/jump" + ofToString(i) + ".png";
		ofImage jump;
		jump.load(file);
		jumpAnimation.push_back(jump); 
	}

	//load idle animation
	for (int i = 1; i < 5; i++) {
		string file = "images/idle" + ofToString(i) + ".png";
		ofImage idle;
		idle.load(file);
		idleAnimation.push_back(idle);
	}

	//load running animation
	for (int i = 1; i < 7; i++) {
		string file = "images/running" + ofToString(i) + ".png";
		ofImage runner;
		runner.load(file);
		runningAnimation.push_back(runner);
	}

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
    controller->update();
	playerCollider.get()->update();	 
	if (getX()-radius < 0) {
		setX(radius);
	}
	if (getX() + radius > ofGetWidth()) {
		setX(ofGetWidth()-radius);
	}
    //get controller input
    controllerInput(controller->getInput());

    //NEED TO UPDATE x & y slot positions
}

void Player::draw() 
{ 
	//set back to white 
	ofSetColor(255);

	//orient images based on player state/direction
	orientPlayer(); 

	if (running && !jumpState) {
		//running Animation handler 

		runningHandler();
	}

	//jump handler
	else if (jumpState) {
		jumpHandler();
	}

	//idle handler
	else {
		idleHandler();
	}
    //playerCollider.get()->draw();

}
//b = UP, c = DOWN, p = LEFT, a = RIGHT
void Player::controllerInput(char key){
	switch (key) {  

		//sprint
		case 's': 
			if (running && !inAir) {
				if (getXVelocity() > 0) {
					setVelocity(speed * speedMultiplier, getYVelocity());
				}
				else {
					setVelocity(-speed * speedMultiplier, getYVelocity());					}		
				}
				break;
		

		//run right
		case 'r': {
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
			running = true;
			setVelocity(-speed, getYVelocity());
			break;
		}
		case 'L': {
			running = false;
			setVelocity(0, getYVelocity());
			break;
		}


		//jump
		case 'c': 
			if (!inAir) { 
				jumpNum = 0;
				jumpState = true;
				playerCollider.get()->addForce(ofVec2f(0, getY()), -jumpForce);
			}
			if (doubleJump) {
				playerCollider.get()->addForce(ofVec2f(0, getY()), -jumpForce);
				doubleJump = false;
			}
			break;  
			
			 		
		//grab items (left button) 
		case 'p':  
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
			if (hasItem && getItem()->tossForce > getItem()->scale + 2) {
				throwItem();
			}
			break;
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
		runningAnimation[runningNum].draw(getX() - radius, getY() - radius - 12, size, size);
		if (ofGetFrameNum() % int(speed *.5) == 0) {
			runningNum++;
			runningNum = runningNum % runningAnimation.size();
		}	
}


void Player::jumpHandler() {

	//if in the air 
	if (abs(getYVelocity()) > 0) {
		inAir = true;
		jumpAnimation[jumpNum].draw(getX() - radius, getY() - radius - 12, size, size);
		if (ofGetFrameNum() % 25 == 0) {
			if (jumpNum == jumpAnimation.size()-1) {
				jumpAnimation[jumpAnimation.size()-1].draw(getX() - radius, getY() - radius - 12, size, size);
			}
			else {
				jumpNum++;
			}
			jumpNum = jumpNum % jumpAnimation.size();
		}
	}

	//reset after falling to the ground
	else {
		inAir = false; 
		jumpState = false; 
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

	//blinks about half the time  
	if (idleNum == 3 && blink > .35) {
		idleAnimation[0].draw(getX() - radius, getY() - radius - 12, size, size);
	}
	else {
		idleAnimation[idleNum].draw(getX() - radius, getY() - radius - 12, size, size);
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
	double closest_dist = 120;
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
