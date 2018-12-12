//
//  Item.c
//  GameFinal
//
//  Created by Jfry on 11/10/18.
//

#include "Item.h"
#include "Player.h"
#include "ofApp.h" 
vector<Player*> Player::playerList;  
Item::Item(string type, int x, int y, int size, int style, int id){ 
    this->x = x;
    this->y = y;
    this->size = size;  
    this->image = image;  
	this->type = type;
	this->id = id;
	if(type == "coin") {
		coinNum = 0;
		for (int i = 1; i < 7; i++) {
			ofImage coin;
			coin.load("images/coinSheet/coin" + ofToString(i) + ".png");
			coinAnimation.push_back(coin);
		}
		
	}

	
} 

void Item::setup(){   
	dx = 0;
	dy = 1;
	contact = false;
}
void Item::update(){  
	 
	if (distance(MultiPlayerManager::players[0]->getX(), MultiPlayerManager::players[0]->getY()) <= MultiPlayerManager::players[0]->getRadius()) {
		contact = true;
		if (type == "coin") {
			MultiPlayerManager::players[0]->score += 250;
		}
	}

	else if (MultiPlayerManager::players.size() > 1) {
		if (distance(MultiPlayerManager::players[1]->getX(), MultiPlayerManager::players[1]->getY()) <= MultiPlayerManager::players[1]->getRadius()) {
			contact = true;
			if (type == "coin") {
				MultiPlayerManager::players[1]->score += 250;
			}
		}
	}
	else {
		contact = false;
		updateAnimation(7, coinAnimation);
	}
}
void Item::draw() { 
		ofSetColor(255); 
		coinAnimation[coinNum].draw(x,y,size,size);
		  
} 
  
int Item::getX(){
	return x;
}
int Item::getY(){
	return y;
}

int Item::getSize() {
	return size;
}

double Item::distance(int x1, int y1) {
	return sqrt(pow(x - x1, 2) + pow(y - y1, 2));
}

void Item::updateAnimation(int framerate, vector<ofImage> &im) {
	if (ofGetFrameNum() % framerate == 0) {
		coinNum++;
		coinNum = coinNum % im.size();
	}	
} 

 



