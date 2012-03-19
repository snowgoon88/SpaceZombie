// -*- coding: utf-8 -*-

#ifndef __STATE_H__
#define __STATE_H__

#include <string>

class State {
 public:
  State( unsigned int id, std::string name );
  State( State& other_s );
  virtual ~State( void );

  bool operator ==(const State& s) const;

 public:
  std::string _name;
  unsigned int _id;
};
#endif // __STATE_H__
