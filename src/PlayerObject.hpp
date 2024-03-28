//
//  PlayerObject.hpp
//  PursuitGame
//
//  Created by Jonathan Thomas on 3/8/24.
//
#pragma once

#include "GameObject.hpp"
#include "PlayerGun.hpp"


class PlayerObject: public GameObject {
public:
    PlayerObject();
    
    PlayerGun gun;
    
    void update();
    void draw();
};
