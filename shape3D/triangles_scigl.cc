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

#include "triangles_scigl.h"
#include <iostream>

// ******************************************************************** CREATION
Triangles::Triangles( void ) : Object()
{
  set_visible( true );
  set_position( 0, 0, 0 );
  set_fg_color( 1, 0, 0, 1);
  alpha_ = 1.0f;
  fade_in_delay_ = 0;
  fade_out_delay_ = 0;

  _fg_normal = false;
  _fg_light = false;

  _nb_triangles = 0;
  _vertex = NULL;
  _indices_vertex = NULL;


  orient_from_vec( TVec3( 1, 0, 0) );

  std::ostringstream oss;
  oss << "Triangles_" << id_;
  set_name (oss.str());
}
Triangles::~Triangles( void )
{
}
// ********************************************************************** RENDER
void Triangles::render( void )
{
  compute_visibility();
  if (not get_visible()) return;

  // Check if must create _normals
  if( _normals.size() < _nb_triangles ) {
    _normals.clear();
    for( unsigned int i=0; i < _nb_triangles; i += 3 ) {
      _normals.push_back( TVec3(0,0,0) );
    }
  }
  // Check if must create _arrow_scigl
  if( _arrow_normal.size() != _nb_triangles*3 ) {
    _arrow_normal.clear();
    for( unsigned int i=0; i < _nb_triangles*3; ++i ) {
      _arrow_normal.push_back( ArrowPtr( new Arrow ));
    }
  }

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

  // draw triangles
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
  glColor4fv (get_fg_color().data);
  glBegin (GL_TRIANGLES); {
    if ( _indices_vertex == NULL ) {
      for( unsigned int i=0; i < _vertex->size(); i += 3 ) {
	if( _fg_normal ) {
	  // Compute normal as cross product 10 x 12
	  // _normals[i] << (*_vertex)[i+0](1)*(*_vertex)[i+1](2) -
	  //   (*_vertex)[i+0](2)*(*_vertex)[i+1](1), 
	  //   (*_vertex)[i+0](2)*(*_vertex)[i+1](0) -
	  //   (*_vertex)[i+0](0)*(*_vertex)[i+1](2),
	  //   (*_vertex)[i+0](0)*(*_vertex)[i+1](1) -
	  //   (*_vertex)[i+0](1)*(*_vertex)[i+1](0) ;
	  _normals[i] = ((*_vertex)[i+0] - (*_vertex)[i+1]).cross( ((*_vertex)[i+2] - (*_vertex)[i+1]));
	  _normals[i].normalize();
	  glNormal3f( _normals[i](0), _normals[i](1), _normals[i](2) );
	}
	else {
	  glNormal3f( 0, 0, 0 );
	}
	glVertex3f( (*_vertex)[i+0](0), (*_vertex)[i+0](1), (*_vertex)[i+0](2) ); 
	glVertex3f( (*_vertex)[i+1](0), (*_vertex)[i+1](1), (*_vertex)[i+1](2) ); 
	glVertex3f( (*_vertex)[i+2](0), (*_vertex)[i+2](1), (*_vertex)[i+2](2) ); 
      }
    }
    else { // as list of indices
      for( unsigned int i = 0; i < _indices_vertex->size(); i += 3) {
	unsigned int i0 = (*_indices_vertex)[i];
	unsigned int i1 = (*_indices_vertex)[i+1];
	unsigned int i2 = (*_indices_vertex)[i+2];
	if( _fg_normal ) {
	  _normals[i] = ((*_vertex)[i0] - (*_vertex)[i1]).cross( ((*_vertex)[i2] - (*_vertex)[i1]));
	  _normals[i].normalize();
	  glNormal3f( _normals[i](0), _normals[i](1), _normals[i](2) );
	}
	else {
	  glNormal3f( 0, 0, 0 );
	}
	glVertex3f( (*_vertex)[i0](0), (*_vertex)[i0](1), (*_vertex)[i0](2) ); 
	glVertex3f( (*_vertex)[i1](0), (*_vertex)[i1](1), (*_vertex)[i1](2) ); 
	glVertex3f( (*_vertex)[i2](0), (*_vertex)[i2](1), (*_vertex)[i2](2) );
      }
    }
  } glEnd();
    
  // draw normals
  if( _fg_normal ) {
    if (_indices_vertex == NULL) {
      for( unsigned int i=0; i < _vertex->size(); i += 3 ) {
	_arrow_normal[i+0]->set_position( (*_vertex)[i+0] );
	_arrow_normal[i+0]->compute_from_vec( _normals[i] );
	_arrow_normal[i+0]->render();
	//std::cout << "[" << i << "] at " << line_repr( (*_vertex)[i+0] ) << " n=" << line_repr( _normals[i] ) << "\n";
	_arrow_normal[i+1]->set_position( (*_vertex)[i+1] );
	_arrow_normal[i+1]->compute_from_vec( _normals[i] );
	_arrow_normal[i+1]->render();
	//std::cout << "[" << i+1 << "] at " << line_repr( (*_vertex)[i+1] ) << " n=" << line_repr( _normals[i] ) << "\n";
	_arrow_normal[i+2]->set_position( (*_vertex)[i+2] );
	_arrow_normal[i+2]->compute_from_vec( _normals[i] );
	_arrow_normal[i+2]->render();
	//std::cout << "[" << i+2 << "] at " << line_repr( (*_vertex)[i+2] ) << " n=" << line_repr( _normals[i] ) << "\n";
      }
    }
    else {
      for( unsigned int i=0; i < _indices_vertex->size(); i += 3 ) {
	unsigned int i0 = (*_indices_vertex)[i];
	unsigned int i1 = (*_indices_vertex)[i+1];
	unsigned int i2 = (*_indices_vertex)[i+2];
	_arrow_normal[i+0]->set_position( (*_vertex)[i0] );
	_arrow_normal[i+0]->compute_from_vec( _normals[i] );
	_arrow_normal[i+0]->render();
	//std::cout << "[" << i << "] at " << line_repr( (*_vertex)[i+0] ) << " n=" << line_repr( _normals[i] ) << "\n";
	_arrow_normal[i+1]->set_position( (*_vertex)[i1] );
	_arrow_normal[i+1]->compute_from_vec( _normals[i] );
	_arrow_normal[i+1]->render();
	//std::cout << "[" << i+1 << "] at " << line_repr( (*_vertex)[i+1] ) << " n=" << line_repr( _normals[i] ) << "\n";
	_arrow_normal[i+2]->set_position( (*_vertex)[i2] );
	_arrow_normal[i+2]->compute_from_vec( _normals[i] );
	_arrow_normal[i+2]->render();
	//std::cout << "[" << i+2 << "] at " << line_repr( (*_vertex)[i+2] ) << " n=" << line_repr( _normals[i] ) << "\n";
      }
    }
  }
  
  // restore transformation matrix
  glPopMatrix();

  // restore attributes
  glPopAttrib();

}
// ********************************************************************** ATTACH
void Triangles::attach_vertex( std::vector<TVec3> * v )
{
  _vertex = v;
  _nb_triangles = _vertex->size() / 3;
}
void Triangles::attach_indices( std::vector<unsigned int> * i )
{
  _indices_vertex = i;
  _nb_triangles = _indices_vertex->size() / 3;
}
// ******************************************************************** POSITION
void Triangles::set_position( TVec3 p )
{
  Object::set_position( p(0), p(1), p(2) );
}
void Triangles::set_position( float x, float y, float z )
{
  Object::set_position( x, y, z );
}
void Triangles::orient_from_vec( TVec3 v )
{
  ang_from_vec( v, _ang_z1, _ang_y2 );
}
// *****************************************************************************
