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
class Player; //foward declaration
class ShootingHandler{
public:
    void update();
    void draw();
    void deleteBullets();
    void shootingHandler();
    void resetDeltaTime();
    void setShooting(bool isShooting);
    //Need Constructor for enemy
     ShootingHandler(Player* player, int speed, int damage, float fireRate, int size,vector<ofImage> images);
    
private:
    int speed, damage, size;
    float deltaTime,lastTime,currentTime,fireRate;
    Player* player;
    vector<ofImage> images;
    vector<Bullet *> bullets;
    vector<Bullet *>::iterator bull;
    vector<int> indexesToDelete;
    bool isBullets, isShooting;
};

#endif /* ShootingHandler_h */
