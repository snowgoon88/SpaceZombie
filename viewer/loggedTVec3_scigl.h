/* -*- coding: utf-8 -*- */

#ifndef __LOGGED_TVEC3_SCIGL_H
#define __LOGGED_TVEC3_SCIGL_H

#include <string>
#include "observer.h" 
#include "object.h"
#include "utils.h"

#include "loggedT.h" 

// Smart pointer
#ifdef HAVE_BOOST
//typedef boost::shared_ptr<class LoggedT<TVec3>> LoggedTVec3Ptr; 
typedef boost::shared_ptr<class LoggedTVec3Scigl> LoggedTVec3SciglPtr;
#else
//typedef class LoggedT<TVec3> * LoggedTVec3Ptr; 
typedef class LoggedTVec3Scigl * LoggedTVec3SciglPtr;
#endif

/**
 * As a lines between TVec3.
 * br_color.
 */
class LoggedTVec3Scigl : public Observer, public Object
{
public:
  /** Create with model */
  //LoggedTVec3Scigl(  LoggedTVec3Ptr model );
  LoggedTVec3Scigl(  LoggedTPtr<TVec3>::Type model );
  /** Destruction */
  virtual ~LoggedTVec3Scigl();
  
  /** display string */
  std::string dump_string();

public: // Observer
  virtual void update( int signal=0 );
public: // Object
  virtual void render();

public: // Variables
  //LoggedTVec3Ptr _model;
  LoggedTPtr<TVec3>::Type _model;
};

#endif // __LOGGED_TVEC3_SCIGL_H
