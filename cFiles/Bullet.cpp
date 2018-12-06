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
    //std::cout << "Deleting" << endl;
}
Bullet::Bullet(int x, int y, int speed, int radius, int dir, vector<ofImage>images){
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->radius = radius;
    this->dir = dir;
    this->images = images;
}
Bullet::Bullet(double x_, double y_, double dx,double dy, int radius, int dir, vector<ofImage>images){
    this->x_ = x_;
    this->y_ = y_;
    this->dx = dx;
    this->dy = dy;
    this->radius = radius;
    this->dir = dir;
    this->images = images;
    //std::cout<<"Bullet Made"<<endl;
}
void Bullet::update(){
    switch(dir){
        case 0:
            x -= speed;
            break;
        case 1:
            x += speed;
            break;
        case 3:
            x_ += dx;
            y_ += dy;
            break;
        default:
            break;
    }
}
void Bullet::draw(){
    switch(dir){
        case 3:
            ofSetColor(0, 0, 0);
            ofDrawCircle(x_,y_,radius);
            break;
        default:
            ofSetColor(0, 0, 0);
            ofDrawCircle(x,y,radius);
            break;
    }
}
int Bullet::getX(){
    return x;
}
int Bullet::getY(){
    return y;
}
