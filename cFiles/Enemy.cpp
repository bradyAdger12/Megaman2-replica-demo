//
//  Enemy.cpp
//  GameFinal
//
//  Created by Jfry on 12/4/18.
//

#include "Enemy.h"
Enemy::Enemy(double x, double y, double range, int dir, double speed, string patrol_path, string hit_path, string bullet_path){
    this->x =x;
    this->y =y;
    this->range = range;
    this->dir = dir;
    this->speed = speed;
    this->patrol_path;
    this->hit_path = hit_path;
    this->bullet_path = bullet_path;
    this->y_start = y;
    //ShootingHandler(Enemy* enemy, int speed, int damage, float fireRate, int size, vector<ofImage> images);
    shootingHandler = new ShootingHandler(this, 3, 8, 0.66, 4, bullet_anim);//Move to bottom of setup after animations are built.

}
void Enemy::setup(){
    //Build Animation Vectors
    
    //load Patrol animation
    for (int i = 2; i < 3; i++) {
        string file = patrol_path + ofToString(i) + ".png";
        ofImage pat;
        pat.load(file);
        patrol_anim.push_back(pat);
    }
    
    //load hit animation
    for (int i = 2; i < 3; i++) {
        string file = hit_path + ofToString(i) + ".png";
        ofImage hit;
        hit.load(file);
        hit_anim.push_back(hit);
    }
    
    //load bullet animation
    for (int i = 2; i < 3; i++) {
        string file = bullet_path + ofToString(i) + ".png";
        ofImage bull;
        bull.load(file);
        bullet_anim.push_back(bull);
    }
    //:ShootingHandler(Enemy* enemy, int speed, int damage, float fireRate, int size,vector<ofImage> images){
}
void Enemy::update(){ //Cycle animations in here
    patrol();
    shootingHandler->update();
}
void Enemy::draw(){
    ofSetColor(0,0,0);
    ofDrawRectangle(x,y, 20,20);
    shootingHandler->draw();
}
void Enemy::patrol(){ //Move up and down.
    switch(dir){
        case 0: //up
            if(y > y_start - range){
                y -= speed;
            }else{
                dir = 1;
            }
            break;
        case 1: //down
            if(y < y_start + range){
                y += speed;
            }else{
                dir = 0;
            }
            break;
        default:

            break;
    }
}
int Enemy::getX(){
    return x;
}
int Enemy::getY(){
    return y;
}
void Enemy::applyDamage(int dmg){ //On Collision with player Bullet
    health -= dmg;
}
//void Enenmy::die(){}
