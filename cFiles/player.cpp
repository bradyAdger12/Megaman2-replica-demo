#include "player.h" 

void player::setup()
{
	//player states
	running = false;
	leftOriented = false;
	jumpState = false;
	inAir = false; 
	
	//setup player attributes
	speed = 12;
	runningNum = 0;
	blink = 0;    //random between 0 and 1
	size = 140;   //size of the player skin
	jumpForce = size*2;   //set jumpForce to size*2 because size adds mass, thus a greater jumpForce is needed
	radius = size/2.2;

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

	//create playerCollider 
	ob = new collider();
	playerCollider = ob->Circle(50, ofGetHeight()-40, radius, 25, 0, 0); 

}

void player::update()
{  
	playerCollider.get()->update();	
	if (getX()-radius < 0) {
		setX(radius);
	}
	if (getX() + radius > ofGetWidth()) {
		setX(ofGetWidth()-radius);
	}
}

void player::draw()
{ 
	//set back to white
	ofSetColor(255);


	//orient images based on player state/direction
	orientPlayer();

	if (running && !jumpState) {
		//running Animation handler
		runningHandler();
	}

	else if (jumpState) {
		jumpHandler();
	}
	else {
		idleHandler();
	}

}

void player::keyPressed(int key) {

		if (key == 'd') {
			setVelocity(speed, getYVelocity());
			running = true;
		}
		else if (key == 'a') {
			running = true;
			setVelocity(-speed, getYVelocity());
		}
	
		else if (!inAir) {
			if (key == 'w') {
				jumpState = true;
				playerCollider.get()->addForce(ofVec2f(0, getY()), -jumpForce);
			}
	}
}

void player::keyReleased(int key)
{

	if (key == 'd') { 
		running = false; 
		setVelocity(0, getYVelocity());
	}
	if (key == 'a') { 
		running = false;
		setVelocity(0, getYVelocity());
	} 
	
}


//flip images whenever turned to the left
void player::flipImages() {
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

void player::orientPlayer() {
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

void player::runningHandler() { 

		runningAnimation[runningNum].draw(getX() - radius, getY() - radius - 15, size, size);
		if (ofGetFrameNum() % int(speed *.5) == 0) {
			runningNum++;
			runningNum = runningNum % runningAnimation.size();
		}
		
	
}


void player::jumpHandler() {

	//if in the air 
	if (abs(getYVelocity()) > 0) {
		inAir = true;
		jumpAnimation[jumpNum].draw(getX() - radius, getY() - radius - 15, size, size);
		if (ofGetFrameNum() % 25 == 0) {
			if (jumpNum == jumpAnimation.size()-1) {
				jumpAnimation[jumpAnimation.size()-1].draw(getX() - radius, getY() - radius - 15, size, size);
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

void player::idleHandler() {
	if (ofGetFrameNum() % 17 == 0) {
		idleNum++;
		idleNum = idleNum % idleAnimation.size();
		//deteermines if model blinks or not
		blink = ofRandom(0, 1);
	}

	//blinks about half the time  
	if (idleNum == 3 && blink > .35) {
		idleAnimation[0].draw(getX() - radius, getY() - radius - 15, size, size);
	}
	else {
		idleAnimation[idleNum].draw(getX() - radius, getY() - radius - 15, size, size);
	}
}


int player::getX()
{
	return playerCollider.get()->getPosition().x;
}

int player::getY()
{
	return playerCollider.get()->getPosition().y;
}

float player::getXVelocity()
{
	return playerCollider.get()->getVelocity().x;
}

float player::getYVelocity()
{
	return playerCollider.get()->getVelocity().y;
}

void player::setX(float x)
{
	playerCollider.get()->setPosition(x, playerCollider.get()->getPosition().y);
}

void player::setY(float y)
{
	playerCollider.get()->setPosition(playerCollider.get()->getPosition().x, y);
}

void player::setVelocity(float x, float y)
{
	return playerCollider.get()->setVelocity(x, y);
}
