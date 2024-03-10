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
    sprite.draw(-ofVec2f(sprite.getWidth() * scale / 2, sprite.getHeight() * scale / 2), sprite.getWidth() * scale, sprite.getHeight() * scale);
    ofPopMatrix();
}
