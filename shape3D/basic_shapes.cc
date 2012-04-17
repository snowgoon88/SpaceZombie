// -*- coding: utf-8 -*-

#if defined(__APPLE__)
#   include <GL/glew.h>
#   include <OpenGL/gl.h>
#else
#   include <GL/glew.h>
#   include <GL/gl.h>
#endif

#include "basic_shapes.h"
#include "math.h"

//*********************************************************************** CIRCLE
void draw_circle(float cx, float cy, float r, int num_segments)
{ 
  float theta = 2 * 3.1415926 / float(num_segments); 
  float c = cosf(theta);//precalculate the sine and cosine
  float s = sinf(theta);
  float t;
  
  float x = r;//we start at angle = 0 
  float y = 0; 
    
  glBegin(GL_LINE_LOOP); { 
    for(int ii = 0; ii < num_segments; ii++) { 
      glVertex2f(x + cx, y + cy);//output vertex 
      
      //apply the rotation matrix
      t = x;
      x = c * x - s * y;
      y = s * t + c * y;
    }
  } 
  glEnd(); 
}
//******************************************************************************
