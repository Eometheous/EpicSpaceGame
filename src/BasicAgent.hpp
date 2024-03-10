//
//  BasicAgent.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/8/24.
//

#ifndef BasicAgent_hpp
#define BasicAgent_hpp

#import "GameObject.hpp"

#endif /* BasicAgent_hpp */

class BasicAgent: public GameObject {
public:
    BasicAgent();
    
    GameObject *target;
    float age;
    float birthTime;
    
    
    void update();
    void draw();
    void chase();
    
    void setTarget(GameObject *target);
};
