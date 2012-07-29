/* -*- coding: utf-8 -*- */

#ifndef __TAG_H__
#define __TAG_H__

#include "object.h"
#include "utils.h"

#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<class TagScigl> TagSciglPtr;

/**
 * A labelled tag "floating above" an object.
 * Color depends on its state (background always in bg_color):
 *  - normal : line and text in fg_color
 *  - selected : line in br_color.
 *
 * Linked to a position.
 */
class TagScigl : public Object
{
public:
  /** Creation with a position and floating distance*/
  TagScigl( std::string label, TVec3 *pos, float height = 1.0f );
  /** Destruction */
  virtual ~TagScigl();
  

  /**
   *  @name Rendering
   */
  /** No rendering if view_ratation not given */
  virtual void render (void);
  /** Render arrow as line and rectangle around label text facing viewer */
  virtual void render( float view_rotation[4][4] );

  /** Set position */
  virtual void set_position( TVec3 *pos, float height = 1.0f );
  /** Set label */
  virtual void set_label( std::string label );
  /** Set selected */
  virtual void set_selected( bool selected );

public: // Variables
  /* selected ? */
  bool _fg_selected;
  /* linked object */
  TVec3 *_pos;
  /* height above object */
  float _height;
  /* label */
  std::string _label;
};

#endif // __TAG_H__
