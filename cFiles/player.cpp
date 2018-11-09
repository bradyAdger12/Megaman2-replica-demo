#include "player.h" 

bool areFlipped = false;
void player::setup()
{
	//player states
	running = false;
	leftOriented = false;
	
	//setup player attributes
	speed = 12;
	runningFrameNum = 0;
	jump = -10;
	
	//load idle image
	idleSkin.load("images/idle.png");

	//load running animation
	for (int i = 1; i < 7; i++) {
		string file = "images/running" + ofToString(i) + ".png";
		ofImage runner;
		runner.load(file);
		runningAnimation.push_back(runner);
	}

	//create playerCollider 
	ob = new object();
	playerCollider = ob->Circle(50, ofGetHeight()-40, 35, 25, 0, 0); 

}

void player::update()
{ 
		playerCollider.get()->update();	
}

void player::draw()
{ 
	//draw player 
	ofSetColor(255);

	//running Animation handler
	runningHandler();

}

void player::keyPressed(int key)
{
	if (key == 'd') {
		playerCollider.get()->setVelocity(speed, getXVelocity());
		running = true; 
	}
	else if (key == 'a') { 
		running = true;  
		playerCollider.get()->setVelocity(-speed, getYVelocity());
	}
	else if (key == 'w') {
		playerCollider.get()->setVelocity(getXVelocity(), jump);
	}
}

void player::keyReleased(int key)
{
	
	if (key == 'd') {
		running = false;
		runningFrameNum = 0;
		setVelocity(0, getYVelocity());
	}
	if (key == 'a') {
		running = false;
		setVelocity(0, getYVelocity());
	}
	if (key == 'w') {
		setVelocity(getXVelocity(), 0);
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

void player::setVelocity(float x, float y)
{
	return playerCollider.get()->setVelocity(x,y);
}

void player::flipImages() {
	areFlipped = true;
	for (int i = 0; i < runningAnimation.size(); i++) { 
		runningAnimation[i].mirror(false, true);
	} 
}

void player::runningHandler() {

	if (running) {
		if (leftOriented && getXVelocity() < 0) {
			flipImages();
			leftOriented = false;
			idleSkin.mirror(false, true);
		}
		if (!leftOriented && getXVelocity() > 0) {
			leftOriented = true;
			if (areFlipped) {
				idleSkin.mirror(false, true);
				flipImages();
			}

		}

		runningAnimation[runningFrameNum].draw(getX() - 40, getY() - 40, 80, 80);

		if (ofGetFrameNum() % int(speed * 1.5) == 0) {
			runningFrameNum++;
			runningFrameNum = runningFrameNum % runningAnimation.size();
		}
	}

	else {  //if player is idle
		idleSkin.draw(getX() - 40, getY() - 40, 80, 80);
	}
}
