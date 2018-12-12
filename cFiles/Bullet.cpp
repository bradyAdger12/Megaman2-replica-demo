//
//  bullet.cpp
//  squareShooter
//
//  Created by Jfry on 10/18/18.
//

#include <stdio.h>
#include "ofMain.h"
#include "Bullet.h"
#include "ofApp.h"
Bullet::Bullet(){
    
}
Bullet::~Bullet(){
    //std::cout << "Deleting" << endl;
}
Bullet::Bullet(int x, int y, int speed, int radius, int dir, vector<ofImage>images, string tag){
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->radius = radius;
    this->dir = dir;
    this->images = images;
    this->tag = tag;
    
    //create collider
    ob = new collider();
    bullCollider = ob->Circle(x + radius /2, y + radius /2, radius/2, 0, 0, 0);
    bullCollider->setData(this);
    ofApp::collisionObjects.insert(make_pair(this, tag));
}
Bullet::Bullet(double x_, double y_, double dx,double dy, int radius, int dir, vector<ofImage>images, string tag){
    this->x_ = x_;
    this->y_ = y_;
    this->dx = dx;
    this->dy = dy;
    this->radius = radius;
    this->dir = dir;
    this->images = images;
    this->tag = tag;
    //std::cout<<"Bullet Made"<<endl;

    //create collider
    ob = new collider();
    bullCollider = ob->Circle(x_ + radius /2,y_ + radius /2, radius/2, 0, 0, 0);
    bullCollider->setData(this);
    ofApp::collisionObjects.insert(make_pair(this, tag));
}

void Bullet::update(){
    frame ++;
    if(frame%5 == 0){
        anim_count ++;
    }
    switch(dir){
        case 0:
            x -= speed;
            bullCollider.get()->update();
            bullCollider.get()->setPosition(x + radius /2, y + radius /2);
            break;
        case 1:
            x += speed;
            bullCollider.get()->update();
            bullCollider.get()->setPosition(x + radius /2, y + radius /2);
            break;
        case 3:
            x_ += dx;
            y_ += dy;
            bullCollider.get()->update();
            bullCollider.get()->setPosition(x_ + radius /2, y_ + radius/2);
            break;
//        default:
//            break;
    }
}
void Bullet::draw(){
    switch(dir){
        case 3:
            images[0].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
            images[0].draw(x_, y_, radius, radius);
            break;
        default:
            int index = anim_count%images.size();
            images[index].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
            images[index].draw(x, y, radius, radius);
            break;
    }
//        ofSetColor(0, 0, 0, 150);
//        bullCollider.get()->draw();
}
int Bullet::getX(){
    return x;
}
int Bullet::getY(){
    return y;
}
double Bullet::getX_() {
    return x_;
}

double Bullet::getY_() {
    return y_;
}

