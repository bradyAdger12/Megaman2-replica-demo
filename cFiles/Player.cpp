
#include "Player.h" 
#include "Controller.h"
#include "ofApp.h"
#include "GameManager.h"     
Player::Player(string portName, int x, int y, bool playerOne, int id){
	this->portName = portName;
	this->playerOne = playerOne;
	this->id = id;
	this->x = x;
	this->y = y;
    this->health = 100;
	//playerList.push_back(this);
    ofApp::collisionObjects.insert(make_pair(this, "player"));
	playerList.push_back(this);
    std::cout<<"Player Inited with ID " << id <<endl; 
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
	climbing = false; 
	climbingPaused = false;
	firingPosition = false; 
	randClimbPic = false;
	dead = false;
	justDied = false;
	spawning = true;
	reset = false;
	win = false;
	justWon = false;
	canJump = true;
	
	//setup player attributes
	score = 0; //player score
	speed = 2;  //speed of player
	speedMultiplier = 1.20; //sprint at 120%
	jumpCount = 0; //used to keep track of double jump
	runningNum = 0;  //used to index running sprites
	idleNum = 0;  //index idle sprites
	dyingNum = 0; //index dying sprites
	jumpNum = 0;  //index jump sprites
	spawningNum = 0; //spawn sprites
	climbingNum = 0; //index climbing sprites
	shootingNum = 0; //index shhoting sprites
	blink = 0;    //random between 0 and 1
	radius = 11;  //radius of circle collider 
	size = radius * 2.4;  //size of character image is based of size of collider 

	//pause logic
	pauseCount = 0;

	//sounds
	playerDeath.load("sounds/deathSound.mp3"); 

	//create playerCollider 
	ob = new collider();
	playerCollider = ob->Circle(x, y, radius, 25, 0, 0);
	if (!MultiPlayerManager::keyboard) {
		controller = new Controller(portName, 9600);
		controller->setup();
	}

	//item vars
	count = 0; //used to determine when item is throwable

	//load jumping animation
	for (int i = 1; i < 2; i++) {
		string file = "images/megaman" + ofToString(id) + "Jumping/jump" + ofToString(i) + ".png";
		ofImage jump;
		jump.load(file);
		jumpAnimation.push_back(jump);
	}

	//load shooting animation
	for (int i = 2; i < 5; i++) {
		string file = "images/megaman" + ofToString(id) + "Shooting/shoot" + ofToString(i) + ".png";
		ofImage shoot;
		shoot.load(file);
		shoot.mirror(false, true);
		shootingAnimation.push_back(shoot);
	}

	//spawn animation 
	for (int i = 1; i < 4; i++) {
		string file = "images/megaman" + ofToString(id) + "Spawning/spawn" + ofToString(i) + ".png";
		ofImage spawn;
		spawn.load(file);
		spawnAnimation.push_back(spawn);
	}

	//load idle animation
	for (int i = 1; i < 4; i++) {
		string file = "images/megaman" + ofToString(id) + "Idle/idle" + ofToString(i) + ".png";
		ofImage idle;
		idle.load(file);
		idleAnimation.push_back(idle);
	}

	//load climbing animation 
	for (int i = 1; i < 3; i++) {
		string file = "images/megaman" + ofToString(id) + "Climbing/climbing" + ofToString(i) + ".png";
		ofImage climb;
		climb.load(file);
		climbingAnimation.push_back(climb);
	}

	//load dying animation 
	for (int i = 1; i < 6; i++) {
		string file = "images/megamanDying/death" + ofToString(i) + ".png";
		ofImage die;
		die.load(file);
		dyingAnimation.push_back(die);
	}

	//load running animation
	for (int i = 1; i < 4; i++) {
		string file = "images/megaman" + ofToString(id) + "Running/running" + ofToString(i) + ".png";
		ofImage runner;
		runner.load(file);
		runningAnimation.push_back(runner);
	}
	//load Bullet animation
	for (int i = 1; i < 4; i++) {
		string file = "images/megamanBullet/mm_shoot_" + ofToString(i) + ".png";
		ofImage bull;
		bull.load(file);
		bulletAnimation.push_back(bull);
	}

	//idle shoot animation
	idleShoot.load("images/megaman" + ofToString(id) + "Shooting/shoot1.png");
	idleShoot.mirror(false, true);

	//ShootingHandler::ShootingHandler(Player* player, int speed, int damage, float fireRate, int size,vector<ofImage> images){
	shootingHandler = new ShootingHandler(this, 3, 25, 0.2, 8, bulletAnimation);
	playerCollider->setData(this);
}
//********************** ITEM LOGIC **********************************************
int Player::getX_Slot(){
    return x_Slot;
    return x_Slot;
}
int Player::getY_Slot(){
    return y_Slot;
} 

//********************** ITEM LOGIC **********************************************



void Player::update()  {  

	if (getY() > 1400) {
		applyDamage(100);
	}

	if (justDied) {
		deathTimer.Reset();
		playerDeath.play(); 
		cout << "player death music" << endl;
		justDied = false;
	}

	if (dead && deathTimer.GetMilliseconds() > 3500) { 
		reset = true;
		delete controller;
	}

	if (!justWon && win) {
		winTimer.Reset();
		 
		justWon = true;
	}

	if (win && winTimer.GetMilliseconds() >= 6000) {   
		for (int i = 0; i < MultiPlayerManager::players.size(); i++) {
			MultiPlayerManager::players[i]->health = 0;
			MultiPlayerManager::players[i]->reset = true;
		}
	}


	//determine if player made it to the end
	isWin();


	//correct players speed if going too fast
	if (abs(getXVelocity()) > 2) {
		if (getXVelocity() > 0) {
			setVelocity(speed, getYVelocity());
		}
		if (getXVelocity() < 0) {
			setVelocity(-speed, getYVelocity());
		}
	}


	//find ladder closest to player
	findClosestLadder();

	
	//if player is using an arduino. open up port for streaming
	if (!MultiPlayerManager::keyboard) {
		if (GameManager::go && !dead) { 
			controller->update();
			controllerInput(controller->getI());
		}
	} 

	if (!ladder) {
		climbingPaused = false;
		climbing = false;
		if (abs(getYVelocity() <= 0)) {
			inAir = false;
		}
	}


	if (!dead) {
		//shooting handler
		shootingHandler->update();

		//update collider
		playerCollider.get()->update();

		//spawn handler
		if (!GameManager::go && GameManager::spawnTimer.GetMilliseconds() < 500) {
			spawnHandler();
		}

		//handle running
		if (running && !jumpState && !shooting) {
			if (shootingTimer.GetMilliseconds() < 1500) {
				shootingAnimationHandler();
			}
			else {
				runningHandler();
			}
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

	}

	else {
		dyingHandler();
	}
 
}

void Player::draw() 
{ 

    
	//if player dies
	if (dead && deathTimer.GetMilliseconds() < 1000) {  
		setVelocity(0, 0);
		dyingAnimation[dyingNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		dyingAnimation[dyingNum].draw(getX() - radius*2, getY() - 14 - radius, size*2, size*2);
	}

	if(!dead) { 

		//set back to white 
		ofSetColor(255);

		//orient images based on player state/direction
		orientPlayer();

		if (!GameManager::go && GameManager::spawnTimer.GetMilliseconds() < 600) {
			spawnAnimation[spawningNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
			spawnAnimation[spawningNum].draw(getX() - radius, getY() - 14, size, size);
		}

		else {

			//running drawing handler
			if (running && !jumpState && !shooting) {
				if (shootingTimer.GetMilliseconds() < 1500) {
					shootingAnimation[shootingNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
					shootingAnimation[shootingNum].draw(getX() - radius, getY() - 14, size, size);
				}
				else {
					runningAnimation[runningNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
					runningAnimation[runningNum].draw(getX() - radius, getY() - 14, size, size);
				}
			}


			//running shooting drawing
			else if (shooting && running) {
				shootingAnimation[shootingNum].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
				shootingAnimation[shootingNum].draw(getX() - radius, getY() - 14, size, size);
			}

			else if (!shooting && running && shootingTimer.GetMilliseconds() < 1500) {
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


			else if (climbingPaused && ladder) {
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
		}

		//Draw bullets
		shootingHandler->draw();
	}
    
}
//b = UP, c = DOWN, p = LEFT, a = RIGHT
void Player::controllerInput(char key){ 
	switch (key) {		
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

	case 'b':
		playerCollider.get()->body->SetActive(true);
		if (playerOne) {
			GameManager::active = false;
			GameManager::paused = true;
		}
		break;


		//used for climbing
	case 'u':
		if (ladder && canClimb) {
			jumpState = false;
			randClimbPic = true;
			setX(eLadder->getX());
			climbing = true;
			if (climbing) {
				playerCollider.get()->body->SetActive(true);
				setVelocity(getXVelocity(), -speed / 1.6);
			}
		}
		break;

	case 'U':
		if (ladder) {
			climbing = false;
			climbingPaused = true;
			if (randClimbPic) {
				int rand = ofRandom(0, 2);
				climbingNum = rand;
				randClimbPic = false;
			}
			playerCollider.get()->body->SetActive(false);
		}

		break;

	case 'd':
		if (ladder && canClimb) {
			jumpState = false;
			randClimbPic = true;
			climbing = true;
			if (climbing) {
				playerCollider.get()->body->SetActive(true);
				setVelocity(getXVelocity(), speed / 1.6);
			}
		}
		break;

	case 'D':
		if (ladder) {
			climbing = false;
			climbingPaused = true;
			if (randClimbPic) {
				int rand = ofRandom(0, 2);
				climbingNum = rand;
				randClimbPic = false;
			}
			playerCollider.get()->body->SetActive(false);
		}
		break;

		//jump
	case 'c':
		if (!inAir) {
			jumpNum = 0;
			if (getYVelocity() != 0) {
				playerCollider.get()->addForce(ofVec2f(0, getY()), -jumpForce);
			}
			jumpState = true; 	
		}
		break; 
	}

	


	if (key == 'a' && !climbingPaused) { 
		shooting = true;
		shootingTimer.Reset();
		shootingHandler->setShooting(true);
	}
	else if (key == 'A') {
		shooting = false;
		shootingHandler->setShooting(false);
		shootingHandler->resetDeltaTime();
	} 

	if (!ladder) { 
		climbingPaused = false;
	}
}



//KEY PRESSED
void Player::keyPressed(int key) {
	if (MultiPlayerManager::keyboard && GameManager::go) {
		switch (key) {

			//run right
		case 'd': {
			playerCollider.get()->body->SetActive(true);
			running = true;
			setVelocity(speed, getYVelocity());
			break;
		}

				  //run left
		case 'a': {
			playerCollider.get()->body->SetActive(true);
			running = true;
			setVelocity(-speed, getYVelocity());
			break;
		}
 


		case 'p':
			playerCollider.get()->body->SetActive(true);
			if (playerOne && pauseCount == 0) {
				GameManager::active = false;
				GameManager::paused = true;
				pauseCount++;
			}
			else {
				GameManager::active = true;
				GameManager::paused = false;
				pauseCount = 0;
			}
			break;


			//used for climbing
		case 'w':
			if (ladder && canClimb) {
				jumpState = false;
				climbing = true;
				if (climbing) {
					playerCollider.get()->body->SetActive(true);
					setVelocity(getXVelocity(), -speed / 1.6);
				}
			}
			break;

		case 's':
			if (ladder && canClimb) {
				jumpState = false;
				climbing = true;
				if (climbing) {
					playerCollider.get()->body->SetActive(true);
					playerCollider.get()->addForce(ofVec2f(0, 500), -1.7);
					setVelocity(getXVelocity(), speed / 1.6);
				}
			}
			break;


		}

		//jump
		if (key == 32) {
			if (!inAir && !ladder) {
				jumpState = true;
				jumpNum = 0;
				playerCollider.get()->addForce(ofVec2f(0, getY()), -jumpForce);
			}
		}

		else if (key == 'f' && !ladder) {
			shootingTimer.Reset();
			shooting = true;
			firingPosition = true;
			shootingHandler->setShooting(true);
		}

		if (!ladder) {
			climbingPaused = false;

		}
	}
}


//KEY RELEASED 
void Player::keyReleased(int key) {
	switch (key) {

		//run right 
	case 'd' : {
		running = false;
		setVelocity(0, getYVelocity());
		break;
	}

			  //run left
	case 'a': {
		running = false;
		setVelocity(0, getYVelocity());
		break;
	}
 

	case 'w' :
		if (ladder) {
			climbing = false;
			climbingPaused = true;
			climbingNum = 0;
			playerCollider.get()->body->SetActive(false);
		}
		break;

	case 's':
		if (ladder) {//
			climbing = false;
			climbingPaused = true;
			climbingNum = 0;
			playerCollider.get()->body->SetActive(false);
		}
		break;

	}

	//jump 
	if (key == 'f') {
		shooting = false;
		shootingNum = 0;
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
	if (ofGetFrameNum() % int(speed*3) == 0) {
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

void Player::spawnHandler() {
	if (ofGetFrameNum() % 10 == 0) {
		spawningNum++;
		spawningNum = spawningNum % spawnAnimation.size();
	}
}

void Player::dyingHandler() {
	if (ofGetFrameNum() % 12 == 0) {
		dyingNum++;
		dyingNum = dyingNum % dyingAnimation.size();
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
 

//Returns distance between 2 pts
double Player::distance(int x1, int x2, int y1, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int Player::getOrientation() {
	if (leftOriented) {
		return 1;
	}
	else {
		return 0;
	}
}
 

void Player::findClosestLadder() {
	double dist = 1000000; 
	double ladderD = 0;
	//find closest ladder
	for (int i = 0; i < Environment::ladders.size(); i++) { 
		ladderD = distance(getX(), Environment::ladders[i]->getX(), getY(), Environment::ladders[i]->getY());
		if (ladderD < dist) {
			dist = ladderD;
			eLadder = Environment::ladders[i];
		}
	}
	getLadderSpecs(eLadder); 
}

void Player::getLadderSpecs(Environment *e) {
	if (getY() >= (e->getY() - e->getHeight()/2) + getRadius() && getY() <= e->getY() + e->getHeight()) {
		canClimb = true;
	}
	else {
		canClimb = false;
	}
	if (getX() > e->getX() - e->getWidth() && getX() < e->getX() + e->getWidth()) {
		ladder = true;
	}
	else {
		ladder = false;
	}
}
void Player::applyDamage(int dmg){
    health -= dmg;
    if((health <= 0) && !dead){
        std::cout<<"Player died =("<<endl;
		dead = true; 
		justDied = true;
    }
}

int Player::getHealth(){
    return health;
}

void Player::isWin() {
	if (getX() - getRadius() >= 4108) { 
		win = true; 
	} 
}

