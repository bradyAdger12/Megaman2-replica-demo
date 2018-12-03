//
//  ShootingHandler.cpp
//  GameFinal
//
//  Created by Jfry on 12/2/18.
//

#include "ShootingHandler.h"
ShootingHandler::ShootingHandler(Player* player, int speed, int damage, float fireRate, int size,vector<ofImage> images){
    this->player = player;
    this->speed = speed;
    this->damage = damage;
    this->fireRate = fireRate;
    this->size = size;
    this->images = images;
    
}
void ShootingHandler::update(){
    currentTime = ofGetElapsedTimef();
    deltaTime += currentTime - lastTime;
    
    shootingHandler();
    boundsControll();
    
    lastTime = currentTime;
}
void ShootingHandler::draw(){
    if(bullets.size() != 0){
        for(bull = bullets.begin(); bull != bullets.end(); bull++){
            (*bull)->draw();
        }
    }
}
void ShootingHandler::shootingHandler(){
    if(shooting && deltaTime >= fireRate){
        deltaTime = 0.0f;
        //int x, int y, int speed, int radius, int dir, vector<ofImage>images
        bullets.push_back(new Bullet(player->getX() + size/2,player->getY(), 20, 8, player->getOrientation(), images));
    }
    
    //Sending off screen bullets to the TRASH!
    if(isBullets){
        for(int i = 0; i < bullets.size(); i++){
            if(bullets[i]->getY() < 0 || bullets[i]->getY() > 2000 || bullets[i]->getX() < 0 || bullets[i]->getX() > 4355){
                indexesToDelete.push_back(i);
            }else{
                bullets[i]->update();
            }
        }
        deleteBullets();
    }
}
void ShootingHandler::deleteBullets(){
    for(int i = 0; i < indexesToDelete.size(); i++){
        delete bullets[indexesToDelete[i]];
        bullets.erase(bullets.begin() + indexesToDelete[i]);
    }
    indexesToDelete.clear();
}
