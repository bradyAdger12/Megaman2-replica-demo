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
    for(int i =0; i<deviceList.size();i++){
        if(ports.setup(deviceList[i].getDevicePath(), 9600)){
            std::size_t found = deviceList[i].getDevicePath().find("Blue");
            if(found==std::string::npos){ //if string path doesnt contain BLUE for bluetooth
                if(i>0){
                    bool dupplicate = false;
                    for(int p = 0;p < availblePorts.size();p++){
                        if(deviceList[i].getDevicePath() == availblePorts[p]){
                            dupplicate = true;
                        }
                    }
                    if(!dupplicate){
                        found = deviceList[i].getDevicePath().find("cu");
                        if(found==std::string::npos){
                            availblePorts.push_back(deviceList[i].getDevicePath());
                        }
                    }
                }else{
                    availblePorts.push_back(deviceList[i].getDevicePath());
                }
            }
            ports.close();
        }
    }
    cout << "ConnectedPorts: " << availblePorts.size() << endl;;
    for(int i =0; i < availblePorts.size(); i++){
        cout << "devicePort: " << availblePorts[i] << endl;
        //setup player and its controller. delete controller so that menu has access to port
        Player *p;
        p = new Player(availblePorts[i], 50, 1150, isPlayerOne);
        isPlayerOne = false;
//        ofApp::collisionObjects.insert(make_pair(this, "player" + ofToString(i+1)));
        p->setup();
        players.push_back(p);
    }
    }else {
        Player *p;
        //test player spawn
        //p = new Player("COM3", 1737, 870, isPlayerOne);
        //starting spawn
        p = new Player("COM3", 50, 1150, isPlayerOne);
//        ofApp::collisionObjects.insert(make_pair(this, "player1"));
        p->setup();
        players.push_back(p);
    }
}
MultiPlayerManager::MultiPlayerManager(bool keyboard){ 
		this->keyboard = keyboard;	
		assignPorts();
}

