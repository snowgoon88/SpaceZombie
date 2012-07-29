/* -*- coding: utf-8 -*- */

// -*- coding: utf-8 -*-

#include "tag_scigl.h"
#include <iostream>
#include <sstream>
#include "font.h"

//********************************************************************* CREATION
/** Creation */
TagScigl::TagScigl( std::string label, TVec3 *pos, float height )
{
  _label = label;
  _pos = pos;
  _height = height;

  set_fg_color( 0, 0, 0, 1);
  set_br_color( 1, 0, 0, 1);
  set_bg_color( 1, 1, 1, 1);

  _fg_selected = false;

  std::ostringstream oss;
  oss << "TagScigl_" << id_;
  set_name (oss.str());
}
/** Destruction */
TagScigl::~TagScigl()
{
}
//*********************************************************************** RENDER
void TagScigl::render (void)
{
  /* nothing */
}
void TagScigl::render( float view_rotation[4][4] )
{
  // save Light Attributes and remove lighting to get "full" RGB
  // colors
  glPushAttrib( GL_LIGHTING_BIT );
  glDisable( GL_LIGHTING );
    
  // save transformation matrix, then translate and scale.
  glPushMatrix();
  glTranslatef( (*_pos)[0], (*_pos)[1], (*_pos)[2] );
  //std::cout << "TagScigl(x,y,z)= " <<  (*_pos)[0] << ", " << (*_pos)[1] << ", " << (*_pos)[2] << "\n";

  // Restore rotation to face viewer
  glMultTransposeMatrixf( &view_rotation[0][0] );

  // draw line
  if( _fg_selected == false ) {
    glColor4fv( get_fg_color().data );
  }
  else {
    glColor4fv( get_br_color().data );
  }
  glLineWidth( 0.5 );
  glBegin( GL_LINES ); {
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, _height, 0 );
  }
  glEnd();
  
  // draw text
  glPushAttrib( GL_ENABLE_BIT );
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  glEnable( GL_TEXTURE_2D );
  glEnable( GL_BLEND );
  FontPtr font = FontPtr( Font::Font32() );
  glPushMatrix();
  glTranslatef ( 0.0f, _height+0.0f, 0.0f);
  // Need to scale doxn ! (Why ??)
  glScalef( 0.0025, 0.0025, 0.0025 );
  font->render ( _label );
  glPopMatrix();
  glPopAttrib();

  // restore transformation matrix
  glPopMatrix();
  // restore attributes
  glPopAttrib();
}
//************************************************************************** SET
void TagScigl::set_position( TVec3 *pos, float height )
{
  _pos = pos;
  _height = height;
}
void TagScigl::set_label( std::string label )
{
  _label = label;
}
//********************************************************************* SELECTED
void TagScigl::set_selected( bool selected )
{
  _fg_selected = selected;
}
//******************************************************************************
