//
//  MultiPlayerManager.h
//  GameFinal
//
//  Created by Jfry on 11/29/18.
//

#ifndef MultiPlayerManager_h
#define MultiPlayerManager_h

#include <stdio.h>
#include "ofMain.h"
#include "Player.h"
using namespace std;
class MultiPlayerManager{
public:
    MultiPlayerManager();
    void assignPorts();
    void setup();
    void update();
    void draw();
    int getPlayerXAvg();
    int getPlayerYAvg();

private:
    ofSerial ports;
    vector<Player*> players;
    vector<string> availblePorts;
};
#endif /* MultiPlayerManager_h */
