//
//  Circle.h
//  AAVP_1
//
//  Created by Muiredach O'Riain on 12/01/2017.
//
//

#ifndef Circle_h
#define Circle_h


class Circle {
public:
    //constuctor
    explicit Circle(int _x, int _y, int _w, ofColor colour);
    
    // Methods
    void draw();
    
    //properties
    ofColor colour;
    int x;
    int y;
    int w;
};



#endif /* Circle_h */
