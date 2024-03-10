//
//  BasicAgentSpawner.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/9/24.
//

#ifndef BasicAgentSpawner_hpp
#define BasicAgentSpawner_hpp

#include "BasicAgent.hpp"

#endif /* BasicAgentSpawner_hpp */

class BasicAgentSpawner {
public:
    BasicAgentSpawner();
    BasicAgentSpawner(GameObject *target);
    
    GameObject *target;
    float spawnRate;
    float timeSinceLastSpawned;
    
    vector<BasicAgent> basicAgents;
    
    void update();
    void draw();
    void spawnBasicAgent();
    void despawnAgent(int i);
    
    void reset();
};
