#include "ofApp.h"
#include <cstdlib>
#include "maximilian.h"


    maxiOsc myCounter;
    int CurrentCount;
    double myOscOutput,myCurrentVolume;
    maxiEnv myEnvelope;
    float dealayedData;

//--------------------------------------------------------------
void ofApp::setup(){
    
    myEnvelope.setAttack(500);
    myEnvelope.setDecay(1);  // Needs to be at least 1
    myEnvelope.setSustain(50);
    myEnvelope.setRelease(500);
    
    
    ofSetFrameRate(60);
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    /* Anything that you would normally find/put in maximilian's setup() method needs to go here. For example, Sample loading.
     */
    
    mySample.load(ofToDataPath("sound.wav"));
    
    ofBackground(0,0,0);
    
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
    
    
    gui.setup();
    gui.add(speed.setup("speed", 5, 1, 10));
    gui.add(length.setup("length", 50, 10, sqrt( (((ofGetHeight()/2)*(ofGetHeight()/2)) + ((ofGetWidth()/2)*(ofGetWidth()/2))))));
    gui.add(CircleRadius.setup("circle raius", 5, 1, 20));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}


void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    
    for (int i = 0; i < bufferSize; i++){
        
        
        double sound;
        
        for (auto & CircleDelay : Circles)
        {
                sound += CircleDelay.process(CircleDelay.CircleOscs(12, 12)/Circles.size());
        }
        
        output[i*nChannels    ] = sound;
        output[i*nChannels + 1] = output[i*nChannels    ];

    }
    
}


void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for (auto & CircleDelay : Circles)
    {
        CircleDelay.draw();
    }
    
    ofSetLineWidth(5);
    
    int frameCount = ofGetFrameNum();
    int frameAngle = frameCount;
    
    float lineX = length * cos((frameAngle*speed)/40);
    float lineY = length * sin((frameAngle*speed)/40);
    ofDrawLine(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2 + lineX, ofGetHeight()/2 + lineY);
    
    
    gui.draw();
    
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
    
    int x_pos = x;
    int y_pos = y;
    
    Circles.push_back(CircleDelay(x_pos, y_pos, CircleRadius));
    
    
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

///--- my functions
