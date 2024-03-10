//
//  BasicAgent.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/8/24.
//

#ifndef BasicAgent_hpp
#define BasicAgent_hpp

#import "ofMain.h"
#import "GameObject.hpp"
#import "PlayerObject.hpp"

#endif /* BasicAgent_hpp */

class BasicAgent: public GameObject {
public:
    BasicAgent();
    
    GameObject *target;
    float age;
    float lifespan;
    
    
    void update();
    void draw();
    void chase();
    
    void setTarget(GameObject *target);
};
