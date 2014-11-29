//
//  Circle.h
//  OpenGLTesting
//
//  Created by Emma Meersman on 9/18/14.
//  Copyright (c) 2014 Emma Meersman. All rights reserved.
//

#ifndef __OpenGLTesting__Circle__
#define __OpenGLTesting__Circle__

#pragma once
#include <iostream>
#include <math.h>
#include "float2.h"
#include "Curve.h"

#endif /* defined(__OpenGLTesting__Circle__) */

class Circle : public Curve {
    // center and radius stored in members
public:
    float2 center;
    float radius;
    // constructor to initialize members
    
    Circle():center(0.0f,0.0f),radius(0.0){}
    Circle(float2 center, float radius):center(center),radius(radius){}
    
    float2 getPoint(float t)
    {
        float scaleT = t*(2*M_PI);
        float x = radius*cos(scaleT);
        float y = radius*sin(scaleT);
        return float2(x,y);
    }
    
    float2 getDerivative(float t) {
        float scaleT = t*(2*M_PI);
        float x = -scaleT*radius*sin(scaleT);
        float y = scaleT*radius*cos(scaleT);
        return float2(x,y);
    }
};
