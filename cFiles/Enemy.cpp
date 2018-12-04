//
//  Enemy.cpp
//  GameFinal
//
//  Created by Jfry on 12/4/18.
//

#include "Enemy.h"
Enemy::Enemy(int x, int y, int range, int dir, int speed, string patrol_path, string hit_path, string bullet_path){
    this->x =x;
    this->y =y;
    this->range = range;
    this->dir = dir;
    this->patrol_path;
    this->hit_path = hit_path;
    this->bullet_path = bullet_path;
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
    shootingHandler = new ShootingHandler(this, 10, 8, 0.33, 9, bullet_anim);
}
void Enemy::update(){
    patrol();
}
void Enemy::draw(){
    
}
void Enemy::patrol(){
    
}
int Enemy::getX(){
    return x;
}
int Enemy::getY(){
    return y;
}
