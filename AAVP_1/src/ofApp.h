#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMaxim.h"
#include "CircleDelay.hpp"

#include <vector>
#include <array>

using std::vector;
using std::array;

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
    
        // Audio output and input methods
    
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
    
    
        int		bufferSize; /* buffer size */
        int		sampleRate;
    
        maxiSample mySample;
    
        //---

        ofxFloatSlider speed;
        ofxFloatSlider CircleRadius;
        ofxFloatSlider length;
        ofxPanel gui;
    
        ofxMaxiSample sample;
        ofxMaxiMix mixer;
    
        ofxMaxiOsc noise;
    
        vector <CircleDelay> Circles;
    
        int w;
    
		
};

