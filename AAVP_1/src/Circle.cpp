//
//  Circle.cpp
//  AAVP_1
//
//  Created by Muiredach O'Riain on 12/01/2017.
//
//

#include <stdio.h>
#include "ofMain.h"
#include "Circle.h"

Circle::Circle(int _x, int _y, int _w, ofColor _colour): x(_x), y(_y), w(_w), colour(_colour){
    

}

void Circle::draw()
{
    ofCircle( x, y, w);
}