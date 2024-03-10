//
//  BasicAgentSpawner.cpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/9/24.
//
#include "BasicAgentSpawner.hpp"

BasicAgentSpawner::BasicAgentSpawner() {
    spawnRate = 1;
    timeSinceLastSpawned = 0;
}

BasicAgentSpawner::BasicAgentSpawner(GameObject *t) {
    target = t;
    spawnRate = 1;
    timeSinceLastSpawned = 0;
}

void BasicAgentSpawner::update() {
    float time = ofGetElapsedTimeMillis();
    
    if ((time - timeSinceLastSpawned) > (1000 / spawnRate)) {
        spawnBasicAgent();
        timeSinceLastSpawned = time;
    }
    
    for (int i = 0; i < basicAgents.size(); i++) {
        basicAgents.at(i).update();
        if (basicAgents.at(i).age > (basicAgents.at(i).lifespan)) despawnAgent(i);
    }
}

void BasicAgentSpawner::draw() {
    for (int i = 0; i < basicAgents.size(); i++) {
        basicAgents.at(i).draw();
    }
}

void BasicAgentSpawner::spawnBasicAgent() {
    BasicAgent newAgent;
    newAgent.setTarget(target);
    if ((newAgent.position - target->position).length() > 100)
        basicAgents.push_back(newAgent);
}

void BasicAgentSpawner::despawnAgent(int i) {
    basicAgents.erase(basicAgents.begin() + i);
}
