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
    float spawnRate;
    float timeSinceLastSpawned;
    
    vector<BasicAgent> basicAgents;
    
    void update();
    void spawnBasicAgent();
};
