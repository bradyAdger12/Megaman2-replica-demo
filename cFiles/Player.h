#pragma once
#include "ofMain.h"
#include <string>
#include "Object.h"
#include "Bullet.h"
#include <vector>
#include <map>
using namespace std;

class Player {
	public:
		Player(string s, string c);
		float x, y, dx, dy, maxSpeed, gravity, time, delta, currentTime, fireRate, health, fallSpeed;
		bool inAir, jump, flipped = false;
		bool drop;
		bool fallDamage = true;
		int size, speed;
		string name;
		string character;
		vector<Bullet*> magazine;
		vector<Bullet*> bulletsToDelete;
		static map<string,Player*> playerMap;
		ofImage image; 
		ofSoundPlayer gunshot; 
		void setup();
		void update();
		void draw();
		void shoot();
		void reset();
		void deleteBullets();
		void collisionHandling();
		void _keyPressed(int key);
		void _keyReleased(int key);


};
