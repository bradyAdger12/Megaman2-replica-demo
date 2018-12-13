//
//  bullet.h
//  squareShooter
//
//  Created by Jfry on 10/18/18.
//

#ifndef Bullet_h
#define Bullet_h
#include "ofxBox2dCircle.h"
#include "ofxBox2d.h"
#include "collider.h"
class Bullet{
public:
    
    void update();
    void draw();
    int getX(), getY();
    double getX_(),getY_();
    Bullet();
    Bullet(int x, int y, int speed, int radius,int dir, vector<ofImage> images, string tag);
    Bullet(double x_, double y_, double dx,double dy, int radius,int dir, vector<ofImage> images, string tag);
    ~Bullet();
private:
    int x, y,speed, radius, dir, frame, anim_count;//dir = 0 left =1 right =2 toward nearest player
    vector<ofImage> images;
    double x_,y_,dx,dy;
    string tag;
    
    shared_ptr<ofxBox2dCircle> bullCollider;
    collider *ob; 

    
};


#endif /* bullet_h */
