//
//  Crusher.cpp
//  AAVP_CRUSHER
//
//  Created by Muiredach O'Riain on 21/01/2017.
//
//

#include "Crusher.hpp"

Crusher::Crusher()
{
}
double Crusher::crusher(double input, float normfreq, int bits, float clipLevel){
    
    //normfreq might have to be the samplerate?
    
    float step = pow(0.5, bits);
    double last = 0;
    
    if (Phase.phasor(normfreq) >= clipLevel) {
        last = step * floor(input/step + 0.5);
    }
    
    return last;
}