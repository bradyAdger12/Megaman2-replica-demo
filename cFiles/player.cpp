#include "player.h" 

void player::setup()
{
	//player states
	running = false;
	leftOriented = false;
	isFlipped = false;
	
	//setup player attributes
	speed = 12;
	runningNum = 0;
	blink = 0;
	size = 140;
	jumpForce = size*2;
	radius = size/2.2;
	
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


	if (running) {
		//running Animation handler
		runningHandler();
	}
	else {
		idleHandler();
	}

}

void player::keyPressed(int key)
{
	if (key == 'd') {
		setVelocity(speed, getYVelocity());
		running = true; 
	}
	else if (key == 'a') { 
		running = true;  
		setVelocity(-speed, getYVelocity());
	}
	else if (key == 'w') {  
		playerCollider.get()->addForce(ofVec2f(0, getY()), -jumpForce);
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

void player::flipImages() {
	isFlipped = true;
	for (int i = 0; i < runningAnimation.size(); i++) { 
		runningAnimation[i].mirror(false, true);
	} 
	for (int i = 0; i < idleAnimation.size(); i++) {
		idleAnimation[i].mirror(false, true);
	}
}

void player::runningHandler() { 
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

		runningAnimation[runningNum].draw(getX() - radius, getY() - radius - 10, size, size);

		if (ofGetFrameNum() % int(speed * .5) == 0) {
			runningNum++;
			runningNum = runningNum % runningAnimation.size();
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
	if (idleNum == 3 && blink > .5) {
		idleAnimation[0].draw(getX() - radius, getY() - radius - 10, size, size);
	}
	else {
		idleAnimation[idleNum].draw(getX() - radius, getY() - radius - 10, size, size);
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
