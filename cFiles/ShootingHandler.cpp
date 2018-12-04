//
//  ShootingHandler.cpp
//  GameFinal
//
//  Created by Jfry on 12/2/18.
//
#include "Player.h"
#include "Enemy.h"
#include "ShootingHandler.h"
#include "MultiPlayerManager.h"
#include "Math.h"
ShootingHandler::ShootingHandler(Player* player, int speed, int damage, float fireRate, int size,vector<ofImage> images){
    this->player = player;
    this->speed = speed;
    this->damage = damage;
    this->fireRate = fireRate;
    this->size = size;
    this->images = images;
    isPlayer = true;
}
ShootingHandler::ShootingHandler(Enemy* enemy, int speed, int damage, float fireRate, int size,vector<ofImage> images){
    this->enemy = enemy;
    this->speed = speed;
    this->damage = damage;
    this->fireRate = fireRate;
    this->size = size;
    this->images = images;
    isPlayer = false;
}
void ShootingHandler::update(){
    currentTime = ofGetElapsedTimef();
    deltaTime += currentTime - lastTime;

    shootingHandler();
    
    lastTime = currentTime;
}
void ShootingHandler::draw(){
    if(bullets.size() != 0){
        isBullets = true;
        for(bull = bullets.begin(); bull != bullets.end(); bull++){
            (*bull)->draw();
        }
    }else{
        isBullets = false;
    }
}
void ShootingHandler::shootingHandler(){
    if(deltaTime >= fireRate && isShooting){
        deltaTime = 0.0f;
        //int x, int y, int speed, int radius, int dir, vector<ofImage>images
        if(isPlayer){
            bullets.push_back(new Bullet(player->getX(),player->getY(), 5, 3, player->getOrientation(), images));
        }else{
            
        }
    }
    
    //Sending off screen bullets to the TRASH!
    if(isBullets){
        for(int i = 0; i < bullets.size(); i++){
            if(bullets[i]->getX() < player->getX() - 400|| bullets[i]->getX() > player->getX() + 400){
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

void ShootingHandler::resetDeltaTime(){
    deltaTime = 0.0f;
    lastTime = 0.0f;
}
void ShootingHandler::setShooting(bool isShooting){
    this->isShooting = isShooting;
}
vector<int> ShootingHandler::getClosestPlayer(){
    vector<int> player_XY;
    double currentDist;
    double minDist = 99999;
    int minPlayerIndex = 0;
    for(int i =0; i< MultiPlayerManager::players.size(); i++){
        currentDist = sqrt(pow(enemy->getX()-MultiPlayerManager::players[i]->getX(),2) + pow(enemy->getY()- MultiPlayerManager::players[i]->getY(),2));
        if(currentDist < minDist){
            minDist = currentDist;
            minPlayerIndex = i;
        }
    }
    
    player_XY.push_back(MultiPlayerManager::players[minPlayerIndex]->getX());
    player_XY.push_back(MultiPlayerManager::players[minPlayerIndex]->getY());
    return player_XY;
}
