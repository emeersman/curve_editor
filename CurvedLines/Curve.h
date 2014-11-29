//
//  Curve.h
//  OpenGLTesting
//
//  Created by Emma Meersman on 9/18/14.
//  Copyright (c) 2014 Emma Meersman. All rights reserved.
//

#ifndef __OpenGLTesting__Curve__
#define __OpenGLTesting__Curve__

#pragma once

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "float2.h"

#endif /* defined(__OpenGLTesting__Curve__) */

class Curve {
public:
    float2 offset; // Offset vector used for mouse dragging

    // Return curve point at parameter t in [0,1]
    virtual float2 getPoint(float t)=0;
    
    // Return curve derivative at parameter t
    virtual float2 getDerivative(float t)=0;
    
    // Return size of the controlPoints vector
    virtual int getControlSize() = 0;
    
    // Color values specified for each type of curve
    virtual float getRed()=0;
    virtual float getGreen()=0;
    virtual float getBlue()=0;
    
    // Overwritten for drawing subdivision curves
    virtual void subdivide() {};
    
    // Draw function to make curves
    virtual void draw(bool selected)
    {
        if (selected) {
            glColor3d(0,0,1);
            glLineWidth(2.0);
        } else {
            glColor3d(getRed(), getGreen(), getBlue());
            glLineWidth(1.0);
        }
        float2 a;
        float2 b;
        glBegin(GL_LINE_STRIP);
        // Draw a line strip of small segments along the curve
        a = getPoint(0);
        // Take offset into account for dragging
        glVertex2d(a.x + offset.x, a.y + offset.y);
        for(int i = 1; i <= 100; ++i) {
            // Draw strips around a point
            a = getPoint(i/100.0);
            glVertex2d(a.x + offset.x, a.y + offset.y);
        }
        glEnd();
    }
    
    // Fills curve by connecting the first and last points
    virtual void drawFill(bool selected)
    {
        if (selected) {
            glColor3d(0,0,1);
        } else {
            glColor3d(getRed(), getGreen(), getBlue());
        }
        float2 a;
        float2 b;
        glBegin(GL_TRIANGLE_FAN);
        // Draw a line strip of small segments along the curve
        a = getPoint(0);
        glVertex2d(a.x + offset.x, a.y + offset.y);
        for(int i = 1; i <= 100; ++i) {
            // Draw strips around a point
            a = getPoint(i/100.0);
            glVertex2d(a.x + offset.x, a.y + offset.y);
        }
        glEnd();
    }
    
    virtual void drawControlPoints(bool selected){}
    
    virtual float2 getControlPoint(int i) {
        float2 point(0,0);
        return point;
    }
    
    virtual void addControlPoint(float2 p) {}
    
    virtual void removeControlPoint(float2 p) {}
    
    // Visual representation of derivative at specified location along curve
    void drawTracker(float t)
    {
        glBegin(GL_POINT);
        float2 r = getPoint(t);
        glColor3d(getRed(), getGreen(), getBlue());
        glPointSize(10);
        glVertex2d(r.x, r.y);
        glEnd();
        
        glBegin(GL_LINES);
        float2 d = getDerivative(t);
        glVertex2d(r.x, r.y);
        glVertex2d(r.x + d.x, r.y + d.y);
        glEnd();
    }
};


class Freeform : public Curve
{
protected:
    std::vector<float2> controlPoints; // Vector of points that make up a curve
    
public:
    virtual float2 getPoint(float t)=0;
    
    // Appends specified control point to the end of the curve
    virtual void addControlPoint(float2 p)
    {
        controlPoints.push_back(p);
    }
    
    // Deletes specified control point from the curve
    virtual void removeControlPoint(float2 p) {
        int i = 0;
        for(float2 q : controlPoints) {
            float dist = sqrt(pow(p.x - q.x,2.0)+pow(p.y-q.y,2.0));
            if(dist < 0.05) {
                controlPoints.erase(controlPoints.begin()+i);
                break;
            }
            ++i;
        }
    }
    
    // Draws visual representation of the control points of the curve
    void drawControlPoints(bool selected){
        // Draw points at control points
        glPointSize(10);
        glBegin(GL_POINTS);
        if(selected) {
            glColor3d(0,0,1);
        } else {
            glColor3d(getRed(),getGreen(),getBlue());
        }
        for(float2 p : controlPoints) {
            glVertex2d(p.x + offset.x, p.y + offset.y);
            
        }
        glEnd();
    }
};


class BezierCurve : public Freeform
{
public:
    // Draws in red color
    virtual float getRed(){
        return 1.0;
    }
    virtual float getGreen(){
        return 0.0;
    }
    virtual float getBlue(){
        return 0.0;
    }
    
    // Return curve derivative at parameter t
    virtual float2 getDerivative(float t) {
        float2 r(0.0, 0.0);
        int i = 0;
        for(float2 p : controlPoints) {
            r += p*bernsteinDerivative(i, (int)controlPoints.size()-1, t);
            ++i;
        }
        return r;
    }
    
    // Compute weights for the curve along the control points
    static double bernstein(int i, int n, double t) {
        if(n == 1) {
            if(i == 0)
                return 1-t;
            if(i == 1)
                return t;
            return 0;
        }
        if(i < 0 || i > n)
            return 0;
        return (1 - t) * bernstein(i, n-1, t) + t * bernstein(i-1, n-1, t);
    }
    
    static double bernsteinDerivative(int i, int n, double t) {
        if(n == 1) {
            if(i == 0)
                return -1;
            if(i == 1)
                return 1;
            return 0;
        }
        if(i < 0 || i > n)
            return 0;
        return (-1 * bernsteinDerivative(i, n-1, t) + (1-t)* bernsteinDerivative(i, n-1, t))
        + (bernstein(i-1, n-1, t) + t*bernsteinDerivative(i-1, n-1, t));
    }
    
    // Weight a point along the curve based on the weight of all other parts of the curve
    float2 getPoint(float t) {
        float2 r(0.0, 0.0);
        int i = 0;
        for(float2 p : controlPoints) {
            r += p*bernstein(i, (int)controlPoints.size()-1, t);
            ++i;
        }
        return r;
    }
    
    int getControlSize() {
        return controlPoints.size();
    }
};


class LagrangeCurve : public Freeform
{
private:
    // These are the values where the curve intersects the points at time t, curve goes from t=0 to t=1
    // It's enough to make evenly distributed knot values from 0 to 1
    std::vector<float> knots;
    
public:
    // This type of curve is drawn in green
    virtual float getRed(){
        return 0.0;
    }
    virtual float getGreen(){
        return 1.0;
    }
    virtual float getBlue(){
        return 0.0;
    }
    
    // Knots vector is also reweighted when adding a control point
    virtual void addControlPoint(float2 p) {
        controlPoints.push_back(p);
        knots.push_back(1.0);
        if(knots.size() > 0) {
            for(int k = 0; k < knots.size()-1; ++k) {
                knots[k] = 1.0*k/(knots.size()-1);
            }
        }
    }
    
    // Deleting a control point removes the corresponding point from the knots vector
    virtual void removeControlPoint(float2 p) {
        int i = 0;
        for(float2 q : controlPoints) {
            float dist = sqrt(pow(p.x-q.x,2.0) + pow(p.y-q.y,2.0));
            if(dist < 0.05) {
                controlPoints.erase(controlPoints.begin()+i);
                break;
            }
            ++i;
        }
        knots.pop_back();
        if(knots.size() > 0) {
            for(int k = 0; k < knots.size(); ++k) {
                if(k == knots.size()-1)
                    knots[k] = 1.0;
                knots[k] = 1.0*k/(knots.size()-1);
            }
        }
    }
    
    // Weight for the points in the Lagrange curve
    double lWeights(int i, int n, double t) {
        float numer = 1;
        float denom = 1;
        for(int j = 0; j < knots.size(); ++j) {
            if(j != i) {
                numer *= (t - knots[j]);
                denom *= (knots[i] - knots[j]);
            }
        }
        return numer/denom;
    }
    
    virtual float2 getPoint(float t) {
        float2 r(0.0, 0.0);
        int i = 0;
        for(float2 p : controlPoints) {
            r += p*lWeights(i, (int)controlPoints.size()-1, t);
            ++i;
        }
        return r;
    }
    
    int getControlSize() {
        return controlPoints.size();
    }
    
    // Return curve derivative at parameter t
    virtual float2 getDerivative(float t){return float2(0,0);}
    
};


class Polyline : public Freeform
{
public:
    // This curve is drawn in pink
    virtual float getRed(){
        return 1.0;
    }
    virtual float getGreen(){
        return 0.0;
    }
    virtual float getBlue(){
        return 1.0;
    }
    
    // Overrides draw function because Polylines just draw lines directly between all
    // adjacent control points
    virtual void draw(bool selected) {
        if(selected) {
            glColor3d(0,0,1);
            glLineWidth(2.0);
        } else {
            glColor3d(getRed(),getGreen(),getBlue());
            glLineWidth(1.0);
        }
        glBegin(GL_LINE_STRIP);
        float2 prev(0,0);
        for(float2 p : controlPoints) {
            glVertex2d(p.x + offset.x, p.y + offset.y);
        }
        glEnd();
    }
    
    virtual void drawFill(bool selected) {
        glBegin(GL_TRIANGLE_FAN);
        float2 prev(0,0);
        if(selected) {
            glColor3d(0,0,1);
        } else {
            glColor3d(getRed(),getGreen(),getBlue());
        }
        for(float2 p : controlPoints) {
            glVertex2d(p.x + offset.x, p.y + offset.y);
        }
        glEnd();
    }
    
    virtual float2 getPoint(float t){return float2(0.0,0.0);};
    
    virtual float2 getControlPoint(int i) {
        float2 point(0,0);
        int j = 0;
        for(float2 p : controlPoints) {
            if(i == j) {
                point = p;
            }
            ++j;
        }
        return point;
    }
    
    int getControlSize() {
        return controlPoints.size();
    }
    
    // return curve derivative at parameter t
    virtual float2 getDerivative(float t){return float2(0,0);}
    
    // Support for Subdivision Curves
    virtual void subdivide() {
        std::vector<float2> newPoints;
        float2 s;
        float2 t;
        float2 q;
        float2 r;
        
        // Keep the first control point
        newPoints.push_back(controlPoints[0]);
        for(unsigned int i=0;i<(controlPoints.size()-1);++i) {
            s = controlPoints.at(i);
            t = controlPoints.at(i+1);
            
            // Average the two adjacent points to make two new ones in between them
            q.x = 0.75f*s.x + 0.25f*t.x;
            q.y = 0.75f*s.y + 0.25f*t.y;
                
            r.x = 0.25f*s.x + 0.75f*t.x;
            r.y = 0.25f*s.y + 0.75f*t.y;
            
            newPoints.push_back(q);
            newPoints.push_back(r);
        }
        
        // Keep the last control point
        newPoints.push_back(controlPoints[controlPoints.size()-1]);
        
        // Set the new points array to be the new control points of the curve
        controlPoints = newPoints;
    }
};

