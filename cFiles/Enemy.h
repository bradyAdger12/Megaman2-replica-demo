//
//  Enemy.hpp
//  GameFinal
//
//  Created by Jfry on 12/4/18.
//

#ifndef Enemy_h
#define Enemy_h

#include "ShootingHandler.h"
#include "ofMain.h"
#include "ofxBox2dCircle.h"
#include "ofxBox2d.h"
#include "collider.h"
#include <stdio.h>

using namespace std;
class Enemy{
public:
    void setup();
    void update();
    void draw();
    void isHit(bool hit), die();
    Enemy(double x, double y, double range, int dir, double speed, string patrol_path, string hit_path, string bullet_path);
    void patrol(), applyDamage(int dmg);
    double getX(), getY(), getCX(), getCY();
    int getHealth();
    
private:
    int dir, health, frame, patrol_count;
    double x,y,range,speed,centerX,centerY;
    double y_start;
    bool hit;
    vector<ofImage> patrol_anim;
    vector<ofImage> hit_anim;
    vector<ofImage> bullet_anim;
    string patrol_path, hit_path, bullet_path;
    shared_ptr<ofxBox2dCircle> enemyCollider;
    collider *ob;
    
    ShootingHandler* shootingHandler;
};
#endif /* Enemy_h */
