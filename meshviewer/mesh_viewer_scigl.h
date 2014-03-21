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

#ifndef __MESH_VIEWER_SCIGL_H__
#define __MESH_VIEWER_SCIGL_H__
#include "object.h"                  // Scigl
#include "utils.h"                   // TVec3
#include "mesh_model.h"              // MeshModel

#ifdef HAVE_BOOST
    #include <boost/shared_ptr.hpp>
    typedef boost::shared_ptr<class MeshViewer> MeshViewerPtr;
#else
    typedef class MeshViewer * MeshViewerPtr;
#endif


/**
 * A Mesh as a set of triangles, with normals computed automatically.
 *
 * The reference_frame of the Mesh is set using Mesh::set_position()
 * 1. The whole set is translater to that position.
 * 2. It is rotated of _ang_z1 around Oz
 * 3. It is rotated of _ang_y2 around Oy
 *
 * The MeshViewer observes a MeshModel. Variables settings are allowed:
 * + _fg_wireframe : wireframe or solid.
 *
 * @todo : colors or not, normals or not, Lightings
 *
 * @todo CLEAN FOLLOWING DOC FROM TRIANLES_SCIGL
 * If only vertex (and color) are given
 * + Every set of 3 TVec3 define a triangle.
 * + Normals are computed if needed at each point of each triangle.
 * If vertex (and colors) and also a set of indexes (which must be supplied
 * AFTER the vertex):
 * + Every TVec3 of the arrays can be used many time
 * + Every set if 3 indexes (that references T3Vec) defines a triangle
 * + Normals are computed if needed at each point of each triangle.
 *
 * + _fg_light dictate if GL_LIGHTING is enabled or not.
 * + _fg_normal dictates if glNormal(0,0,0) or "true" normales are set
 * with each point.
 * 
 * @todo switch between draw/not draw normals.
 */
class MeshViewer : public Object, public Observer {

public:
    /**
     * @name Creation/Destruction
     */
    /** Default constructor */
    MeshViewer( MeshModelPtr model );
    /** Destructor */
    virtual ~MeshViewer( void );
    //@}

    /**
     *  @name Rendering
     */
    /** Render */
    virtual void render (void);
    //@}

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

    /** The Model to observe */
    MeshModelPtr _model;

    /** Wireframe or Solid */
    bool _fg_wireframe;
    /** With of without Lights */
    bool _fg_light;
    /** With or without Color */
    bool _fg_color;
};

#endif // __MESH_VIEWER_SCIGL_H__
