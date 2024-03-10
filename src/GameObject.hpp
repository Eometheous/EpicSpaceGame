//
//  GameObject.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/8/24.
//
#pragma once

#include "ofMain.h"

class GameObject {
public:
    GameObject();
    
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    float rotationalVelocity;
    float rotationalAcceleration;
    ofVec2f forces;
    float rotationalForces;
    float mass;
    ofMatrix4x4 rotationMatix;
    
    
    ofImage sprite;
    
    void setPosition(ofVec2f nPos);
    void integrate();
    virtual void draw() = 0;
    
    void clamp();
    bool collision(GameObject *otherObject);
};
