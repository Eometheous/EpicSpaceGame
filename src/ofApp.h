#pragma once

#include "ofMain.h"
#include "PlayerObject.hpp"
#include "BasicAgentSpawner.hpp"
#include "Explosion.hpp"
#include "GameObject.hpp"
#include "unordered_map"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;

    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    
    ofImage background;
    
    PlayerObject player;
    Explosion playerExplosion;
    
    BasicAgentSpawner basicAgentSpawner;
    
    int energyLevel;
    float energyLevelAsFloat;
    
    bool gameStarted;
    bool gameOver;
    bool gameWon;
    
    int timeAlive;
    int startTime;
    
    unordered_map<int, bool> keymap;
    
    ofxPanel gui;
    
    ofSoundPlayer thrusterSound;
    ofSoundPlayer hitSound1;
    ofSoundPlayer hitSound2;
    ofSoundPlayer hitSound3;
    ofSoundPlayer explosionSound1;
    ofSoundPlayer explosionSound2;
    ofSoundPlayer explosionSound3;
    
    ofxIntSlider startingEnergyLevel;
    ofxIntSlider timeRequiredToWin;
    ofxFloatSlider movementForceMultiplier;
    ofxFloatSlider rotationForceMultiplier;
    ofxFloatSlider playerScale;
    
    ofxFloatSlider basicAgentSpawnRate;
    ofxFloatSlider basicAgentLifespan;
    ofxIntSlider basicAgentSpawnLimit;
    
    ofxIntSlider levelSlider;
    
    void startGame();
};
