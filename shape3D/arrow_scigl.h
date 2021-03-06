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

#ifndef __ARROW_H__
#define __ARROW_H__
#include "object.h"
#include "utils.h"

#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class Arrow> ArrowPtr;

/**
 * 3D arrow as a ligne and a head (4 triangles + quad ).
 *
 * + br_color : color of the line
 * + fg_color : color of head and text.
 * 
 * Has a position (x,y,z) and rotation (euler angles _z1,x1,z2)
 * 
 * Two different rendering mode are possible :
 * + arrow label is aligned to arrow
 * + arrow label is displayed face to the viewer (need to pass the
 * correct view_rotation to Arrow::render(float view_rotation[4][4])
 *
 * @author Alain
 * @date 01/2014
 */
class Arrow : public Object {

public:
  /**
   * @name Creation/Destruction
   */
  /** Default constructor */
  Arrow( void );
  Arrow( TVec3 v );
  /** Destructor */
  virtual ~Arrow( void );
  //@}
  
  /**
   *  @name Rendering
   */
  /** Render arrow as line and faces */
  virtual void render (void);
  /** Render arrow as line and face, with text facing viewer */
  virtual void render( float view_rotation[4][4] );
  //@}
  
  /** Set position */
  virtual void set_position( TVec3 p );
  /** Compute euler angles and length from a vector */
  void compute_from_vec( TVec3 v );
  
  /** Set text */
  void set_text( std::string text );
  
  /** 1st euler angle, around Oz */
  float _ang_z1;
  /** 2nd euler angle, around Oy (beware of sign ) */
  float _ang_y2;
  /** length of vector */
  float _length;
  
  /** moment arrow */
  bool _fg_moment;
  
  /** display text ? */
  bool _fg_text;
  /** text to display */
  std::string _text;
};

#endif // __ARROW_H__
