#pragma once

#include "ofMain.h"
#include "ofxBox2dCircle.h"
#include "ofxBox2d.h"
#include "Item.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);   
		vector <shared_ptr<ofxBox2dCircle>> circles;
		ofImage background;
		ofImage soccerBall;
		ofImage block;
		ofImage block2;
		ofTrueTypeFont controlFont;
		static ofxBox2d world;
		
    vector<Item*> items;
    Item* closestUsableItem(int x, int y);
    void spawnRandomItem();
    double distance(int x1,int x2,int y1,int y2);
    //ofSerial serial;
    
};
