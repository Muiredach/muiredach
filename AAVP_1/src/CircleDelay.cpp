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
    Feedback = 0.9;     //ammount that the sound decreases in intensity each loop
    
}




void CircleDelay::draw()
{
    ofCircle(x,y,w);
}


//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------


double CircleDelay::CircleOscs()
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
    
    Buffer[BufferIndex] = input + (Buffer[BufferIndex] * Feedback);
    
    BufferIndex ++;
    BufferIndex%=BufferLength;
    //cout << Buffer[BufferIndex] << endl;
    
    return output;
}


//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------



void CircleDelay::calcNote(){
    
    int SampleRate = 44100;
    
    
    //fills an array with all note frequency values
    float midi[127];
    int a = 440;
    for (int i= 0; i < 127; ++i)
    {
        midi[i] = (a / 32) * (2 ^ ((i - 9) / 12));
    }
    
    
    float distance = sqrt(((ofGetWidth()/2 - x)*(ofGetWidth()/2 - x))+( (ofGetHeight()/2 - y) * (ofGetHeight()/2 - y) )); //calculates the distance of circle from the center of the window
    float maxDistance = sqrt((ofGetWidth()*ofGetWidth())+(ofGetHeight()*ofGetHeight()));
    
    int maxSections = 7; //determines how many notes the area of the window is split into
    int section = roundf(7*(distance/maxDistance)); //pos of circle put into 1 of 8 categories
    
    
    //sets note of each section
    int note;
    
    if (section == 0) note == 60; //middleC
    if (section == 1) note == 62; //D4
    if (section == 2) note == 64; //E4
    if (section == 3) note == 65; //F4
    if (section == 4) note == 67; //G4
    if (section == 5) note == 69; //A5
    if (section == 6) note == 71; //B5
    if (section == 7) note == 72; //C5
    
    BufferLength = roundf(midi[note]/SampleRate); //sets the length of the delay (in samples) and the pitch of the pluck
}






