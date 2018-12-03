//
//  ShootingHandler.h
//  GameFinal
//
//  Created by Jfry on 12/2/18.
//

#ifndef ShootingHandler_h
#define ShootingHandler_h

#include <stdio.h>
#include "ofMain.h"
#include "Bullet.h"
#include "Player.h"
class ShootingHandler{
public:
    void update();
    void draw();
    void deleteBullets();
    void shootingHandler();
    void boundsControll();
    //Constructor for enemy
     ShootingHandler(Player* player, int speed, int damage, float fireRate, int size,vector<ofImage> images);
    
private:
    int speed, damage, size;
    float deltaTime,lastTime,currentTime,fireRate;
    Player* player;
    vector<ofImage> images;
    vector<Bullet *> bullets;
    vector<Bullet *>::iterator bull;
    vector<int> indexesToDelete;
    bool isBullets;
    bool shooting = false;
};

#endif /* ShootingHandler_h */
