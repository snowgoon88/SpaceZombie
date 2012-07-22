// -*- coding: utf-8 -*-

#include "player_scigl.h"
#include <iostream>
#include <sstream>

//********************************************************************* CREATION
/** Creation */
PlayerScigl::PlayerScigl( PlayerPtr model ) : Observer(), Object()
{
  _model = model;

  set_fg_color( 0.8, 0.0, 0.8, 1.0 );

  std::ostringstream oss;
  oss << "PlayerScigl_" << id_;
  set_name (oss.str());
}
/** Destruction */
PlayerScigl::~PlayerScigl()
{
}
//*********************************************************************** STRING
std::string PlayerScigl::dump_string()
{
  std::stringstream ss;
  
  ss << "PlayerScigl::dump_string()" << "\n";
  
  return ss.str();
}
//*********************************************************************** RENDER
void PlayerScigl::render()
{
  glPushAttrib (GL_ENABLE_BIT);
  glDisable (GL_TEXTURE_2D);
  glDisable (GL_LIGHTING);
  glEnable (GL_DEPTH_TEST);
  glDepthMask (GL_TRUE);

  // face for player
  struct face {
    float vertices[4*3];
  };
  int nb_player_faces = 6;
  face player_faces[6] = {
    {{ 0.0,  0.0,  0.5,    -0.2, -0.1, 0.5,     0.3,  0.0,  0.5,  -0.2,  0.1,  0.5}},
    {{ 0.0,  0.0,  0.0,    -0.2,  0.1, 0.0,     0.3,  0.0,  0.0,  -0.2, -0.1,  0.0}},
    {{ 0.0,  0.0,  0.0,    -0.2, -0.1, 0.0,    -0.2, -0.1,  0.5,   0.0,  0.0,  0.5}},
    {{-0.2, -0.1,  0.0,     0.3,  0.0, 0.0,     0.3,  0.0,  0.5,  -0.2, -0.1,  0.5}},
    {{ 0.3,  0.0,  0.0,    -0.2,  0.1, 0.0,    -0.2,  0.1,  0.5,   0.3,  0.0,  0.5}},
    {{-0.2,  0.1,  0.0,     0.0,  0.0, 0.0,     0.0,  0.0,  0.5,  -0.2,  0.1,  0.5}}
  };

  // set pose
  glPushMatrix();
  glTranslatef( _model->_pos(0), _model->_pos(1), _model->_pos(2) );
  glRotatef( to_deg( _model->_ang_Oz), 0.0f, 0.0f, 1.0f);
  
  // draw player
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);  
  // Color of front face
  glColor4fv (get_fg_color().data);
  glBegin( GL_QUADS ); {
    for( int i = 0; i <nb_player_faces; ++i) {
      glVertex3f(player_faces[i].vertices[0], player_faces[i].vertices[1], player_faces[i].vertices[2]);
      glVertex3f(player_faces[i].vertices[3], player_faces[i].vertices[4], player_faces[i].vertices[5]);
      glVertex3f(player_faces[i].vertices[6], player_faces[i].vertices[7], player_faces[i].vertices[8]);
      glVertex3f(player_faces[i].vertices[9], player_faces[i].vertices[10], player_faces[i].vertices[11]);
    }
  }
  glEnd();
  glPopMatrix();
  glPopAttrib();
}
//*********************************************************************** UPDATE
void PlayerScigl::update( int signal )
{
}
//******************************************************************************
