/* -*- coding: utf-8 -*- */

#ifndef __BAR_H_
#define __BAR_H_

#include "utils.h"
#include "model.h"

// Smart pointer
#include <boost/shared_ptr.hpp>

/** 
 * A bar has an origin, a direction vector, @todo a thickness,
 * a starting and ending coordinate.
 */
class Bar : public Model
{
public:
  /** Creation */
  Bar( TVec3 ori=TVec3(0,0,0), TVec3 dir=TVec3(1,0,0),
       float x_start=0, float x_end=1.0f, float thick=0 );
  /** Destruction */
  virtual ~Bar();
  
  /** display string */
  std::string dump_string();

  /** set position */
  void set_position( TVec3 pos );
  /** set direction */
  void set_dir( TVec3 dir );

  /** get point at various coordinate, return false if no point */
  bool get_point_at( float x_coord, TVec3& point );

public: //Variables
  /** Origin point */
  TVec3 _ori;
  /** Dir vector */
  TVec3 _dir;
  /** start and end coordinate along length of bar */
  float _x_start, _x_end;
  /** start and end point */
  TVec3 _pt_start, _pt_end;
};
#endif // __BAR_H_
