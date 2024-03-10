//
//  PlayerObject.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/8/24.
//
#pragma once

#include "GameObject.hpp"
#include "ofMain.h"


class PlayerObject: public GameObject {
public:
    PlayerObject();
    
    int nEnergy;
    float scale;
    
    void update();
    void draw();
};
