//
//  main.cpp
//  CurvedLines
//
//  Created by Emma Meersman on 9/11/14.
//  Copyright (c) 2014 Emma Meersman. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <vector>
#include "float2.h"
#include "BezierDigit.h"
#include "Circle.h"
#include "Curve.h"

using namespace std;


//---------------------------------------------
// Global values throughout the main function
//---------------------------------------------

bool lPressed = false;
bool bPressed = false;
bool pPressed = false;
bool aPressed = false;
bool dPressed = false;
bool fPressed = false;
bool cPressed = false;
bool spacePressed = false;
bool drawSelected = false;
int space = -1;
float2 currClick;
float2 firstPoint;

std::vector<Curve*> curves;
Curve* c;
Curve* selected;
BezierCurve* ones;
BezierDigit* bd = new BezierDigit(0);


//--------------------------
// Event handler functions
//--------------------------

// Set the Bezier Digit counter to be the current number of curves
void setBD() {
    ones = new BezierCurve();
    int size = curves.size();
    bd = new BezierDigit(size);
    std::vector<float2> bdPoints = bd->getControl();
    for( float2 b : bdPoints) {
        ones->addControlPoint(b);
    }
    ones->draw(false);
}

// Display callback responsible for handling elements on the screen
void onDisplay( ) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);        	// clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen
    
    // Draw all curves
    for (Curve *x : curves) {
        if(x == selected) {
            drawSelected = true;
        } else {
            drawSelected = false;
        }
        x->draw(drawSelected);
        x->drawControlPoints(drawSelected);
    }
    
    if(fPressed && selected != nullptr) {
        selected->drawFill(true);
    }
    
    setBD();
    
	glutSwapBuffers();                     		// Swap buffers for double buffering
	
}

// Select one of the curves on the screen based on mouse click
void selectObject(int x, int y){
    float screenX = (float)640.0/2.0;
    float screenY = (float)480.0/2.0;
    float xf = float((float)(x-screenX)/screenX);
    float yf = -1.0 * float((float)(y-screenY)/screenY);
    
    // Iterate through curves and their control points to see if click was nearby
    int i = 0;
    for(Curve* curve : curves) {
        for(float i = 0; i <= 1; i += 0.05) {
            float2 currPoint = curve->getPoint(i);
            float distance = sqrt(pow(currPoint.x - xf,2)+pow(currPoint.y-yf,2));
            if(distance < 0.08) {
                selected = curve;
                space = i;
                break;
            }
        }
        for(int j = 0; j < curve->getControlSize(); ++j){
            float2 curr = curve->getControlPoint(j);
            if(curr.x != 0.0 && curr.y != 0.0) {
                float distance = sqrt(pow(curr.x - xf,2)+pow(curr.y-yf,2));
                if(distance < 0.08) {
                    selected = curve;
                    space = i;
                    break;
                }
            }
        }
        ++i;
    }
}


// Events relating to mouse clicks
void onMouse(int button, int state, int x, int y) {
    int viewportRect[4];
    glGetIntegerv(GL_VIEWPORT, viewportRect);
    currClick.x = x * 2.0 / viewportRect[2] - 1.0;
    currClick.y = -y * 2.0 / viewportRect[3] + 1.0;
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(lPressed || bPressed || pPressed) { // Draw new curve
            float2 lPoint = currClick;
            selected->addControlPoint(lPoint);
        } else if (aPressed) { // Add control point to selected curve
            if(selected != nullptr) {
                float2 aPoint = currClick;
                selected->addControlPoint(aPoint);
            }
        } else if (dPressed) { // Delete control point from selected curve
            if(selected != nullptr) {
                float2 dPoint = currClick;
                selected->removeControlPoint(dPoint);
            }
        } else { // Select object at click and redraw it as selected
            selectObject(x, y);
            if(selected != nullptr) {
                selected->draw(true);
                selected->drawControlPoints(true);
             }
        }
    }
    
    glutPostRedisplay();
}

// Events when mouse moves with clicked button
void onMouseMotion(int x, int y) {
    int viewportRect[4];
    glGetIntegerv(GL_VIEWPORT, viewportRect);
    
    // Modify the offset vector of the selected curve
    if(selected != nullptr) {
        float xOff = (x * 2.0 / viewportRect[2] - 1.0) - currClick.x;
        float yOff = (-y * 2.0 / viewportRect[3] + 1.0) - currClick.y;
        selected->offset.x = xOff;
        selected->offset.y = yOff;
    }
    
    glutPostRedisplay();
}

// Conditions for different keys pressed
void onKeyboard(unsigned char key, int x, int y) {
    if(key == 'l') { // Draw new Lagrange curve
        if(selected != nullptr) {
            c = selected;
        }
		if(!lPressed)
		{
	        selected = new LagrangeCurve();
			curves.push_back(selected);
		}
        lPressed = true;
    } if(key == 'b') { // Draw new Bezier curve
        if(selected != nullptr) {
            c = selected;
        }
		if(!bPressed)
		{
	        selected = new BezierCurve();
			curves.push_back(selected);
		}
        bPressed = true;
    } if(key == 'p') { // Draw new Polyline
        if(selected != nullptr) {
            c = selected;
        }
		if(!pPressed)
		{
	        selected = new Polyline();
			curves.push_back(selected);
		}
        pPressed = true;
    } if(key == 32) { // Space changes the selected curve to the next one on screen
        if(!spacePressed) {
            ++space;
            if(space == curves.size()) {
                space = 0;
            }
            selected = curves.at(space);
        }
        spacePressed = true;
    } if(key == 'c') { // Create subdivision curve from current selected curve
        if(selected != nullptr) {
            selected->subdivide();
        }
        cPressed = true;
    } if(key == 'a') {
        aPressed = true;
    } if (key == 'd') {
        dPressed = true;
    } if (key == 'f') {
        fPressed = true;
    }
    
    glutPostRedisplay();
}

// Events when keys are released
void onKeyboardUp(unsigned char key, int x, int y) {
    // No curves with two control points or less
    if(c->getControlSize() <= 2) {
        curves.pop_back();
    }
    if(lPressed)
        lPressed = false;
    if(bPressed)
        bPressed = false;
    if(pPressed)
        pPressed = false;
    if(spacePressed)
        spacePressed = false;
    if(aPressed)
        aPressed = false;
    if(dPressed)
        dPressed = false;
    if(fPressed)
        fPressed = false;
    if(cPressed)
        cPressed = false;
    
    glutPostRedisplay();
}

//--------------------------------------------------------
// The entry point of the application
//--------------------------------------------------------
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);                 		// GLUT initialization
    glutInitWindowSize(640, 480);               // Initial window size
    glutInitWindowPosition(100, 100);           // Set initial position
    
    // Image = 8 bit R,G,B + double buffer + depth buffer
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("Draw ALL the Curves!");        	// Window is born
    
    glutDisplayFunc(onDisplay);                	// Register event handlers
    glutMouseFunc(onMouse);                     // Mouse click event handler
    glutMotionFunc(onMouseMotion);              // Mouse movement event handler
    glutKeyboardFunc(onKeyboard);               // Key press event handler
    glutKeyboardUpFunc(onKeyboardUp);           // Key release event handler
    
    glutMainLoop();                    			// Event loop
    return 0;
}