// -*- coding: utf-8 -*-

#ifndef __TORSOR_SCIGL_H_
#define __TORSOR_SCIGL_H_
#include "object.h"
#include "arrow_scigl.h"
#include "torsor.h"

#ifdef HAVE_BOOST
    typedef boost::shared_ptr<class TorsorScigl> TorsorSciglPtr;
#else
    typedef class TorsorScigl * TorsorSciglPtr;
#endif

class TorsorScigl : public Object
{
 public:
  /** Default constructor */
  TorsorScigl();
  TorsorScigl( Torsor& t);
  /** Destructor */
  ~TorsorScigl();

  /**
   *  @name Rendering
   */
  /** Render as 2 arrows and central axe */
  virtual void render (void);
  //@}

 public:
  /** Resultant arrow */
  Arrow _arr_res;
  /** Moment arrow */
  Arrow _arr_mom;
};

#endif // __TORSOR_SCIGL_H_
