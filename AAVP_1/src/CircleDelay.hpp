//
//  CircleDelay.hpp
//  AAVP_1
//
//  Created by Muiredach O'Riain on 16/01/2017.
//
//

#ifndef CircleDelay_hpp
#define CircleDelay_hpp

#include <stdio.h>
#include "ofxMaxim.h"
#include "ofMain.h"
#include <array>

using std::array;

class CircleDelay{

public:
    //constuctor and initialisation
    explicit CircleDelay(int _x, int _y, int _w);
    
    //properties for the circle
    int x;
    int y;
    int w;
    
    //properties for the delay
    array< float, 44100*2 > Buffer; //this sets the size of the delay buffer to 1 second (considering a SamleRate of 44100Hz
    float Feedback;
    int BufferIndex, BufferLength;
    
    //properties noise generation
    ofxMaxiOsc CirclePluck;
    ofxMaxiOsc CircleCounter;
    maxiEnv CircleEnvelope;
    double CircleOscOutput, CircleCurrentVolume;

    
    
    // Methods
    void draw();
    float process(float input);
    int calcNote();
    double CircleOscs(int x, int y);
    
};

#endif /* CircleDelay_hpp */
