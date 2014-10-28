#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    image.loadImage("images/trippy.png");
    imageTwo.loadImage("images/01_5.jpg");
    image.resize(200, 200);
    imageTwo.resize(800, 800);
    mesh.setMode(OF_PRIMITIVE_LINES);
    ofSetFrameRate(60);
    
    
    cout << mesh.getNumVertices() << endl;  // It should be ~64,000
    
    float intensityThreshold = 150.0;
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x=0; x<w; ++x) {
        for (int y=0; y<h; ++y) {
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(4*x, 4*y, z);
                mesh.addVertex(pos);
                mesh.addColor(c);
                
                offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            }
        }
    }
    
    float connectionDistance = 30;
    int numVerts = mesh.getNumVertices();
    for (int a=0; a<numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b=a+1; b<numVerts; ++b) {
            ofVec3f vertb = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
        }
    }
    mouseDisplacement = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    meshCopy = mesh;
    
    if (mouseDisplacement) {
        // Get the mouse location - it must be relative to the center of our screen because of the ofTranslate() command in draw()
        ofVec3f mouse(mouseX, ofGetWidth()-mouseY, 0);
        
        // Loop through all the vertices in the mesh and move them away from the mouses
        for (int i=0; i<mesh.getNumVertices(); ++i) {
            ofVec3f vertex = meshCopy.getVertex(i);
            float distanceToMouse = mouse.distance(vertex);
            
            // Scale the displacement based on the distance to the mouse
            // Small distance to mouse should yield a small displacement
            float displacement = ofMap(distanceToMouse, 0, 400, 300.0, 0, true);
            
            // Calculate the direction from the mouse to the current vertex
            ofVec3f direction = vertex - mouse;
            
            // Normalize the direction so that it has a length of one
            // This lets us easily change the length of the vector later
            direction.normalize();
            
            // Push the vertex in the direction away from the mouse and push it
            // a distance equal to the value of the variable displacement
            ofVec3f displacedVertex = vertex + displacement*direction;
            mesh.setVertex(i, displacedVertex);
        }
    }

    
    int numVerts = mesh.getNumVertices();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        
        float time = ofGetElapsedTimef();
        float timeScale = 5.0;
        float displacementScale = 0.75;
        ofVec3f timeOffsets = offsets[i];
        
        // A typical design pattern for using Perlin noise uses a couple parameters:
        // ofSignedNoise(time*timeScale+timeOffset)*displacementScale
        //     ofSignedNoise(time) gives us noise values that change smoothly over time
        //     ofSignedNoise(time*timeScale) allows us to control the smoothness of our noise (smaller timeScale, smoother values)
        //     ofSignedNoise(time+timeOffset) allows us to use the same Perlin noise function to control multiple things and have them look as if they are moving independently
        //     ofSignedNoise(time)*displacementScale allows us to change the bounds of the noise from [-1, 1] to whatever we want
        // Combine all of those parameters together, and you've got some nice control over your noise
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
        mesh.setVertex(i, vert);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    mesh.draw();
    ofPopMatrix();
    easyCam.end();
    
    
//    me.draw(me.width, 0);
//    me.draw(me.width, me.height);
//    me.draw(0, me.height);
 
    
    
    
//    int w = me.getWidth();
//    int h = me.getHeight();
//    float diameter = 8;
    
    
//    unsigned char* pixels = me.getPixels();
//    for(int y = 0; y < h; y++) {
//        for(int x = 0; x < w; x++) {
//            int index = y * w + x;
//            unsigned char cur = pixels[index];
//            float size = 1 - ((float) cur / 255);
//            ofCircle(0 + x * diameter, 0 + y * diameter, 1 + size * diameter / 2);
//        }
//    }
    
//    ofSetColor(255);
//    ofEnableAlphaBlending();
//    float wave = sin(ofGetElapsedTimef());
//    me.draw(me.width/4 + (wave * 100), 20);
//    ofDisableAlphaBlending();
    
 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'm') {
        mouseDisplacement = !mouseDisplacement;  // Inverts the boolean
        mesh = meshCopy;  // Restore the original mesh
    }
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
