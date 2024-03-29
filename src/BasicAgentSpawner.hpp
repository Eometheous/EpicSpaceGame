//
//  BasicAgentSpawner.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/9/24.
//

#ifndef BasicAgentSpawner_hpp
#define BasicAgentSpawner_hpp

#include "BasicAgent.hpp"
#include "Explosion.hpp"

#endif /* BasicAgentSpawner_hpp */

class BasicAgentSpawner {
public:
    BasicAgentSpawner();
    BasicAgentSpawner(GameObject *target);
    
    GameObject *target;
    float spawnRate;
    float lifespan;
    float basicAgentSpawnLimit;
    float timeSinceLastSpawned;
    
    vector<BasicAgent> basicAgents;
    vector<Explosion> explosions;
    
    void update();
    void draw();
    void spawnBasicAgent();
    void despawnAgent(int i);
    void killAgent(int i);
    
    void despawnAll();
    void killAll();
};
