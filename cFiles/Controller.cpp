//
//  Controller.cpp
//  GameFinal
//
//  Created by Jfry on 11/13/18.
//

#include "Controller.h"
Controller::Controller(string port, int baud){
    input.setup(port, baud);
	controllers.push_back(this);
}
void Controller::setup(){
    //input.listDevices();
}
void Controller::update(){
    if(input.available() > 0){
        i = input.readByte();
        //std::cout << i << endl;
    }
}
char Controller::getI(){
    return i;
}

