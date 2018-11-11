//
//  Item.hpp
//  GameFinal
//
//  Created by Jfry on 11/10/18.
//

#ifndef Item_h
#define Item_h
#include "ofMain.h"
#include "collider.h"
#include <stdio.h>
#include "ofxBox2dCircle.h"
class Player; //foward declaration
class Item{
    
public:
    
    Item(string shape, int x, int y, int mass, int style, ofImage image);
    void setup();
    void update();
    void draw();
    
    //Ability
    void use();
    void toss();
    void setParent(Player *parent);
    bool hasParent();
    int getX();
    int getY();
	int style;

	
    
private:
    ofImage image;
	string shape;
    int x, y, mass, tossForce;
    bool hasPlayer;
    Player *parent;
	//collider
	collider *collide;
	shared_ptr<ofxBox2dCircle> it;
};
#endif /* Item_h */
