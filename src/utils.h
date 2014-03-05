// -*- coding: utf-8 -*-
/** @file utils.h
 * Various utilities.
 *
 * + MACRO for formating float with precision
 * + Angle conversion and clipping.
 * + Euler angles from a TVec3 vector
 * + Structure for using a (x,y,z) vector in AntTweakBar
 *
 * @author Alain
 * @date 01/2014
 */

#ifndef __UTILS_H_
#define __UTILS_H_

#include "math.h"
#include <Eigen/Dense>
// AntTweakBar
#include <AntTweakBar.h>

// Eigen library for "dense" matrices and vectors
#include <Eigen/Dense>
#include <vector>

#include <string>
#include <iostream>
#include <sstream>

// Précision dans les formats
#include <iomanip>
/**
 * MACRO precision of 'p' for float.
 * @todo : example of use.
 */
#define SETPREC(P) std::setiosflags(std::ios::fixed) << std::setprecision(P)
/**
 * Vector types:
 * + TVec2 and TVec2Ptr : vector with 2 dimensions.
 * + TVec3 and TVec3Ptr : vector with 2 dimensions.
 */
typedef Eigen::Vector2f TVec2;
typedef Eigen::Vector3f TVec3;
#ifdef HAVE_BOOST
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<TVec3> TVec3Ptr;
typedef boost::shared_ptr<TVec2> TVec2Ptr;
#else
typedef TVec3 * TVec3Ptr;
typedef TVec2 * TVec2Ptr;
#endif

/**
 * Color
 */
typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
} TColorUC;

/**
 * Return a str line representation of a vector.
 */
std::string line_repr( Eigen::VectorXf vector, int precision=2);

/** Angle conversion in [-180, 180] */
float to_deg( float rad );
/** Angle conversion in [-M_PI, M_PI] */
float to_rad( float deg );
/** Angle Clip to [-M_PI,M_PI] */
float clip_rad_pi( float rad);
/** Angle Clip to [0,2*M_PI] */
float clip_rad_2pi( float rad);

/** From a TVec3, get 2 first euler angles : 0x->vxy and vxy->v */
void ang_from_vec( TVec3 v, float& ang_z1, float& ang_y2 );

/** AntTweakBar structure for TVec3 */
// A user defined structure
typedef struct {
  float x; float y; float z;
} SVec3;

/**
 * Struc to be used by AntTweakBar.
 *
 * + x : float, step by 0.1
 * + y : float, step by 0.1
 * + z : float, step by 0.1
 */
extern TwStructMember SVec3Members[];

#endif // __UTILS_H_
