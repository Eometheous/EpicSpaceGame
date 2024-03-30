//
//  PlayerGun.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/27/24.
//

#ifndef PlayerGun_hpp
#define PlayerGun_hpp
#pragma once
#include "Particle.hpp"

#endif /* PlayerGun_hpp */

class Gun {
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
    
    vector<Particle> firedBullets;
    
    Gun();
    void update();
    void draw();
    void fire();
    void despawnBullet(int i);
    bool checkHit(GameObject &o);
};
