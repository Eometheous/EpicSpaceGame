//
//  Bullet.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/27/24.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "GameObject.hpp"

#endif /* Bullet_hpp */

class Bullet: public GameObject {
public:
    float age;
    float birthtime;
    
    Bullet();
    void update();
    void draw();
};
