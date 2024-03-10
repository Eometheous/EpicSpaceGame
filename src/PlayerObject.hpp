//
//  PlayerObject.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/8/24.
//
#pragma once

#include "GameObject.hpp"


class PlayerObject: public GameObject {
public:
    PlayerObject();
    
    void update();
    void draw();
};
