// -*- coding: utf-8 -*-

#ifndef __TORSOR_SCIGL_H_
#define __TORSOR_SCIGL_H_
#include "object.h"
#include "arrow_scigl.h"
#include "torsor.h"
#include "observer.h"

#ifdef HAVE_BOOST
    typedef boost::shared_ptr<class TorsorScigl> TorsorSciglPtr;
#else
    typedef class TorsorScigl * TorsorSciglPtr;
#endif

/**
 * Graphic representation of a torsor.
 * the central axis can be drawn as a stippled line
 */
class TorsorScigl : public Observer, public Object
{
 public:
  /** Default constructor */
  TorsorScigl();
  TorsorScigl( Torsor& t);
  TorsorScigl( TorsorPtr model );
  /** Destructor */
  ~TorsorScigl();

public: // Observer
  virtual void update( int signal=0 );
public: // Object
  /**
   *  @name Rendering
   */
  /** Render as 2 arrows and central axe */
  virtual void render (void);
  //@}

  /** Color */
  void set_color( float r=0, float g=0, float b=0, float a=1 ) ;
  void set_color( Color color );


 public: // Variables
  TorsorPtr _model;
  /** Resultant arrow */
  Arrow _arr_res;
  /** Moment arrow */
  Arrow _arr_mom;
  /** draw Central Axis ? */
  bool _fg_axis;
  /** memorize a point of the central axis and direction */
  TVec3 _pt_axis, _dir_axis;
};

#endif // __TORSOR_SCIGL_H_
