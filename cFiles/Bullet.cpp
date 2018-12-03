//
//  bullet.cpp
//  squareShooter
//
//  Created by Jfry on 10/18/18.
//

#include <stdio.h>
#include "ofMain.h"
#include "Bullet.h"
Bullet::Bullet(){
    
}
Bullet::~Bullet(){
    std::cout << "Deleting" << endl;
}
Bullet::Bullet(int x, int y, int speed, int radius, int dir, vector<ofImage>images){
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->radius = radius;
    this->dir = dir;
    this->images = images;
}

void Bullet::update(){
    y -= speed;
}
void Bullet::draw(){
    ofSetColor(255, 0, 0);
    ofDrawCircle(x,y,radius);
}
int Bullet::getX(){
    return x;
}
int Bullet::getY(){
    return y;
}
