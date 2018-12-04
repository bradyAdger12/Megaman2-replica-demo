//
//  bullet.h
//  squareShooter
//
//  Created by Jfry on 10/18/18.
//

#ifndef Bullet_h
#define Bullet_h
class Bullet{
public:
    
    void update();
    void draw();
    int getX(), getY();
    Bullet();
    Bullet(int x, int y, int speed, int radius,int dir, vector<ofImage> images);
    Bullet(int x, int y, int dx,int dy, int radius,int dir, vector<ofImage> images);

    ~Bullet();
private:
    int x, y,speed, radius, dir, dx, dy;//dir = 0 left =1 right =2 toward nearest player
    vector<ofImage> images;
    
};


#endif /* bullet_h */
