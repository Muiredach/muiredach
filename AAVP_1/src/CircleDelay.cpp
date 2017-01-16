//
//  CircleDelay.cpp
//  AAVP_1
//
//  Created by Muiredach O'Riain on 16/01/2017.
//
//

#include "CircleDelay.hpp"

CircleDelay::CircleDelay(int _x, int _y, int _w): x(_x), y(_y), w(_w){
    
    BufferIndex = 0;
    Feedback = 0.8;    
}




void CircleDelay::draw()
{
    ofCircle(x,y,w);
}


//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------



int CircleDelay::calcNote(){
    
    int SampleRate = 44100;
    
    
    //fills an array with all note frequency values
    float midi[127];
    
    for (int i= 0; i < 127; ++i)
    {
        // nf=2^{(d-69)/12} * 440
        
        midi[i] = pow(2, ((i-69.0)/12)) * 440;
    }
    
    
    float distance = sqrt(((ofGetWidth()/2 - x)*(ofGetWidth()/2 - x))+( (ofGetHeight()/2 - y) * (ofGetHeight()/2 - y) )); //calculates the distance of circle from the center of the window
    float maxDistance = sqrt((ofGetWidth()/2*ofGetWidth()/2)+(ofGetHeight()/2*ofGetHeight()/2));
    
    int maxSections = 8; //determines how many notes the area of the window is split into
    int section = floor(maxSections*(distance/maxDistance)); //pos of circle put into 1 of 8 categories
    
    
    //sets note of each section
    int note;
    
    if (section == 0) note = 48; //middleC
    if (section == 1) note = 50; //D3
    if (section == 2) note = 52; //E3
    if (section == 3) note = 53; //F3
    if (section == 4) note = 55; //G3
    if (section == 5) note = 57; //A4
    if (section == 6) note = 59; //B4
    if (section == 7) note = 60; //C4
    
    return 44100/midi[note]; //sets the length of the delay (in samples) and the pitch of the pluck
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------


double CircleDelay::CircleOscs(int x, int y)
{
    
    //sets the enelope depending on positon and size of circle
    CircleEnvelope.setAttack(y);
    CircleEnvelope.setDecay(1);  // Needs to be at least 1
    CircleEnvelope.setSustain(x);
    CircleEnvelope.setRelease(w*10);
    
    
    
    
    //initialises the oscilators to a noise and a Phazor :P
    double pluck = CirclePluck.noise();
    
    int CurrentCount = CircleCounter.phasor(1, 1, 9);
    CircleCurrentVolume=CircleEnvelope.adsr(1.,CircleEnvelope.trigger);
    
    //______________FOR_TESTING______________
    
    //triggers a pluck
    if (CurrentCount==1) CircleEnvelope.trigger=1;
    else CircleEnvelope.trigger=0;
    
    //______________FOR_TESTING______________
    
    
    return (CircleCurrentVolume*pluck);
}


//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------


float CircleDelay::process(float input){
    
    float output = Buffer[BufferIndex];
    
    int SampleRate = 44100;
    
    Buffer[BufferIndex] = input + (Buffer[BufferIndex] * Feedback);
    
    BufferIndex ++;
    BufferIndex%=calcNote();
    
    return output;
}





