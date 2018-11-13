//
//  Item.c
//  GameFinal
//
//  Created by Jfry on 11/10/18.
//

#include "Item.h"
#include "Player.h"
#include "ofApp.h" 
Item::Item(string shape, int x, int y, int size, int style, ofImage image){

    this->x = x;
    this->y = y;
    this->size = size;
	this->shape = shape;
    this->style = style; //0 = throwable 1= consumable
    this->image = image; 
	density = size / 2.1;
	hasPlayer = false;   
	if (shape == "circle") {
		it = collide->Circle(x, y, size, density, .2, .5);
		it.get()->setFixedRotation(true);
	}
	if(shape == "square") { 
		size *= 2;
		it = collide->Rectangle(x, y, size, size, density, .2, .5);
		it.get()->setFixedRotation(true);
	}
} 

void Item::setup(){
	scale = 5;
	tossForce = scale;
	multiplier = 1.25;
	maxTossForce = 70;
	count = 0;
}
void Item::update(){

	//if alive, update item 
	if (it.get()->alive) {
		if (it.get()->getPosition().x + size >= ofGetWidth()) {
			it.get()->setVelocity(it.get()->getVelocity().x * -1, it.get()->getVelocity().y);
			//added this second if statement to respawn object if it gets off screen
			if (it.get()->getPosition().x >= ofGetWidth()) {
				it.get()->setPosition(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
			}
		}
		else if (it.get()->getPosition().x - size <= 0) {
			it.get()->setVelocity(it.get()->getVelocity().x * -1, it.get()->getVelocity().y);
			//added this second if statement to respawn object if it gets off screen
			if (it.get()->getPosition().x + size / 2 <= 0) {
				it.get()->setPosition(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
			}
		} 
		it.get()->update();
	}
	
		//if player has item. destroy collider until player throws item
		if (hasPlayer) { 
			it.get()->destroy(); 
			//it.get()->setPosition(parent->getX() + parent->radius, parent->getY()); //change to x_Slot in future 	
		}
    
}
void Item::draw(){
    //draw item and rotate image 
	if (it.get()->alive) {
		ofSetColor(0);
		it.get()->draw();
		ofSetColor(255);
		ofPushMatrix();
		ofTranslate(it.get()->getPosition().x, it.get()->getPosition().y, 0);
		image.setAnchorPercent(0.5f, 0.5f);
		ofRotate(it.get()->getRotation());
		image.draw(0, 0, size * 2, size * 2);
		ofPopMatrix();
	}


	//draw the item image when player is holding the item
	else {
		if (parent->leftOriented) {
			image.draw(parent->getX() + parent->radius - 15, parent->getY() + 15, size * 2, size * 2);
		}
		else {
			image.draw(parent->getX() - parent->radius + 20, parent->getY() + 15, size * 2, size * 2);
		}
	} 
}

//Ability
void Item::use(){
    //abillity->trigger();
    cout << "Item_Used"<< endl;
}
 
void Item::toss(){ 
	recreateCollider(); 
	cout << "Thrown from: (" << it.get()->getPosition() << ")" << endl;
	if (parent->leftOriented) {
		cout << "toss right" << endl;
		it.get()->addForce(ofVec2f(300, -300), tossForce);
	} 

	else {
		cout << "toss left" << endl;
		it.get()->addForce(ofVec2f(-300, -300), tossForce);
	}
    hasPlayer = false;
	tossForce = scale;
	count = 0;

}
void Item::setParent(Player *parent){
    this->parent = parent;
    hasPlayer = true;
}
bool Item::hasParent(){
    return hasPlayer;
}
int Item::getX(){
    return it.get()->getPosition().x;
}
int Item::getY(){
    return it.get()->getPosition().y;

}


//used to recreate collider when player throws an item
void Item::recreateCollider() {
	if (shape == "circle") { 
		
		//track player orientation so that collider spawns in correct spot
		if (parent->leftOriented) {
			it = collide->Circle(parent->getX() + parent->radius, parent->getY(), size, density, .2, .5);
		}
		else {
			it = collide->Circle(parent->getX() - parent->radius, parent->getY(), size, density, .2, .5);
		}
		it.get()->setFixedRotation(true);
	}
	if (shape == "square") { 
		
		//track player orientation so that collider spawns in correct spot
		if (parent->leftOriented) {
			it = collide->Rectangle(parent->getX() + parent->radius, parent->getY(), size * 2, size * 2, density/1.2, .2, .5);
		}
		else { 
			it = collide->Rectangle(parent->getX() - parent->radius, parent->getY(), size * 2, size * 2, density/1.2, .2, .5);
		}
		it.get()->setFixedRotation(true);
	}
}



