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

#ifndef __TRIANGLES_H__
#define __TRIANGLES_H__
#include "object.h"
#include "arrow_scigl.h"
#include "utils.h"
#include <vector>

#ifdef HAVE_BOOST
    #include <boost/shared_ptr.hpp>
    typedef boost::shared_ptr<class Triangles> TrianglesPtr;
#else
    typedef class Triangles * TrianglesPtr;
#endif


/**
 * A set of triangles, with normal computed automatically.
 */
class Triangles : public Object {

public:
    /**
     * @name Creation/Destruction
     */
    /** Default constructor */
    Triangles( void );
    /** Destructor */
    virtual ~Triangles( void );
    //@}

    /**
     *  @name Rendering
     */
    /** Render arrow as line and faces */
    virtual void render (void);
    //@}

    /** Attach a set of points */
    virtual void attach_vertex( std::vector<TVec3> * v_vertex );

    /** Position from TVec3 */
    void set_position( TVec3 p );
    /** Classical Object::set_position */
    void set_position( float x, float y, float z );
    /** Compute euler angles and length from a vector */
    void orient_from_vec( TVec3 v );

    /** 1st euler angle, around Oz */
    float _ang_z1;
    /** 2nd euler angle, around Oy (beware of sign ) */
    float _ang_y2;

    /** A set of vertex */
    std::vector<TVec3> * _vertex;
    /** A set of arrow to depict vectors */
    std::vector<ArrowPtr> _arrow_normal;
    /** A set of normal vectors */
    std::vector<TVec3> _normals;
    /** With or without normals */
    bool _fg_normal;
    /** With or without lighting */
    bool _fg_light;
};

#endif // __TRIANGLES_H__
