//
//  Camera.h
//  GameFinal
//
//  Created by Jfry on 11/29/18.
//

#ifndef Camera_h
#define Camera_h

#include <stdio.h>
#include "ofMain.h"
#include "Player.h"
using namespace std;
class Camera{
public:
    void setup();
    void update();
    Camera(vector<Player*> players);
private:
    ofCamera camera;
    vector<Player*> players;
};
#endif /* Camera_h */
