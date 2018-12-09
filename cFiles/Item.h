//
//  Item.hpp
//  GameFinal
//
//  Created by Jfry on 11/10/18.
//

#ifndef Item_h
#define Item_h
#include "ofMain.h"
#include "collider.h"
#include <stdio.h>
#include "ofxBox2dCircle.h"
#include "ofxBox2dRect.h"
#include "GameManager.h"
class Player; //foward declaration
using namespace std;
class Item{
    
public:
    
    Item(string shape, int x, int y, int size, int style, int id); 
    void setup();
    void update();
    void draw(); 
	int dx;
	int dy;
	int id;
	bool contact;
    int getX();
    int getY();
	int getSize();
	int style;
	void updateAnimation(int frameRate, vector<ofImage> &im);   
	double distance(int x1,int y1);
	int density;

	
	
	

private:
	//coin animation
	vector<ofImage> coinAnimation;
	int coinNum;
    ofImage image; 
	string type;
	int x, y, size;
	ofColor color;  
	 
};
#endif /* Item_h */

