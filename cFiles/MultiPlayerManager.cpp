//
//  MultiPlayerManager.cpp
//  GameFinal
//
//  Created by Jfry on 11/29/18.
//

#include "MultiPlayerManager.h" 
#include "GameManager.h" 
#include "ofApp.h"
vector<Player*> MultiPlayerManager::players; 
bool MultiPlayerManager::keyboard;
void MultiPlayerManager::setup(){
	initialize = true;
	isPlayerOne = true;

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
	if (!keyboard) {
		vector <ofSerialDeviceInfo> deviceList = ports.getDeviceList();
		for (int i = 0; i < deviceList.size(); i++) {
			if (ports.setup(deviceList[i].getDevicePath(), 9600)) {
				availblePorts.push_back(deviceList[i].getDevicePath());
				ports.close();
			}
		}
		for (int i = 0; i < availblePorts.size(); i++) {
			cout << "devicePort: " << availblePorts[i] << endl; 
			Player *p;
			p = new Player(availblePorts[i], 50, 1150 + (i * 50), isPlayerOne);
			isPlayerOne = false;
			ofApp::collisionObjects.insert(make_pair(this, "player" + ofToString(i + 1)));
			p->setup();
			players.push_back(p);
		}
	}
	else {
		Player *p;
		//test player spawn
		//p = new Player("COM3", 1737, 870, isPlayerOne);
		//starting spawn
		p = new Player("COM3", 50, 1150, isPlayerOne);
		ofApp::collisionObjects.insert(make_pair(this, "player1"));
		p->setup();
		players.push_back(p);
	}
  
}
MultiPlayerManager::MultiPlayerManager(bool keyboard){ 
		this->keyboard = keyboard;	
		assignPorts();
}
