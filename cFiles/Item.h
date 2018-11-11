//
//  Item.hpp
//  GameFinal
//
//  Created by Jfry on 11/10/18.
//

#ifndef Item_h
#define Item_h
#include "ofMain.h"
#include <stdio.h>
class Player; //foward declaration
class Item{
    
public:
    
    Item(int x, int y, int mass, int style, ofImage image);
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
    
private:
    ofImage image;
    int x, y, mass, style;
    bool hasPlayer;
    Player *parent;
};
#endif /* Item_h */
