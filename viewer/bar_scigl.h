/* -*- coding: utf-8 -*- */

#ifndef __BAR_SCIGL_H
#define __BAR_SCIGL_H

#include "observer.h"
#include "object.h"

// Smart pointer
class Bar;
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class Bar> BarPtr;

#include "bar.h"
typedef boost::shared_ptr<class BarScigl> BarSciglPtr;

/**
 * A Bar is represented as a line.
 * fg_color is the color of the bar.
 * @todo thickness
 */
class BarScigl : public Observer, public Object
{
public:
  /** Creation */
  BarScigl();
  /** With model */
  BarScigl( BarPtr model );
  /** Destruction */
  virtual ~BarScigl();
  
  /** display string */
  virtual std::string dump_string();

public: // Observer
  virtual void update( int signal=0 );
public: // Object
  virtual void render();

public: // Variables
  BarPtr _model;
  
};
#endif // __BAR_SCIGL_H
