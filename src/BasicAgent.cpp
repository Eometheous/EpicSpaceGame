//
//  BasicAgent.cpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/8/24.
//

#include "BasicAgent.hpp"

BasicAgent::BasicAgent() {
    age = 0;
    lifespan = 5;
    birthTime = ofGetElapsedTimeMillis() / 1000;
    sprite.load("sprites/basic_enemy.png");
    position = ofVec2f(rand() % (ofWindowSettings().getWidth() - 30 ) + 30, rand() % (ofWindowSettings().getHeight() - 30) + 30);
    rotationMatix.rotate(rand() % 360, 0, 0, sprite.getWidth());
}

void BasicAgent::update() {
    age = (ofGetElapsedTimeMillis() / 1000) - birthTime;
    chase();
    integrate();
    clamp();
}

void BasicAgent::draw() {
    ofMatrix4x4 translation = ofMatrix4x4();
    translation.translate(position);
    
    ofPushMatrix();
    
    ofMultMatrix(rotationMatix * translation);
    sprite.draw(-ofVec2f(19, 19), 38, 38);
    ofPopMatrix();
}

void BasicAgent::chase() {

    ofVec2f facingDirection;
    
    ofVec3f euler = rotationMatix.getRotate().getEuler();
    
    if (euler.x == 0) {
        forces = ofVec2f(0, -200).rotate(euler.z) - velocity;
        facingDirection = ofVec2f(0, -50).rotate(euler.z);
    }
    else  {
        forces = ofVec2f(0, -200).rotate(180 + euler.z * -1) - velocity;
        facingDirection = ofVec2f(0, -50).rotate(180 + euler.z * -1);
    }
    
    ofVec2f directionToTarget = target->position - position;
    float angle = facingDirection.angle(directionToTarget);
    
    if (angle < 0) rotationalForces = -5 - rotationalVelocity;
    else  rotationalForces = 5 - rotationalVelocity;
}

void BasicAgent::setTarget(GameObject *t) {
    target = t;
}


