//
//  Explosion.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/29/24.
//

#ifndef Explosion_hpp
#define Explosion_hpp
#pragma once
#include "Particle.hpp"

#endif /* Explosion_hpp */

class Explosion {
public:
    vector<Particle*> explosionParticles;
    bool exploding;
    int explosionForce;
    float explodedAtTime;
    
    ofSoundPlayer explosion;
    
    Explosion();
    void update();
    void draw();
    void explode(ofVec2f at, ofVec2f initialVelocity);
    void reset();
};
