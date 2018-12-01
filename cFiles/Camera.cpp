//
//  Camera.cpp
//  GameFinal
//
//  Created by Jfry on 11/29/18.
//

#include "Camera.h"
Camera::Camera(vector<Player*> players){
    this->players = players;
}
void Camera::setup(){
    camera.begin();
}
void Camera::update(){
    float total_x;
    float total_y;
    for(int i =0; i < players.size(); i++){
        total_x += players[i]->getX();
        total_y += players[i]->getY();
    }
    float avgX = total_x/players.size();
    float avgY = total_y/players.size();
    
    camera.move(avgX, avgY, 0);
}
