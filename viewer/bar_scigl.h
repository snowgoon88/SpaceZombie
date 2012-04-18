/* -*- coding: utf-8 -*- */

#ifndef __BAR_SCIGL_H
#define __BAR_SCIGL_H

#include "observer.h"
#include "object.h"

// Smart pointer
class Bar;
#ifdef HAVE_BOOST
    typedef boost::shared_ptr<class Bar> BarPtr;
#else
    typedef class Bar * BarPtr;
#endif
#include "bar.h"

#ifdef HAVE_BOOST
typedef boost::shared_ptr<class BarScigl> BarSciglPtr;
#else
typedef class BarScigl * BarSciglPtr;
#endif

/**
 * A Bar is represented as a line.
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
  virtual void update( int signal );
public: // Object
  virtual void render();

public: // Variables
  BarPtr _model;
  
};
#endif // __BAR_SCIGL_H
