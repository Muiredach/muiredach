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
    
    ofSetFrameRate(180);
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 1024; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    
    gui.setup();
    gui.add(speed.setup("speed", 5, 1, 10));
    gui.add(length.setup("length", 50, 10, sqrt( (((ofGetHeight()/2)*(ofGetHeight()/2)) + ((ofGetWidth()/2)*(ofGetWidth()/2))))));
    gui.add(CircleRadius.setup("circle raius", 5, 1, 20));
    
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    /* Anything that you would normally find/put in maximilian's setup() method needs to go here. For example, Sample loading.
     */
    

    
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}


void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    
    for (int i = 0; i < bufferSize; i++){
        
        
        float *sound;
        
        for (auto & CircleDelay : Circles)
        {
            
            *sound += CircleDelay.process(CircleDelay.CircleOscs()/Circles.size());
            
        }
        
        output[i*nChannels    ] = *sound;
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
    
    ofBackground(0,0,0);
    
    ofSetLineWidth(5);
    
    int frameCount = ofGetFrameNum();
    int frameAngle = frameCount;
    
    float lineX = length * cos((frameAngle*speed)/60);
    float lineY = length * sin((frameAngle*speed)/60);
    ofDrawLine(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2 + lineX, ofGetHeight()/2 + lineY);
    
    for (auto & CircleDelay : Circles)
    {
        CircleDelay.draw();
        //cout << CircleDelay.x << endl;
        for (int i = 0; i <= length; i++)
        {
            if(CircleDelay.x >= (int)((ofGetWidth()/2 + i*(lineX/length))-5)   &&
               CircleDelay.x <= (int)((ofGetWidth()/2 + i*(lineX/length))+5)   &&
               CircleDelay.y >= (int)((ofGetHeight()/2 + i*(lineY/length))-5)   &&
               CircleDelay.y <= (int)((ofGetHeight()/2 + i*(lineY/length))+5))
            {
                ofBackground(255,0,0);
                CircleDelay.trig = true;
            }
            else CircleDelay.trig = false;
        }
    }
    
    
    
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
    
    if (Circles.size() < 5)
    {
        Circles.insert(Circles.begin(), CircleDelay(x, y, CircleRadius));
    }else if (Circles.size() >= 5)
    {
        Circles.pop_back();
        Circles.insert(Circles.begin(), CircleDelay(x, y, CircleRadius));
        
    }
    
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
