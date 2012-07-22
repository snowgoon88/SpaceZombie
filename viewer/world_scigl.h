// -*- coding: utf-8 -*-

#ifndef __WORLD_SCIGL_H__
#define __WORLD_SCIGL_H__

// MVC include
#include "observer.h"
#include "world.h"
// SciGL include
#include "object.h"


// Smart pointer
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class WorldSCIGL> WorldSCIGLPtr;

/**
 * A simple 3D vizualisation of the world.
 */
class WorldSCIGL : public Object, public Observer
{
  
 public:
  //WorldSCIGL();
  WorldSCIGL( WorldPtr model );
  virtual ~WorldSCIGL ();
  
 public: //MVC
  /** update called from Model */
  virtual void update( int signal );
  
 public: // SCIGL  
  /** Render the world as a set of squares. */
  virtual void render ();

  WorldPtr _model;
};
#endif // __WORLD_SCIGL_H__
