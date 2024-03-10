#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    gameStarted = false;
    player = PlayerObject();
    player.setPosition(ofVec2f(ofWindowSettings().getWidth() / 2, ofWindowSettings().getHeight() / 2));
    
    basicAgent = BasicAgent();
    basicAgent.setTarget(&player);
    
    keymap.insert({'w', false});
    keymap.insert({'s', false});
    keymap.insert({'a', false});
    keymap.insert({'d', false});
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (gameStarted)
    {
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
        
        basicAgent.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (gameStarted) {
        player.draw();
        
        basicAgent.draw();
    }
    
    string str;
    str += "Frame Rate: " + std::to_string(ofGetFrameRate());
    ofSetColor(ofColor::white);
    ofDrawBitmapString(str, ofGetWindowWidth() -170, 15);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') gameStarted = true;
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
