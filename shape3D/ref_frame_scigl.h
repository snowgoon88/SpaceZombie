// -*- coding: utf-8 -*-
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

#ifndef __REF_FRAME_H__
#define __REF_FRAME_H__
#include "object.h"
#include "arrow_scigl.h"

#ifdef HAVE_BOOST
    #include <boost/shared_ptr.hpp>
    typedef boost::shared_ptr<class RefFrame> RefFramePtr;
#else
    typedef class RefFrame * RefFramePtr;
#endif


/**
 * A reference frame depicted by 3 axes (X,Y,Z) and a 1/8 of a wiresphere.
 *
 * Main color given by 'fg', sphere color by 'br'.
 *
 * Has a position (x,y,z) and rotation (euler angles _z1,x1,z2)
 * 
 * Two different rendering mode are possible :
 * + axes names are aligned to axes
 * + axes names are displayed face to the viewer (need to pass the
 * correct view_rotation to RefFrame::render(float view_rotation[4][4])
 *
 * @author Alain
 * @date 12/2013
 */
class RefFrame : public Object {

public:

    /**
     * @name Creation/Destruction
     */
    /**
     * Default constructor
     */
    RefFrame (void);

    /**
     * Destructor
     */
    virtual ~RefFrame (void);
    //@}


    /**
     *  @name Rendering
     */
    /** Render as 3 arrows and wiresphere */
    virtual void render (void);
    /** Render as 3 arrows, wireshpere and X,Y,Z facing the view_rotation */
    virtual void render( float view_rotation[4][4] );
    //@}

    /** Angle around Oz1 */
    float _ang_Oz1;
    /** Angle around Ox1 */
    float _ang_Ox1;
    /** Angle around Oz2 */
    float _ang_Oz2;
    /** Nb of points in a quarter circle */
    int _nb_points;
    /** WireSphere */
    float *_pt_sphere;
    /** Arrow3D */
    Arrow _arr_X, _arr_Y, _arr_Z;
};

#endif
