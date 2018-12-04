#pragma once

#include "ofMain.h"
#include "ofxBox2dCircle.h"
#include "ofxBox2d.h"
#include "Item.h"
#include "MultiPlayerManager.h"
#include "Environment.h"
using namespace std;
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
		//string getObjectType(void* data);

		// this is the function for contacts
		void contactStart(ofxBox2dContactArgs &e);
		void contactEnd(ofxBox2dContactArgs &e);

		vector <shared_ptr<ofxBox2dCircle>> circles;
		ofImage background;
		ofImage menuBackground;
		ofImage soccerBall;
		ofImage block;  
		ofSoundPlayer TitleScreenMusic;
		ofSoundPlayer inGameSound;
		static ofxBox2d world;   
		ofEasyCam camera;
		static map<void*, string> collisionObjects;
		ifstream input;
		static vector<Environment*> eList;
		map<void*, string>::iterator itr;
		MultiPlayerManager *mpm;
		
	static vector<Item*> items;

    void spawnRandomItem();
    double distance(int x1,int x2,int y1,int y2);   

};
