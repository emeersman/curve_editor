//
//  BezierDigit.h
//  CurvedLines
//
//  Created by Emma Meersman on 10/17/14.
//  Copyright (c) 2014 Emma Meersman. All rights reserved.
//

#include "float2.h"

#ifndef CurvedLines_BezierDigit_h
#define CurvedLines_BezierDigit_h

class BezierDigit {
public:
    std::vector<float2> controls;
    
    BezierDigit (int digit) {
        // Set up the control points based on digit
        switch(digit) {
            case 0:
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.7,0.8));
                controls.push_back(float2(0.8,0.7));
                controls.push_back(float2(0.9,0.8));
                controls.push_back(float2(0.8,0.9));
                break;
            case 1: {
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.8,0.8));
                controls.push_back(float2(0.8,0.7));
                break;
            }
            case 2: {
                controls.push_back(float2(0.7,0.85));
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.9,0.85));
                controls.push_back(float2(0.7,0.7));
                controls.push_back(float2(0.71,0.7));
                controls.push_back(float2(0.9,0.7));
                break;
            }
            case 3: {
                controls.push_back(float2(0.7,0.85));
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.9,0.85));
                controls.push_back(float2(0.7,0.8));
                controls.push_back(float2(0.7,0.8));
                controls.push_back(float2(0.9,0.75));
                controls.push_back(float2(0.8,0.7));
                controls.push_back(float2(0.7,0.75));
                break;
            }
            case 4: {
                controls.push_back(float2(0.8,0.7));
                controls.push_back(float2(0.8,0.8));
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.85,1.0));
                controls.push_back(float2(0.7,0.8));
                controls.push_back(float2(0.75,0.8));
                controls.push_back(float2(0.85,0.8));
                break;
            }
            case 5: {
                controls.push_back(float2(0.9,0.9));
                controls.push_back(float2(0.7,0.9));
                controls.push_back(float2(0.7,0.85));
                controls.push_back(float2(0.7,0.8));
                controls.push_back(float2(0.7,0.8));
                controls.push_back(float2(0.9,0.75));
                controls.push_back(float2(0.8,0.7));
                controls.push_back(float2(0.7,0.75));
                break;
            }
            case 6: {
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.8,0.7));
                controls.push_back(float2(0.8,0.7));
                controls.push_back(float2(0.9,0.75));
                controls.push_back(float2(0.85,0.8));
                controls.push_back(float2(0.8,0.8));
                break;
            }
            case 7: {
                controls.push_back(float2(0.7,0.9));
                controls.push_back(float2(0.9,0.9));
                controls.push_back(float2(0.8,0.8));
                controls.push_back(float2(0.8,0.7));
                break;
            }
            case 8: {
                controls.push_back(float2(0.7,0.85));
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.9,0.85));
                controls.push_back(float2(0.9,0.85));
                controls.push_back(float2(0.7,0.75));
                controls.push_back(float2(0.7,0.75));
                controls.push_back(float2(0.8,0.7));
                controls.push_back(float2(0.9,0.75));
                controls.push_back(float2(0.9,0.75));
                controls.push_back(float2(0.7,0.85));
                break;
            }
            case 9: {
                controls.push_back(float2(0.8,0.7));
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.8,0.9));
                controls.push_back(float2(0.7,0.85));
                controls.push_back(float2(0.75,0.8));
                controls.push_back(float2(0.8,0.8));
                break;
            }
        }
    }
    
    // Returns the control points
    std::vector<float2> getControl() {
        return controls;
    }
};

#endif
