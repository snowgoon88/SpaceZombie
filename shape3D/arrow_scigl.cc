/*
 * Copyright (C) 2008 Nicolas P. Rougier
 * Modified Alain 2011
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "arrow_scigl.h"
#include "font.h"
#include <iostream>

// ******************************************************************** CREATION
Arrow::Arrow( void ) : Object()
{
  set_visible( true );
  set_size( 2, 2, 2 );
  Object::set_position( 0, 0, 0 );
  set_fg_color( 1, 0, 0, 1);
  set_br_color( 0, 0, 0, 1);
  set_bg_color( 1, 1, 1, 1);
  alpha_ = 1.0f;
  fade_in_delay_ = 0;
  fade_out_delay_ = 0;

  _fg_text = false;
  set_text( "" );
  
  compute_from_vec( TVec3(1,0,0) );

  std::ostringstream oss;
  oss << "Arrow_" << id_;
  set_name (oss.str());
}
Arrow::Arrow( TVec3 v ) : Object()
{
  set_visible( true );
  set_size( 2, 2, 2 );
  Object::set_position( 0, 0, 0 );
  set_fg_color( 1, 0, 0, 1);
  set_br_color( 0, 0, 0, 1);
  set_bg_color( 1, 1, 1, 1);
  alpha_ = 1.0f;
  fade_in_delay_ = 0;
  fade_out_delay_ = 0;
  
  compute_from_vec( v );

  _fg_text = false;
  set_text( "" );

  std::ostringstream oss;
  oss << "Arrow_" << id_;
  set_name (oss.str());
}
Arrow::~Arrow( void )
{}
// ********************************************************************** RENDER
void Arrow::render( void )
{
  compute_visibility();
  if (not get_visible()) return;

  // faces used for head
  struct face {
    float vertices[4*3];
    float normal[3];
    float z;
    char id_str[10];
    static int compare (const void *a, const void *b) {
      const face *da = (const face *) a;
      const face *db = (const face *) b;
      return ((*da).z > (*db).z) - ((*da).z < (*db).z);
      //return ((*da).z - (*db).z);
    }
  };
  int nb_head_faces = 4;
  float sh = 1.0;            // scale of head   
  float wh = 0.025 * sh;     // width of head
  float lh = 1 - 0.1 * sh;   // length og head
  // front face have vertex in couter-clockwise order
  face head_faces[6] = {
    // 4 triangles make the head tip
    {{1,0,0,  lh,0,wh,  lh,-wh,0}, { 0, 0, 0}, 0, "1"},
    {{1,0,0,  lh,-wh,0,  lh,0,-wh}, { 0, 0, 0}, 0, "2"},
    {{1,0,0,  lh,0,-wh,  lh,wh,0}, { 0, 0, 0}, 0, "3"},
    {{1,0,0,  lh,wh,0,  lh,0,wh}, { 0, 0, 0}, 0, "4"}
  };

  // save Light Attributes and remove lighting to get "full" RGB
  // colors
  glPushAttrib( GL_LIGHTING_BIT );
  glDisable( GL_LIGHTING );
    
  // save transformation matrix, then translate and scale.
  glPushMatrix();
  glTranslatef (get_position().x, get_position().y, get_position().z);
  glRotatef( to_deg(_ang_z1), 0, 0, 1); // rotation around 0z
  glRotatef( to_deg(_ang_y2), 0, 1 ,0); // rotation around 0y
  glScalef ( _length, 1.0, 1.0 );

    
  // draw line
  glColor4fv( get_br_color().data );
  glLineWidth( 1.0 );
  glBegin( GL_LINES ); {
    glVertex3f( 0, 0, 0 );
    glVertex3f( 1, 0, 0 );
  }
  glEnd();

  glColor4fv (get_fg_color().data);
  // draw text
  if( _fg_text ) {
    glPushAttrib( GL_ENABLE_BIT );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    FontPtr font = FontPtr( Font::Font32() );
    glPushMatrix();
    glTranslatef ( 1.2f, 0.0f, 0.0f);
    glScalef( 0.0025, 0.0025, 0.0025 );
    font->render (_text);
    glPopMatrix();
    glPopAttrib();
  }

  // draw head
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
  glBegin (GL_TRIANGLES); {
    for (int i=0; i<nb_head_faces; i++) {
      //glNormal3f (head_faces[i].normal[0], head_faces[i].normal[1], head_faces[i].normal[2]);
      glVertex3f (head_faces[i].vertices[0], head_faces[i].vertices[1], head_faces[i].vertices[2]);
      glVertex3f (head_faces[i].vertices[3], head_faces[i].vertices[4], head_faces[i].vertices[5]);
      glVertex3f (head_faces[i].vertices[6], head_faces[i].vertices[7], head_faces[i].vertices[8]);
    }
  } glEnd();
    

  // restore transformation matrix
  glPopMatrix();
  // restore attributes
  glPopAttrib();

}
void Arrow::render( float view_rotation[4][4] )
{
  compute_visibility();
  if (not get_visible()) return;

  // faces used for head
  struct face {
    float vertices[4*3];
    float normal[3];
    float z;
    char id_str[10];
    static int compare (const void *a, const void *b) {
      const face *da = (const face *) a;
      const face *db = (const face *) b;
      return ((*da).z > (*db).z) - ((*da).z < (*db).z);
      //return ((*da).z - (*db).z);
    }
  };
  int nb_head_faces = 4;
  float sh = 1.0;            // scale of head   
  float wh = 0.025 * sh;     // width of head
  float lh = (- 0.1 * sh);   // length og head
  // front face have vertex in couter-clockwise order
  face head_faces[6] = {
    // 4 triangles make the head tip
    {{0,0,0,  lh,0,wh,  lh,-wh,0}, { 0, 0, 0}, 0, "1"},
    {{0,0,0,  lh,-wh,0,  lh,0,-wh}, { 0, 0, 0}, 0, "2"},
    {{0,0,0,  lh,0,-wh,  lh,wh,0}, { 0, 0, 0}, 0, "3"},
    {{0,0,0,  lh,wh,0,  lh,0,wh}, { 0, 0, 0}, 0, "4"}
  };

  // save Light Attributes and remove lighting to get "full" RGB
  // colors
  glPushAttrib( GL_LIGHTING_BIT );
  glDisable( GL_LIGHTING );
    
  // save transformation matrix, then translate and scale.
  glPushMatrix();
  glTranslatef (get_position().x, get_position().y, get_position().z);
  glRotatef( to_deg(_ang_z1), 0, 0, 1); // rotation around 0z
  glRotatef( to_deg(_ang_y2), 0, 1 ,0); // rotation around 0y
  //glScalef ( _length, 1.0, 1.0 );

    
  // draw line
  glColor4fv( get_br_color().data );
  glLineWidth( 1.0 );
  glBegin( GL_LINES ); {
    glVertex3f( 0, 0, 0 );
    glVertex3f( _length, 0, 0 );
  }
  glEnd();

  glColor4fv (get_fg_color().data);
  // draw text
  if( _fg_text ) {
    glPushAttrib( GL_ENABLE_BIT );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    FontPtr font = FontPtr( Font::Font32() );
    glPushMatrix();
    glTranslatef ( _length + 0.2f, 0.0f, 0.0f);
    glScalef( 0.0025, 0.0025, 0.0025 );
    
    glRotatef( to_deg(-_ang_y2), 0, 1 ,0); // rotation around 0y
    glRotatef( to_deg(-_ang_z1), 0, 0, 1); // rotation around 0z
    glMultTransposeMatrixf( &view_rotation[0][0] );

    font->render (_text);
    glPopMatrix();
    glPopAttrib();
  }

  // draw head
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
  glTranslatef( _length, 0, 0 );
  glBegin (GL_TRIANGLES); {
    for (int i=0; i<nb_head_faces; i++) {
      //glNormal3f (head_faces[i].normal[0], head_faces[i].normal[1], head_faces[i].normal[2]);
      glVertex3f (head_faces[i].vertices[0], head_faces[i].vertices[1], head_faces[i].vertices[2]);
      glVertex3f (head_faces[i].vertices[3], head_faces[i].vertices[4], head_faces[i].vertices[5]);
      glVertex3f (head_faces[i].vertices[6], head_faces[i].vertices[7], head_faces[i].vertices[8]);
    }
  } glEnd();
    

  // restore transformation matrix
  glPopMatrix();
  // restore attributes
  glPopAttrib();

}
// ********************************************************************* COMPUTE
void Arrow::compute_from_vec( TVec3 v )
{
  ang_from_vec( v, _ang_z1, _ang_y2 );
  // length
  _length = v.norm();
}
void Arrow::set_position( TVec3 p )
{
  Object::set_position( p(0), p(1), p(2) );
}
// *********************************************************************SET_TEXT
void Arrow::set_text( std::string text )
{
  _text = text;
}
// *****************************************************************************
