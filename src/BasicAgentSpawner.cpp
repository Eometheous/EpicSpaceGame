//
//  BasicAgentSpawner.cpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/9/24.
//
#include "BasicAgentSpawner.hpp"

BasicAgentSpawner::BasicAgentSpawner() {
}

BasicAgentSpawner::BasicAgentSpawner(GameObject *t) {
    target = t;
    spawnRate = 1;
    lifespan = 5;
    basicAgentSpawnLimit = 10;
    timeSinceLastSpawned = 0;
}

void BasicAgentSpawner::update() {
    float time = ofGetElapsedTimeMillis();
    
    if ((time - timeSinceLastSpawned) > (1000 / spawnRate) && basicAgents.size() < basicAgentSpawnLimit) {
        spawnBasicAgent();
        timeSinceLastSpawned = time;
    }
    
    for (int i = 0; i < basicAgents.size(); i++) {
        basicAgents.at(i).update();
        if (basicAgents.at(i).age > lifespan * 1000) despawnAgent(i);
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
    basicAgents.at(i).scale -= .05;
    if (basicAgents.at(i).scale < 0) basicAgents.erase(basicAgents.begin() + i);
}

void BasicAgentSpawner::killAgent(int i) {
    basicAgents.erase(basicAgents.begin() + i);
}

void BasicAgentSpawner::despawnAll() {
    while (basicAgents.size() > 0) {
        despawnAgent(0);
    }
}

void BasicAgentSpawner::killAll() {
    while (basicAgents.size() > 0) {
        killAgent(0);
    }
}
