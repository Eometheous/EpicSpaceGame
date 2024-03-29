//
//  Explosion.cpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/29/24.
//

#include "Explosion.hpp"

Explosion::Explosion() {
    explosionForce = 50;
    for (int i = 0; i < 500; i++) {
        explosionParticles.push_back(new Particle());
        explosionParticles.at(i)->sprite.load("sprites/bullet.png");
    }
}

void Explosion::update() {
    if (exploding) {
        for (int i = 0; i < explosionParticles.size(); i++) {
            explosionParticles.at(i)->integrate();
        }
    }
}

void Explosion::draw() {
    if (exploding) {
        for (int i = 0; i < explosionParticles.size(); i++) {
            explosionParticles.at(i)->draw();
        }
    }
}

void Explosion::explode(ofVec2f at, ofVec2f initialVelocity) {
    for (int i = 0; i < explosionParticles.size(); i++) {
        explosionParticles.at(i)->position = at;
        explosionParticles.at(i)->velocity += initialVelocity;
    }
    exploding = true;
}

void Explosion::reset() {
    exploding = false;
    for (int i = 0; i < explosionParticles.size(); i++) {
        int x = ofRandom(-explosionForce, explosionForce);
        // get a random offset y within the bounds of the circle
        int y = ofRandom(sqrt(explosionForce * explosionForce - x * x) * -1, sqrt(explosionForce * explosionForce - x * x));
        explosionParticles.at(i)->velocity = ofVec2f(x, y);
    }
}
