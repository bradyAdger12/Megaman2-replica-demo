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
    double total_x;
    double total_y;
    for(int i =0; i < players.size(); i++){
        total_x += player[i]->getX();
        total_y += player[i]->getY();
    }
    double avgX = total_x/players.size();
    double avgY = total_y/players.size();
    
}
