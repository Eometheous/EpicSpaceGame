//
//  Bullet.cpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/27/24.
//

#include "Particle.hpp"

Particle::Particle() {
    age = 0;
    birthtime = ofGetElapsedTimeMillis() / 1000;
    sprite.load("sprites/bullet.png");
    position = ofVec2f();
}

void Particle::update() {
    age = (ofGetElapsedTimeMillis() / 1000) - birthtime;
    integrate();
}

void Particle::draw() {
    ofMatrix4x4 translation = ofMatrix4x4();
    translation.translate(position);
    ofMatrix4x4 scaleMatrix = ofMatrix4x4();
    
    scaleMatrix.scale(scale, scale, 0);
    
    ofPushMatrix();
    
    ofMultMatrix(scaleMatrix * rotationMatix * translation);
    sprite.draw(-ofVec2f(sprite.getWidth() / 2, sprite.getHeight() / 2), sprite.getWidth() , sprite.getHeight());
    ofPopMatrix();
}
