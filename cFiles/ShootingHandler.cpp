//
//  ShootingHandler.cpp
//  GameFinal
//
//  Created by Jfry on 12/2/18.
//
#include "Player.h"
#include "ShootingHandler.h"
ShootingHandler::ShootingHandler(Player* player, int speed, int damage, float fireRate, int size,vector<ofImage> images){
    this->player = player;
    this->speed = speed;
    this->damage = damage;
    this->fireRate = fireRate;
    this->size = size;
    this->images = images;
	isShooting = false;
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
		if (player->getOrientation() == 1) {
			bullets.push_back(new Bullet(player->getX() + player->getRadius(), player->getY() - 2, 5, 3, player->getOrientation(), images));
		}
		else {
			bullets.push_back(new Bullet(player->getX() - player->getRadius(), player->getY() - 2, 5, 3, player->getOrientation(), images));
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
