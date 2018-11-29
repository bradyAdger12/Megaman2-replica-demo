//
//  Controller.h
//  GameFinal
//
//  Created by Jfry on 11/13/18.
//

#ifndef Controller_h
#define Controller_h
#include "ofMain.h"
#include <stdio.h>
#include <string>
class Controller{
public:
    Controller(string port, int baud);
    void update();
    void setup(); 
    char getI();
	static vector<Controller*> controllers; 
	ofSerial input;
private:
    
    char i;
};
#endif /* Controller_h */

