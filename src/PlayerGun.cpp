//
//  PlayerGun.cpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/27/24.
//

#include "PlayerGun.hpp"

PlayerGun::PlayerGun() {
    fireRate = 10;
    bulletLifeSpan = 2;
    timeSinceLastSpawned = 0;
    firing = false;
    pos = ofVec2f();
    heading = ofVec2f();
    deviance = 0;
}

void PlayerGun::update() {
    float time = ofGetElapsedTimeMillis();
    
    if (firing && (time - timeSinceLastSpawned) > (1000 / fireRate) + (deviance/50) * (deviance/50)) {
        fire();
        timeSinceLastSpawned = time;
    }
    
    for (int i = 0; i < firedBullets.size(); i++) {
        firedBullets.at(i).update();
        if (firedBullets.at(i).velocity.length() < 200) despawnBullet(i);
    }
}

void PlayerGun::draw() {
    for (int i = 0; i < firedBullets.size(); i++) {
        firedBullets.at(i).draw();
    }
}

void PlayerGun::fire() {
    Bullet newBullet;
    newBullet.position = pos;
    newBullet.velocity = (heading.rotate(ofRandom(-sqrt(deviance), sqrt(deviance)))) * 500;
    firedBullets.push_back(newBullet);
}

void PlayerGun::despawnBullet(int i) {
    firedBullets.erase(firedBullets.begin() + i);
}

bool PlayerGun::checkHit(GameObject &o) {
    for (int i = 0; i < firedBullets.size(); i++) {
        if (o.collision(&firedBullets.at(i))) return true;
    }
    return false;
}
