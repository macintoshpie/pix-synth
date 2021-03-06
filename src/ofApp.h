#pragma once

#include "ofMain.h"
#include "synth.h"
#include "channel.hpp"
#include "wave.h"
#include "kbController.hpp"
#include "gpioController.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
//        Wave wave;
        KbController kbController;
        GPIOController gpioController;
        Synth synth;
        Wave redWave;
        Channel red;
        Wave greenWave;
        Channel green;
        Wave blueWave;
        Channel blue;
//    ofTexture tex;
//    unsigned char pixels[200 * 200];
    
};
