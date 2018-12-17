//
//  Enemy.cpp
//  GameFinal
//
//  Created by Jfry on 12/4/18.
//

#include "Enemy.h"
#include "ofApp.h"
Enemy::Enemy(double x, double y, double range, int dir, double speed, string patrol_path, string hit_path, string bullet_path){
    this->x =x;
    this->y =y;
    this->range = range;
    this->dir = dir;
    this->speed = speed;
    this->patrol_path= patrol_path;
    this->hit_path = hit_path;
    this->bullet_path = bullet_path;
    this->y_start = y;
    this->frame = 0;
    this->patrol_count =0;
    this->health = 100;
    this->hit = false; 
    string file = "images/spider_bullet.png";
            ofImage bull;
            bull.load(file);
    bullet_anim.push_back(bull);
    //ShootingHandler(Enemy* enemy, int speed, int damage, float fireRate, int size, vector<ofImage> images);
    shootingHandler = new ShootingHandler(this, 2, 8, 3.0, 4, bullet_anim);//Move to bottom of setup after animations are built. 
	
   
}
void Enemy::setup(){
    //computer centers
	centerX = x + (20/2);
	centerY = y + (40/2) - 3;
    
    //load Patrol animation
    for (int i = 0; i < 4; i++) {
        string file = patrol_path + ofToString(i) + ".png";
        std::cout<<file<<endl;
        ofImage pat;
        pat.load(file);
        patrol_anim.push_back(pat);
    }
//
//    //load hit animation
//    for (int i = 2; i < 3; i++) {
//        string file = hit_path + ofToString(i) + ".png";
//        ofImage hit;
//        hit.load(file);
//        hit_anim.push_back(hit);
//    }
    
//    //load bullet animation
//    for (int i = 2; i < 3; i++) {
//        string file = bullet_path + ofToString(i) + ".png";
//        ofImage bull;
//        bull.load(file);
//        bullet_anim.push_back(bull);
//    }
    //:ShootingHandler(Enemy* enemy, int speed, int damage, float fireRate, int size,vector<ofImage> images){
}
void Enemy::update(){ //Cycle animations in here
    if (GameManager::go) {
        if(hit){
            hit = false;
            ofSetColor(255, 0, 0, 150);
        }
        patrol();
        shootingHandler->update();
        frame ++;
        if(frame%10 ==0){
            patrol_count ++;
        } 
    }
}
void Enemy::draw(){ 
	if (GameManager::go) {
		int index = patrol_count % patrol_anim.size();
		patrol_anim[index].getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		patrol_anim[index].draw(x, y, 20, 40);
		shootingHandler->draw();
		
	}
}
void Enemy::patrol(){ //Move up and down.
    switch(dir){
        case 0: //up
            if(y > y_start - range){
                y -= speed;
				centerY -= speed;
            }else{
                dir = 1;
            }
            break;
        case 1: //down
            if(y < y_start + range){
                y += speed;
				centerY += speed;
            }else{
                dir = 0;
            }
            break;
        default:

            break;
    }
}
double Enemy::getX(){
    return x;
}
double Enemy::getY(){
    return y;
}
double Enemy::getCX() {
	return centerX;
}
double Enemy::getCY() {
	return centerY;
}
int Enemy::getHealth(){
    return health;
}
void Enemy::applyDamage(int dmg){ //On Collision with player Bullet
    health -= dmg;
    if(health <= 0){
        die();
    }
}
void Enemy::isHit(bool hit){
    this->hit = hit;
}
void Enemy::die(){
    //delete this;
    //Begin deat
}
