//
//  MultiPlayerManager.cpp
//  GameFinal
//
//  Created by Jfry on 11/29/18.
//

#include "MultiPlayerManager.h"
void MultiPlayerManager::setup(){
}
void MultiPlayerManager::update(){
    for(int i=0; i<players.size(); i ++){
        players[i]->update();
    }
}
void MultiPlayerManager::draw(){
    for(int i=0; i<players.size(); i ++){
        players[i]->draw();
    }
}

void MultiPlayerManager::assignPorts(){
    vector <ofSerialDeviceInfo> deviceList = ports.getDeviceList();
    for(int i =0; i<1;i++){
        //ports.setup(deviceList[i].getDevicePath(), 9600);
//        if(ports.isInitialized()){
            availblePorts.push_back(deviceList[i].getDevicePath());
            //ports.close();
        //}
    }
    for(int i =0; i < availblePorts.size(); i++){
        cout<<"devicePort: "<<availblePorts[i]<<endl;
        players.push_back(new Player(availblePorts[i], 50 + i*20, ofGetHeight() - 100));
        players[i]->setup();
    }
}
MultiPlayerManager::MultiPlayerManager(){
    assignPorts();
}

