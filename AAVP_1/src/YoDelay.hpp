//
//  YoDelay.hpp
//  AAVP_1
//
//  Created by Muiredach O'Riain on 16/01/2017.
//
//

#ifndef YoDelay_hpp
#define YoDelay_hpp
#include <array>

using std::array;

class YoDelay{
    
public:
    
    array< float, 44100*2 > Buffer; //this sets the size of the delay buffer to 2 seconds (considering a SamleRate of 44100Hz
    float Feedback;
    int BufferIndex, BufferLength;
    
    YoDelay(/*cum*/)
    {
        BufferIndex = 0;
        Feedback = 0.8;     //ammount that the sound decreases in intensity each loop
        BufferLength = 1000; //sets the length of the delay (in samples) and the pitch of the pluck
    }
    
    float process(float input)
    {
        float output = Buffer[BufferIndex];                                     //
        
        Buffer[BufferIndex] = input + (Buffer[BufferIndex] * Feedback);
        
        BufferIndex ++;
        BufferIndex%=BufferLength;
        
        //cout << Buffer[BufferIndex] << endl;
        
        return output;
        
    }
    
};

#include <stdio.h>

#endif /* YoDelay_hpp */
