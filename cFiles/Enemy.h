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
    Enemy(double x, double y, double range, int dir, double speed, string patrol_path, string hit_path, string bullet_path);
    void patrol(), applyDamage(int dmg);
    double getX(), getY();
    
private:
    int dir, health;
    double x,y,range,speed;
    double y_start;
	vector<ofImage> patrol_anim;
	vector<ofImage> hit_anim;
	vector<ofImage> bullet_anim;
	string patrol_path, hit_path, bullet_path;
	ShootingHandler* shootingHandler;
   
};
#endif /* Enemy_h */
