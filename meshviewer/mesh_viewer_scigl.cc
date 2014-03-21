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

#include "mesh_viewer_scigl.h"
#include <iostream>

// ******************************************************************** CREATION
MeshViewer::MeshViewer( MeshModelPtr model ) : Object(), Observer()
{
  _model = model;

  set_visible( true );
  set_position( 0, 0, 0 );
  set_fg_color( 0, 0, 0, 1); // black
  alpha_ = 1.0f;
  fade_in_delay_ = 0;
  fade_out_delay_ = 0;
  
  _fg_wireframe = true;
  _fg_color = false;
  _fg_light = true;
  _fg_normal = false;

  orient_from_vec( TVec3( 1, 0, 0) );

  std::ostringstream oss;
  oss << "MeshViewer_" << id_;
  set_name (oss.str());
}
MeshViewer::~MeshViewer( void )
{
  std::cout << "~MeshViewer for " << get_name() << "\n";
}
// ********************************************************************** RENDER
void MeshViewer::render( void )
{
  compute_visibility();
  if (not get_visible()) return;

  // // Check if must create _normals
  // if( _normals.size() < _nb_triangles ) {
  //   _normals.clear();
  //   for( unsigned int i=0; i < _nb_triangles; i += 3 ) {
  //     _normals.push_back( TVec3(0,0,0) );
  //   }
  // }
  // // Check if must create _arrow_scigl
  // if( _arrow_normal.size() != _nb_triangles*3 ) {
  //   _arrow_normal.clear();
  //   for( unsigned int i=0; i < _nb_triangles*3; ++i ) {
  //     _arrow_normal.push_back( ArrowPtr( new Arrow ));
  //   }
  // }

  // save Light Attributes
  glPushAttrib( GL_LIGHTING_BIT );
  
  // lighting or not
  if( _fg_light ) {
    glEnable( GL_LIGHTING );
  }
  else {
    glDisable( GL_LIGHTING );
  }

  // save transformation matrix, then translate and scale.
  glPushMatrix();
  glTranslatef (get_position().x, get_position().y, get_position().z);
  glRotatef( to_deg(_ang_z1), 0, 0, 1); // rotation around 0z
  glRotatef( to_deg(_ang_y2), 0, 1 ,0); // rotation around 0y

  // draw triangles from the Mesh
  glPolygonMode (GL_FRONT_AND_BACK, (_fg_wireframe ? GL_LINE : GL_FILL));
  // Set default color
  glColor4fv (get_fg_color().data);
  glBegin (GL_TRIANGLES); {
    for( unsigned int i = 0; i < _model->_v_indices->size(); i += 3) {
      unsigned int i0 = (*_model->_v_indices)[i];
      unsigned int i1 = (*_model->_v_indices)[i+1];
      unsigned int i2 = (*_model->_v_indices)[i+2];
      //std::cerr << "Triangle " << i0 << " - " << i1 << " - " << i2  << "\n";
      if (_fg_normal) {
	TVec3 normal = ((*_model->_v_vertex)[i0] - (*_model->_v_vertex)[i1]).cross( ((*_model->_v_vertex)[i2] - (*_model->_v_vertex)[i1]));
	normal.normalize();
	glNormal3f( normal(0), normal(1), normal(2) );
      }
      else {
	glNormal3f( 0, 0, 0 );
      }
      // std::cerr << "Pt0 = " << (*_model->_v_vertex)[i0](0) << "; " << (*_model->_v_vertex)[i0](1) << "; " << (*_model->_v_vertex)[i0](2) << "\n";
      // std::cerr << "Pt1 = " << (*_model->_v_vertex)[i1](0) << "; " << (*_model->_v_vertex)[i1](1) << "; " << (*_model->_v_vertex)[i1](2) << "\n";
      // std::cerr << "Pt2 = " << (*_model->_v_vertex)[i2](0) << "; " << (*_model->_v_vertex)[i2](1) << "; " << (*_model->_v_vertex)[i2](2) << "\n";
      if( _fg_color ) {
	glColor3i( (GLint) (*_model->_v_color)[i0]->r(), (GLint) (*_model->_v_color)[i0]->g(), (GLint) (*_model->_v_color)[i0]->b() );
      }
      glVertex3f( (*_model->_v_vertex)[i0](0), (*_model->_v_vertex)[i0](1), (*_model->_v_vertex)[i0](2) ); 

      if( _fg_color ) {
	glColor3i( (GLint) (*_model->_v_color)[i1]->r(), (GLint) (*_model->_v_color)[i1]->g(), (GLint) (*_model->_v_color)[i1]->b() );
      }

      glVertex3f( (*_model->_v_vertex)[i1](0), (*_model->_v_vertex)[i1](1), (*_model->_v_vertex)[i1](2) ); 

      if( _fg_color ) {
	glColor3i( (GLint) (*_model->_v_color)[i2]->r(), (GLint) (*_model->_v_color)[i2]->g(), (GLint) (*_model->_v_color)[i2]->b() );
      }

      glVertex3f( (*_model->_v_vertex)[i2](0), (*_model->_v_vertex)[i2](1), (*_model->_v_vertex)[i2](2) );
    }
  } glEnd();
  
  // restore transformation matrix
  glPopMatrix();
  
  // restore attributes
  glPopAttrib();

}
// ******************************************************************** POSITION
void MeshViewer::set_position( TVec3 p )
{
  Object::set_position( p(0), p(1), p(2) );
}
void MeshViewer::set_position( float x, float y, float z )
{
  Object::set_position( x, y, z );
}
void MeshViewer::orient_from_vec( TVec3 v )
{
  ang_from_vec( v, _ang_z1, _ang_y2 );
}
// *****************************************************************************
