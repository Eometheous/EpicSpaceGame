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
    
    vector<Bullet> firedBullets;
    
    PlayerGun();
    void update();
    void draw();
    void fire();
    void despawnBullet(int i);
    bool checkHit(GameObject &o);
};
