#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    background.load("sprites/background.png");
    gameStarted = false;
    gameOver = false;
    
    basicAgentSpawner = BasicAgentSpawner(&player);
    
    keymap.insert({'w', false});
    keymap.insert({'s', false});
    keymap.insert({'a', false});
    keymap.insert({'d', false});
    keymap.insert({' ', false});
    
    thrusterSound.load("sounds/Thrusters.wav");
    thrusterSound.setVolume(.2);
    hitSound1.load("sounds/Hit1.wav");
    hitSound2.load("sounds/Hit2.wav");
    hitSound3.load("sounds/Hit3.wav");
    explosionSound1.load("sounds/Explosion1.wav");
    explosionSound2.load("sounds/Explosion2.wav");
    explosionSound3.load("sounds/BurstFire.wav");
    
    gui.setup();
    gui.add(startingEnergyLevel.setup("Starting Energy", 10, 1, 100));
    gui.add(timeRequiredToWin.setup("Time Required to Win", 30, 10, 60));
    gui.add(movementForceMultiplier.setup("Movement Force Multiplier", 1, .1, 10));
    gui.add(rotationForceMultiplier.setup("Rotational Force Multiplier", 1, .1, 10));
    gui.add(playerScale.setup("Player Scale", 1, .5, 10));
    gui.add(basicAgentSpawnRate.setup("Agent Spawn Rate", 1, .5, 100));
    gui.add(basicAgentLifespan.setup("Agent Life Span", 5, 1, 60));
    gui.add(basicAgentSpawnLimit.setup("Agent Spawn Limit", 10, 1, 100));
}

//--------------------------------------------------------------
void ofApp::update(){
    if (gameStarted && !gameOver)
    {
        player.update();
        if (keymap.at('w')) {
            ofVec3f euler = player.rotationMatix.getRotate().getEuler();
            
            if (euler.x == 0) {
                player.forces = ofVec2f(0, -500 * movementForceMultiplier).rotate(euler.z) - player.velocity;
            }
            else  {
                player.forces = ofVec2f(0, -500 * movementForceMultiplier).rotate(180 + euler.z * -1) - player.velocity;
            }
        }
        if (keymap.at('s')) {
            ofVec3f euler = player.rotationMatix.getRotate().getEuler();
            
            if (euler.x == 0) {
                player.forces = ofVec2f(0, 100 * movementForceMultiplier).rotate(euler.z);
            }
            else  {
                player.forces = ofVec2f(0, 100 * movementForceMultiplier).rotate(180 + euler.z * -1);
            }
        }
        
        if (keymap.at('a')) player.rotationalForces = -5 * rotationForceMultiplier - player.rotationalVelocity;
        if (keymap.at('d')) player.rotationalForces = 5 * rotationForceMultiplier - player.rotationalVelocity;
        
        if ((keymap.at('w') || keymap.at('s') || keymap.at('a') || keymap.at('d')) && !thrusterSound.isPlaying()) {
            thrusterSound.play();
        }
        else if (!(keymap.at('w') || keymap.at('s') || keymap.at('a') || keymap.at('d'))) thrusterSound.stop();
        
        player.gun.firing = keymap.at(' ');
        
        if (!gameWon) {
            timeAlive = (ofGetElapsedTimeMillis() - startTime) / 1000;
            basicAgentSpawner.update();
        }
        
        for (int i = 0; i < basicAgentSpawner.basicAgents.size(); i++) {
            if (basicAgentSpawner.basicAgents.at(i).collision(&player)) {
                basicAgentSpawner.killAgent(i);
                energyLevel -= 1;
                int soundToPlay = ofRandom(3);
                if (soundToPlay == 0) hitSound1.play();
                else if (soundToPlay == 1) hitSound2.play();
                else hitSound3.play();
            }
            
            else if (player.gun.checkHit(basicAgentSpawner.basicAgents.at(i))) {
                basicAgentSpawner.killAgent(i);
                if (energyLevel < startingEnergyLevel) energyLevel += 1;
            }
        }
        
        if ((energyLevel <= 0 || player.gun.deviance >= 1000) && !gameWon) {
            thrusterSound.stop();
            explosionSound1.play();
            explosionSound2.play();
            explosionSound3.play();
            gameOver = true;
            player.gun.firing = false;
            player.gun.alive = false;
        }
        
        if (timeAlive >= timeRequiredToWin) {
            gameWon = true;
            basicAgentSpawner.despawnAll();
        }
    }
    
    if (gameOver) {
        player.sprite.load("sprites/dead_player.png");
        if (player.scale >= 0) {
            player.rotationalForces = 5 - player.rotationalVelocity;
            player.scale -= .01;
            player.update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofColor::white);
    background.draw(0, 0, background.getWidth(), background.getHeight());
    
    
    string frameRate;
    frameRate += "Frame Rate: " + std::to_string(ofGetFrameRate());
    ofDrawBitmapString(frameRate, ofGetWindowWidth() -170, 15);
    
    string timeAliveString;
    
    if (!gameStarted) {
        gui.draw();
        ofDrawBitmapString("Press Enter to start the game", ofGetWindowWidth() / 2 - 120, ofGetWindowHeight() / 2 + 40);
    }
    
    if (gameStarted) {
        player.draw();
        
        basicAgentSpawner.draw();
        
        float barWidth = 200;
        float barHeight = 25;
        
        ofSetColor(ofColor::red);
        energyLevelAsFloat = energyLevel;
        ofDrawRectangle(20, 20, barWidth, barHeight);
        
        ofSetColor(ofColor::green);
        ofDrawRectangle(20, 20, (barWidth * (energyLevelAsFloat / startingEnergyLevel)), barHeight);
        
        ofSetColor(ofColor::white);
        ofDrawBitmapString("Energy Level", 70, 17);
        ofSetColor(ofColor::black);
        ofDrawBitmapString(std::to_string(energyLevel) + " / " + std::to_string(startingEnergyLevel), 90, 37);
    
        ofSetColor(ofColor::green);
        float devianceFloat = player.gun.deviance;
        ofDrawRectangle(260, 20, barWidth, barHeight);
        
        ofSetColor(ofColor::red);
        ofDrawRectangle(260, 20, (barWidth * (devianceFloat / 1000)), barHeight);
        
        ofSetColor(ofColor::white);
        ofDrawBitmapString("Gun Stability", 300, 17);
        ofSetColor(ofColor::black);
        int deviance = player.gun.deviance;
        ofDrawBitmapString(std::to_string(deviance) + " / 1000", 290, 37);
        
        
        timeAliveString = "Time Alive: " + std::to_string(timeAlive);
        ofSetColor(ofColor::white);
        if (!gameOver) ofDrawBitmapString(timeAliveString, ofGetWindowWidth() -170, 30);
    
    }
    
    if (gameOver) {
        ofSetColor(ofColor::white);
        ofDrawBitmapString("Game Over!", ofGetWindowWidth() / 2 - 40, ofGetWindowHeight() / 2);
        ofDrawBitmapString(timeAliveString, (ofGetWindowWidth() / 2) - 40, (ofGetWindowHeight()) / 2 + 30);
        ofDrawBitmapString("Press Enter to return to main menu", ofGetWindowWidth() / 2 - 40, ofGetWindowHeight() / 2 + 60);
        ofDrawBitmapString("Press R to play again", ofGetWindowWidth() / 2 - 40, ofGetWindowHeight() / 2 + 90);
    }
    
    if (gameWon) {
        ofSetColor(ofColor::white);
        ofDrawBitmapString("You Won!", ofGetWindowWidth() / 2 - 40, ofGetWindowHeight() / 2);
        ofDrawBitmapString(timeAliveString, (ofGetWindowWidth() / 2) - 40, (ofGetWindowHeight()) / 2 + 30);
        ofDrawBitmapString("Press Spacebar to return to main menu", ofGetWindowWidth() / 2 - 40, ofGetWindowHeight() / 2 + 60);
        ofDrawBitmapString("Press R to play again", ofGetWindowWidth() / 2 - 40, ofGetWindowHeight() / 2 + 90);
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_RETURN) {
        if (!gameStarted) startGame();
        if (gameOver || gameWon) {
            basicAgentSpawner.killAll();
            gameOver = false;
            gameStarted = false;
            gameWon = false;
        }
    }
    if (key == 'w') keymap.at('w') = true;
    if (key == 's') keymap.at('s') = true;
    if (key == 'a') keymap.at('a') = true;
    if (key == 'd') keymap.at('d') = true;
    if (key == 'r') if (gameStarted) startGame();
    if (key == ' ') keymap.at(' ') = true;
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'w') keymap.at('w') = false;
    if (key == 's') keymap.at('s') = false;
    if (key == 'a') keymap.at('a') = false;
    if (key == 'd') keymap.at('d') = false;
    if (key == ' ') keymap.at(' ') = false;
}

void ofApp::startGame() {
    basicAgentSpawner.despawnAll();
    timeAlive = 0;
    startTime = ofGetElapsedTimeMillis();
    
    player.setPosition(ofVec2f(ofWindowSettings().getWidth() / 2, ofWindowSettings().getHeight() / 2));
    player.velocity = ofVec2f();
    player.acceleration = ofVec2f();
    
    player.rotationMatix = ofMatrix4x4();
    player.rotationalVelocity = 0;
    player.rotationalForces = 0;
    
    player.scale = playerScale;
    player.sprite.load("sprites/player.png");
    energyLevel = startingEnergyLevel;
    
    basicAgentSpawner.spawnRate = basicAgentSpawnRate;
    basicAgentSpawner.lifespan = basicAgentLifespan;
    basicAgentSpawner.basicAgentSpawnLimit = basicAgentSpawnLimit;
    
    gameOver = false;
    gameWon = false;
    gameStarted = true;
    player.gun.alive = true;
    player.gun.deviance = 0;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
