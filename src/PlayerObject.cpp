//
//  PlayerObject.cpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/8/24.
//

#include "ofMain.h"
#include "GameObject.hpp"
#include "PlayerObject.hpp"

PlayerObject::PlayerObject() {
    scale = 1;
    sprite.load("sprites/player.png");
}

void PlayerObject::update() {
    integrate();
    clamp();
}

void PlayerObject::draw() {
    ofMatrix4x4 translation = ofMatrix4x4();
    translation.translate(position);
    
    ofPushMatrix();
    
    ofMultMatrix(rotationMatix * translation);
    sprite.draw(-ofVec2f(19, 19), 38, 38);
    ofPopMatrix();
}
