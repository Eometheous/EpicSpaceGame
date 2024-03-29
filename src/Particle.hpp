//
//  Bullet.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/27/24.
//

#ifndef Bullet_hpp
#define Bullet_hpp
#pragma once
#include "GameObject.hpp"

#endif /* Bullet_hpp */

class Particle: public GameObject {
public:
    float age;
    float birthtime;
    
    Particle();
    void update();
    void draw();
};
