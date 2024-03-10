//
//  GameObject.cpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/8/24.
//

#include "GameObject.hpp"


GameObject::GameObject() {
    position.set(0, 0);
    velocity.set(0, 0);
    acceleration.set(0, 0);
    rotationalVelocity = 0;
    rotationalAcceleration = 0;
    rotationMatix = ofMatrix4x4();
    forces.set(0, 0);
    
    mass = 1;
}

void GameObject::setPosition(ofVec2f nPos) {
    position = nPos;
}

void GameObject::integrate() {
    float dt = 1.0 / ofGetFrameRate();
    
    position += velocity * dt;
    
    ofVec2f currentAcceleration = acceleration;
    currentAcceleration += forces * (1.0 / mass);
    velocity += currentAcceleration * dt;
    
    forces.set(velocity * -.5);
    
    rotationMatix.rotate(rotationalVelocity, 0, 0, sprite.getWidth());
    
    float currentRotationalAcceleration = rotationalAcceleration;
    currentRotationalAcceleration += rotationalForces * (1.0 / mass);
    rotationalVelocity += currentRotationalAcceleration * dt;
    
    rotationalForces = rotationalVelocity * -5;
    
}

void GameObject::clamp() {
    if (position.x < 10 || position.x > ofWindowSettings().getWidth() - 10) {
        velocity.x *= -1;
    }
    
    if (position.y < 10 || position.y > ofWindowSettings().getHeight() -10) {
        velocity.y *= -1;
    }
}

bool GameObject::collision(GameObject *otherObject) {
    return (position - otherObject->position).length() < (sprite.getWidth() / 3 + otherObject->sprite.getWidth() / 3);
}


