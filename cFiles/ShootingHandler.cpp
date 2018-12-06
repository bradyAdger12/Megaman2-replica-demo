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
#include "math.h"
ShootingHandler::ShootingHandler(Player* player, int speed, int damage, float fireRate, int size,vector<ofImage> images){
    this->player = player;
    this->speed = speed;
    this->damage = damage;
    this->fireRate = fireRate;
    this->size = size;
    this->images = images;
    isPlayer = true;
    isShooting = false;
}
//Enemy Shooting handler Constuctor
ShootingHandler::ShootingHandler(Enemy* enemy, int speed, int damage, float fireRate, int size,vector<ofImage> images){
    this->enemy = enemy;
    this->speed = speed;
    this->damage = damage;
    this->fireRate = fireRate;
    this->size = size;
    this->images = images;
    isPlayer = false;
    isShooting = false;
}
void ShootingHandler::update(){
    currentTime = ofGetElapsedTimef();
    deltaTime += currentTime - lastTime;

    if(!isPlayer) getClosestPlayer();
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
        if(isPlayer){ //Shoot bullet in same direction as player Orientation
            if (player->getOrientation() == 1) {
                bullets.push_back(new Bullet(player->getX() + player->getRadius(), player->getY() - 2, 5, 3, player->getOrientation(), images));
            }
            else {
                bullets.push_back(new Bullet(player->getX() - player->getRadius(), player->getY() - 2, 5, 3, player->getOrientation(), images));
            }
        
        }else{ //Shoot bullet in path of closest player, if a player is in range
            bullets.push_back(new Bullet(enemy->getX(),enemy->getY(), player_XY[0], player_XY[1],size, 3, images));
            //std::cout<<"enemy shooting"<<endl;
        }
    }
    
    //Sending off screen bullets to the TRASH!
    if(isBullets && isPlayer){
        for(int i = 0; i < bullets.size(); i++){
            if(bullets[i]->getX() < player->getX() - 400|| bullets[i]->getX() > player->getX() + 400){
                indexesToDelete.push_back(i);
            }else{
                bullets[i]->update();
            }
        }
        deleteBullets();
    }else if(isBullets){
        for(int i = 0; i < bullets.size(); i++){
            if(bullets[i]->getX() < enemy->getX() - 200|| bullets[i]->getX() > enemy->getX() + 200){
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
void ShootingHandler::getClosestPlayer(){
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
  
    if(minDist > 400){
        isShooting = false;
        player_XY.clear();
    }else{
        isShooting = true;
        player_XY.clear();
        //Normalize vector of Enemy to closest player
        double dx_ = enemy->getX() - MultiPlayerManager::players[minPlayerIndex]->getX();
        double dy_ = enemy->getY() - MultiPlayerManager::players[minPlayerIndex]->getY();
        double mag = sqrt(pow(dx_,2) + pow(dy_,2));
        
        //std::cout<<mag<<" "<<(dx_/mag) * speed * -1<<" "<<(dy_/mag) * speed * -1<<endl;
        
        //Scale vector to bullet speed, player_XY is used when bullet is created in update
        player_XY.push_back((dx_/mag) * speed * -1);
        player_XY.push_back((dy_/mag) * speed * -1);
    }
}

