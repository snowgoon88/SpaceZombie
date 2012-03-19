// -*- coding: utf-8 -*-

#include "world_scigl.h"
#include "shapes.h"

// *****************************************************************************
// WorldSCIGL::WorldSCIGL() : Observer(), Object()
// {
//   set_visible (true);
//   set_size (1,1,1);
//   set_position (0,0,0);
//   set_fg_color (0.0, 0.0, 0.8, 1.0);  // face up : blue 
//   set_br_color (0.0, 0.0, 0.0, 1.0);  // border : black
//   set_bg_color (0.6, 0.6, 0.6, 1.0);  // face down : light_grey
//   alpha_ = 1.0f;
//   fade_in_delay_ = 0;
//   fade_out_delay_ = 0;

//   // TODO _model = ??

//   std::ostringstream oss;
//   oss << "World_" << id_;
//   set_name (oss.str());

// }
WorldSCIGL::WorldSCIGL( WorldPtr model) : Object(), Observer()
{
  _model = model;
  
  set_visible (true);
  set_size (1,1,1);
  set_position (0,0,0);
  set_fg_color (0.95, 0.95, 0.8, 1.0);  // face up : blue 
  set_br_color (0.0, 0.0, 0.0, 1.0);  // border : black
  set_bg_color (0.6, 0.6, 0.6, 1.0);  // face down : light_grey
  alpha_ = 1.0f;
  fade_in_delay_ = 0;
  fade_out_delay_ = 0;

  std::ostringstream oss;
  oss << "World_" << id_;
  set_name (oss.str());
}
WorldSCIGL::~WorldSCIGL (void)
{
}
// *****************************************************************************  
/** Render the world as a set of squares. */
void WorldSCIGL::render (void)
{
  // Global visibility
  compute_visibility();
  if (not get_visible()) return;

  glPushAttrib (GL_ENABLE_BIT);
  glDisable (GL_TEXTURE_2D);
  glDisable (GL_LIGHTING);
  //glEnable (GL_BLEND);
  glEnable (GL_CULL_FACE);
  glEnable (GL_DEPTH_TEST);
  glDepthMask (GL_TRUE);
  glEnable (GL_LINE_SMOOTH);
  
  // set origine and scaling
  glPushMatrix();
  glScalef (get_size().x, get_size().y, get_size().z);
  glTranslatef (get_position().x, get_position().y, get_position().z);
  
  // Color of face
  glColor4fv (get_fg_color().data);
  glPolygonMode (GL_FRONT, GL_FILL);
  glPolygonOffset (1, 1);
  glEnable (GL_POLYGON_OFFSET_FILL);
  glBegin( GL_QUADS ); {
    for( unsigned int ind_c = 0; ind_c < _model->_ground->_cells.size(); ++ind_c ) {
      CellPtr cell = _model->_ground->_cells[ind_c];
      // Compute normals
      glNormal3f( -sinf(cell->_ang_y), -sinf(cell->_ang_x), 
		  cosf(cell->_ang_y) + cosf(cell->_ang_x) );
      // Compute positions using angles
      glVertex3f( cell->_x - 0.5, cell->_y - 0.5,
		  cell->_z - 0.5*tanf(cell->_ang_y) - 0.5*tanf(cell->_ang_x) );
      glVertex3f( cell->_x + 0.5, cell->_y - 0.5,
		  cell->_z + 0.5*tanf(cell->_ang_y) - 0.5*tanf(cell->_ang_x) );
      glVertex3f( cell->_x + 0.5, cell->_y + 0.5, 
		  cell->_z + 0.5*tanf(cell->_ang_y) + 0.5*tanf(cell->_ang_x) );
      glVertex3f( cell->_x - 0.5, cell->_y + 0.5, 
		  cell->_z - 0.5*tanf(cell->_ang_y) + 0.5*tanf(cell->_ang_x) );
    }
  }
  glEnd();

  // Wire Faces...
  glColor4fv (get_br_color().data);
  glDisable (GL_POLYGON_OFFSET_FILL);
  glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth (0.5);
  glBegin( GL_QUADS ); {
    for( unsigned int ind_c = 0; ind_c < _model->_ground->_cells.size(); ++ind_c ) {
      CellPtr cell = _model->_ground->_cells[ind_c];
      // Compute normals
      glNormal3f( -sinf(cell->_ang_y), -sinf(cell->_ang_x),
		  cosf(cell->_ang_y) + cosf(cell->_ang_x) );
      // Compute positions using angles
      glVertex3f( cell->_x - 0.5, cell->_y - 0.5,
		  cell->_z - 0.5*tanf(cell->_ang_y) - 0.5*tanf(cell->_ang_x) );
      glVertex3f( cell->_x + 0.5, cell->_y - 0.5,
		  cell->_z + 0.5*tanf(cell->_ang_y) - 0.5*tanf(cell->_ang_x) );
      glVertex3f( cell->_x + 0.5, cell->_y + 0.5, 
		  cell->_z + 0.5*tanf(cell->_ang_y) + 0.5*tanf(cell->_ang_x) );
      glVertex3f( cell->_x - 0.5, cell->_y + 0.5, 
		  cell->_z - 0.5*tanf(cell->_ang_y) + 0.5*tanf(cell->_ang_x) );
    }
  }
  glEnd();

  // Draw position of point
  glPointSize( 10.0 );
  if( _model->_player->_player_state == PhyPoint::s_CONTACT ) { // in contact -> green
    glColor4f( 0.0, 1.0, 0.0, 1.0 );
  }
  else {
    glColor4f( 1.0, 0.0, 0.0, 1.0 );   // else -> red
  }
  glEnable (GL_BLEND);
  glEnable (GL_POINT_SMOOTH);
  glBegin( GL_POINTS ); {
    glVertex3f( _model->_player->_x, _model->_player->_y, _model->_player->_z );
  }
  glEnd();
//   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
//   glColor4f( 1.0, 0.0, 0.0, 1.0 );
//   sphere( _model->_player->_x, _model->_player->_y, _model->_player->_z+0.05 , 0.05 );


  // restore
  glPopMatrix();
  glPopAttrib();}
  
// *****************************************************************************  
void WorldSCIGL::update( int signal )
{
}
// *****************************************************************************
