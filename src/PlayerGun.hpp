//
//  PlayerGun.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/27/24.
//

#ifndef PlayerGun_hpp
#define PlayerGun_hpp

#include "Bullet.hpp"

#endif /* PlayerGun_hpp */

class PlayerGun {
public:
    float fireRate;
    float bulletLifeSpan;
    float timeSinceLastSpawned;
    bool firing;
    ofVec2f pos;
    ofVec2f heading;
    float deviance;
    bool alive;
    
    ofSoundPlayer gunSound1;
    ofSoundPlayer gunSound2;
    ofSoundPlayer gunSound3;
    
    vector<Bullet> firedBullets;
    
    PlayerGun();
    void update();
    void draw();
    void fire();
    void despawnBullet(int i);
    bool checkHit(GameObject &o);
};
