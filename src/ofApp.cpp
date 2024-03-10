#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    gameStarted = false;
    gameOver = false;
    player = PlayerObject();
    
    basicAgentSpawner = BasicAgentSpawner(&player);
    
    keymap.insert({'w', false});
    keymap.insert({'s', false});
    keymap.insert({'a', false});
    keymap.insert({'d', false});
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (gameStarted && !gameOver)
    {
        timeAlive = (ofGetElapsedTimeMillis() - startTime) / 1000;
        player.update();
        if (keymap.at('w')) {
            ofVec3f euler = player.rotationMatix.getRotate().getEuler();
            
            if (euler.x == 0) {
                player.forces = ofVec2f(0, -500).rotate(euler.z) - player.velocity;
            }
            else  {
                player.forces = ofVec2f(0, -500).rotate(180 + euler.z * -1) - player.velocity;
            }
        }
        if (keymap.at('s')) {
            ofVec3f euler = player.rotationMatix.getRotate().getEuler();
            
            if (euler.x == 0) {
                player.forces = ofVec2f(0, 100).rotate(euler.z);
            }
            else  {
                player.forces = ofVec2f(0, 100).rotate(180 + euler.z * -1);
            }
        }
        
        if (keymap.at('a')) player.rotationalForces = -5 - player.rotationalVelocity;
        if (keymap.at('d')) player.rotationalForces = 5 - player.rotationalVelocity;
        
        basicAgentSpawner.update();
        
        for (int i = 0; i < basicAgentSpawner.basicAgents.size(); i++) {
            if (basicAgentSpawner.basicAgents.at(i).collision(&player)) {
                basicAgentSpawner.despawnAgent(i);
                energyLevel -= 1;
                cout <<energyLevel << endl;
            }
        }
        
        if (energyLevel <= 0) gameOver = true;
    }
    
    if (gameOver) {
        player.sprite.load("sprites/dead_player.png");
        if (player.scale >= 0) {
            player.rotationalForces = 5;
            player.scale -= .01;
            player.update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    string frameRate;
    frameRate += "Frame Rate: " + std::to_string(ofGetFrameRate());
    ofSetColor(ofColor::white);
    ofDrawBitmapString(frameRate, ofGetWindowWidth() -170, 15);
    
    string timeAliveString;
    
    if (gameStarted) {
        ofSetColor(255, 255, 255);
        player.draw();
        
        basicAgentSpawner.draw();
        
        float healthBarWidth = 200;
        float healthBarHeight = 25;
        
        ofSetColor(255, 0, 0);
        ofDrawRectangle(ofWindowSettings().getWidth() / 2 - healthBarWidth / 2, 40, healthBarWidth, healthBarHeight);
        
        ofSetColor(0, 255, 0);
        ofDrawRectangle(ofWindowSettings().getWidth() / 2 - healthBarWidth / 2, 40, (healthBarWidth * (energyLevel / 10)), healthBarHeight);
    
        timeAliveString += "Time Alive: " + std::to_string(timeAlive);
        
        if (!gameOver) ofDrawBitmapString(timeAlive, ofGetWindowWidth() -170, 30);
    
    }
    
    if (gameOver) {
        ofDrawBitmapString("Game Over!", ofGetWindowWidth() / 2 - 40, ofGetWindowHeight() / 2);
        ofDrawBitmapString(timeAliveString, (ofGetWindowWidth() / 2) - 40, (ofGetWindowHeight()) / 2 + 30);
        ofDrawBitmapString("Press Spacebar to Play Again", ofGetWindowWidth() / 2 - 40, ofGetWindowHeight() / 2 + 60);
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') startGame();
    if (key == 'w') keymap.at('w') = true;
    if (key == 's') keymap.at('s') = true;
    if (key == 'a') keymap.at('a') = true;
    if (key == 'd') keymap.at('d') = true;
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'w') keymap.at('w') = false;
    if (key == 's') keymap.at('s') = false;
    if (key == 'a') keymap.at('a') = false;
    if (key == 'd') keymap.at('d') = false;
}

void ofApp::startGame() {
    timeAlive = 0;
    startTime = ofGetElapsedTimeMillis();
    basicAgentSpawner.reset();
    
    player.setPosition(ofVec2f(ofWindowSettings().getWidth() / 2, ofWindowSettings().getHeight() / 2));
    player.scale = 1;
    player.sprite.load("sprites/player.png");
    energyLevel = 10;
    gameOver = false;
    gameStarted = true;
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
