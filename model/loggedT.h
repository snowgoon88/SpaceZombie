/* -*- coding: utf-8 -*- */

#ifndef __LOGGED_T_H_
#define __LOGGED_T_H_

#include <vector>
#include "model.h"


template<class T> class LoggedT;
// Smart pointer : using as LoggedTPtr<int>::Type;
#ifdef HAVE_BOOST
  template<class T>
  struct LoggedTPtr
  {
    typedef boost::shared_ptr<LoggedT<T>> Type;
  };
#else
  template<class T>
  struct LoggedTPtr
  {
    typedef LoggedT<T> * Type;
  };
#endif

/** 
 * Memorize a time-stamped collection of items.
 */
template<class T>
class LoggedT : public Model
{
public:
  typedef float T_Time;
  
  struct S_Logged {
    T_Time _t;
    T _item;
  };
  typedef struct S_Logged T_Logged;

public:
  /** Creation */
  LoggedT();
  /** Destruction */
  virtual ~LoggedT();
  
  /** display string */
  std::string dump_string();

   /** Clear log */
  void clear();
  /** Add a new element at given time */
  void add_item( T_Time t, T item); 

public: //Model

public: // Variables
  /** What is memorized */
  std::vector <T_Logged> _data;
};

//********************************************************************* CREATION
/** Creation */
template <class T>
LoggedT<T>::LoggedT() : Model()
{
}
/** Destruction */
template <class T>
LoggedT<T>::~LoggedT()
{
}
//************************************************************************ CLEAR
template <class T>
void LoggedT<T>::clear()
{
  _data.clear();
  notify_observers();
}
//************************************************************************** ADD
template <class T>
void LoggedT<T>::add_item( T_Time t, T item)
{
  T_Logged new_data = {t, item};
  _data.push_back( new_data );
  notify_observers();
}
//******************************************************************************

#endif // __LOGGED_T_H_
