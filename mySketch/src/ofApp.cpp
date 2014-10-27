#include "ofApp.h"

int myCircleX;
int myCircleY;
int myCircleRadius;
int speed;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    myCircleX = 0;
    myCircleY = 200;
    myCircleRadius = 60;
    speed = 2;

}

//--------------------------------------------------------------
void ofApp::update(){
    myCircleX += speed;
    
    if(myCircleX > 1024 || myCircleX < 0) {
        speed = speed*(-1);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255, 0, 255);
    ofCircle(myCircleX, myCircleY, myCircleRadius);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
