#include "ofApp.h"
#include "synth.h"
#include "channel.hpp"
#include "wave.h"
#include "generator.hpp"
#include "gpioController.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    // ofEnableAlphaBlending();
    // not the best way to throttle speed. see here: https://forum.openframeworks.cc/t/for-those-who-dont-know-about-framerate-a-little-demo/6443/2
    // ofSetFrameRate(20);
    redWave = Wave(sawTable, TABLE_LENGTH, 10, 2);
    red = Channel(&redWave, false, 1.0, nullptr, 0.0, modPhase);
    greenWave = Wave(triangleTable, TABLE_LENGTH, 4, 1);
    green = Channel(&greenWave, false, 1.0, nullptr, 0.0, modPhase);
    blueWave = Wave(squareTable, TABLE_LENGTH, 50, 1);
    blue = Channel(&blueWave, false, 1.0, nullptr, 0.0, modPhase);
//    red.setSpeed(0.2);
    //green.setModSrc(&red);
    //green.setModAmt(0.01);
//    green.setWeight(0);
//    blue.setWeight(0);
    synth = Synth(&red, &green, &blue, 60);
    gpioController = GPIOController(&synth);
    kbController = KbController(&synth);
    ofBackground(ofColor::black);
}

//--------------------------------------------------------------
void ofApp::update(){
    gpioController.update();
    synth.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    synth.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // switch synth: r, g, b
    // shape (3)
    //   - q, w, e
    // length (+/-)
    //   - a, s
    // frequency (+/-)
    //   - d, f
    // weight (+/-)
    //   - z, x
    // modAmt (+/-)
    //   - c, v
    // modSrc (3 currently but will be 5)
    //   - t, h, n (next to rgb)
    // modDst (3)
    //   - y, j, m
    
    // create a controller API for Synth class
    // exposes methods like
    //   - setShape(chn, shape)
    //   - setLength(chn, length)
    //   - setModAmt(chn, amt)
    // the downside of this kind of api is that the controller (e.g. keyboard)
    // has to maintain the state of the previous value for the changes that are incremental (e.g. length)
    // But it also seems like a bad idea (worse really) to just have incrementLength()
    // b/c what if the controller and synth state get out of sync
    //   (e.g. using a midi knob, that I turn really fast, it skips some increments, and even though my knob is maxed out
    //    the parameter is not)
    // it is the controller (e.g. keyboard) responsibility
    // to maintain "active" synths if that's how it's implemented
    switch(key) {
        case '?':
            // midiIn.listInPorts();
            synth.toggleDebugger();
            break;
    }
    kbController.keyPressed(key);
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
