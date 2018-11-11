//
//  Item.c
//  GameFinal
//
//  Created by Jfry on 11/10/18.
//

#include "Item.h"
#include "Player.h"
Item::Item(string s, int x, int y, int mass, int style, ofImage image){
    this->x = x;
    this->y = y;
    this->mass = mass;
    this->style = style; //0 = throwable 1= consumable
    this->image = image;
	this->shape = s; 
	hasPlayer = false;
	

}

void Item::setup(){
	collide = new collider();
	it = collide->Circle(x, y, mass, 2, .2, 2.0);
	it.get()->setFixedRotation(true);
	scale = 5;
	tossForce = scale;
	multiplier = 1.35;
	maxTossForce = 22;
	count = 0;
}
void Item::update(){
	//keep item in bounds 
	
	if (it.get()->getPosition().x + it.get()->getRadius() >= ofGetWidth()) {
		it.get()->setVelocity(it.get()->getVelocity().x * -1, it.get()->getVelocity().y);
	}
	else if (it.get()->getPosition().x - it.get()->getRadius() <= 0) {
		it.get()->setVelocity(it.get()->getVelocity().x * -1, it.get()->getVelocity().y);
	}
	
		//a little messy. if item has player. bind to player in up right corner of collider. Arbitrary offset
		if (hasPlayer) { 
			it.get()->setPosition(parent->getX() + 15, parent->getY() - parent->radius - it.get()->getRadius() - 15); //change to x_Slot in future 
		}
	

		if (tossForce >= maxTossForce) {
			tossForce = maxTossForce;	
		}
	
	it.get()->update();
    
}
void Item::draw(){
    //draw item and rotate image
	ofSetColor(0);
	it.get()->draw();
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(it.get()->getPosition().x, it.get()->getPosition().y, 0);
	image.setAnchorPercent(0.5f, 0.5f);
	ofRotate(it.get()->getRotation());
	image.draw(0, 0, 50, 50);
	ofPopMatrix();
}

//Ability
void Item::use(){
    //abillity->trigger();
    cout << "Item_Used"<< endl;
}
void Item::toss(){ 
	cout << "Thrown from: (" << it.get()->getPosition() << ")" << endl;
	if (parent->leftOriented) {
		cout << "toss right" << endl;
		it.get()->addForce(ofVec2f(500, -150), tossForce);
	} 

	else {
		cout << "toss left" << endl;
		it.get()->addForce(ofVec2f(-500, -150), tossForce);
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

