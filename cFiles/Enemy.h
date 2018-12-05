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
#include <stdio.h>

using namespace std;
class Enemy{
public:
    void setup();
    void update();
    void draw();
    Enemy(double x, double y, int range, int dir, int speed, string patrol_path, string hit_path, string bullet_path);
    void patrol();
    int getX(), getY();
    
    
private:
    int range,dir, speed;
    double x,y;
    vector<ofImage> patrol_anim;
    vector<ofImage> hit_anim;
    vector<ofImage> bullet_anim;
    string patrol_path, hit_path, bullet_path;
    
    ShootingHandler* shootingHandler;
};
#endif /* Enemy_h */
