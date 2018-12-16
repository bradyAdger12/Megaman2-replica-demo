//
//  ShootingHandler.cpp
//  GameFinal
//
//  Created by Jfry on 12/2/18.
//
#include "Player.h" 
#include "ShootingHandler.h"
#include "MultiPlayerManager.h"
#include "math.h"
#include "Enemy.h" 
#include "ofApp.h"
ShootingHandler::ShootingHandler(Player* player, int speed, int damage, float fireRate, int size,vector<ofImage> images){
    this->player = player;
    this->speed = speed;
    this->damage = damage;
    this->fireRate = fireRate;
    this->size = size;
    this->images = images;
    isPlayer = true;
    isShooting = false;
	playerIndex++;
	//load blaster sound
	blaster.load("sounds/Blaster.wav");
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

	//check for enemy/player bullet collisions
	checkCollisions();


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

//Checks if player/enemy is shooting and if so creates/destroys bullets
void ShootingHandler::shootingHandler(){
    if(deltaTime >= fireRate && isShooting){
        deltaTime = 0.0f;
        if(isPlayer){ //Shoot bullet in same direction as player Orientation
			blaster.play();
            if (player->getOrientation() == 1) {
                bullets.push_back(new Bullet(player->getX() + player->getRadius(), player->getY() - 6, speed, size, player->getOrientation(), images, "p_bull"));
            }
            else {
                bullets.push_back(new Bullet(player->getX() - player->getRadius(), player->getY() - 6, speed, size, player->getOrientation(), images, "p_bull"));
            }
        
        }else{ //Shoot bullet in path of closest player, if a player is in range 
			bullets.push_back(new Bullet(enemy->getX(), enemy->getY(), player_XY[0], player_XY[1], size, 3, images, "e_bull"));
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
            if(bullets[i]->getX_() < enemy->getX() - 200|| bullets[i]->getX_() > enemy->getX() + 200){
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
  
    if(minDist > 200){
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

void ShootingHandler::checkCollisions() {
	bool playerHit = false;
	bool enemyHit = false;
	for (int i = 0; i < bullets.size(); i++) { 
			double dist = sqrt(pow(MultiPlayerManager::players[0]->getX() - bullets[i]->getX_(), 2) + pow(MultiPlayerManager::players[0]->getY() - bullets[i]->getY_(), 2));
			if (MultiPlayerManager::players.size() > 1) {
			     double distp2 = sqrt(pow(MultiPlayerManager::players[1]->getX() - bullets[i]->getX_(), 2) + pow(MultiPlayerManager::players[1]->getY() - bullets[i]->getY_(), 2));
				 if (distp2 <= MultiPlayerManager::players[1]->getRadius() && !playerHit) {
					playerHit = true;
					MultiPlayerManager::players[1]->applyDamage(20);
					indexesToDelete.push_back(i);
				 }
			} 
			if (dist <= MultiPlayerManager::players[0]->getRadius() && !playerHit) {
				playerHit = true;
				MultiPlayerManager::players[0]->applyDamage(20);
				indexesToDelete.push_back(i);
			}
			

		

		for (int e = 0; e < ofApp::enemies.size(); e++) {
			double dist2 = sqrt(pow(ofApp::enemies[e]->getCX() - bullets[i]->getX(), 2) + pow(ofApp::enemies[e]->getCY() - bullets[i]->getY(), 2));
			if (dist2 <= 10 && !enemyHit) {
				enemyHit = true;
				ofApp::enemies[e]->applyDamage(100);
				indexesToDelete.push_back(i);
				if (MultiPlayerManager::players.size() == 1) { 
					MultiPlayerManager::players[0]->score += 500;
				}
				else {
					if (player->playerOne) {
						MultiPlayerManager::players[0]->score += 500;
					}
					else {
						MultiPlayerManager::players[1]->score += 500;
					}
				}
			}
		}
	}
}


