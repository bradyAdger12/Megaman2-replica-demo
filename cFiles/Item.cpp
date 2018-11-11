//
//  Item.c
//  GameFinal
//
//  Created by Jfry on 11/10/18.
//

#include "Item.h"
#include "Player.h"
Item::Item(int x, int y, int mass, int style, ofImage image){
    this->x = x;
    this->y = y;
    this->mass = mass;
    this->style = style; //0 = throwable 1= consumable
    this->image = image;
}

void Item::setup(){
    
}
void Item::update(){
    if(hasPlayer){
        x = parent->getX(); //change to x_Slot in future
        y = parent->getY();//change to y_Slot in future
    }else{
        //use physics
    }
}
void draw(){
    //image.draw(x,y);
}

//Ability
void Item::use(){
    //abillity->trigger();
    cout << "Item_Used"<< endl;
}
void Item::toss(){
    //add foward and rotational force
    hasPlayer = false;
}
void Item::setParent(Player *parent){
    this->parent = parent;
    hasPlayer = true;
}
bool Item::hasParent(){
    return parent;
}
int Item::getX(){
    return x;
}
int Item::getY(){
    return y;
}

