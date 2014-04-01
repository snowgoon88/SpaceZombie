// -*- coding: utf-8 -*-

#include "mesh_model.h"
#include <sstream>
#include <algorithm>    // std::min

//********************************************************************* CREATION
/** Creation */
MeshModel::MeshModel() : Model()
{
  _v_vertex = NULL;
  _v_indices = NULL;
  _v_color_default = NULL;
  _v_color_custom = NULL;
  _e_color = NO_COLOR;
  
  _scdata = NULL;
}
/** Destruction */
MeshModel::~MeshModel()
{
    std::cout << "~MeshModel START" << "\n";
    if (_v_vertex != NULL ) delete _v_vertex;
    if (_v_indices != NULL ) delete _v_indices;
    if (_v_color_default != NULL ) delete _v_color_default;
    std::cout << "~MeshModel END" << "\n";
}
//*********************************************************************** STRING
std::string MeshModel::str_brief()
{
  std::stringstream ss;
  
  ss << "MeshModel: ";
  if( _v_vertex == NULL ) {
    ss << "NO vertex";
  }
  else {
    ss << _v_vertex->size() << " vertex";
  }
  if( _v_indices == NULL ) {
    ss << " NO triangles";
  }
  else {
    ss << " " << _v_indices->size() << " indices => " << _v_indices->size()/3 << " triangles";
  }
  ss << "\n";

  return ss.str();
}
void MeshModel::dump(std::ostream& out, unsigned int nb_shown)
{
  
  out << str_brief();

  out << "Dump from _v_vertex \n";
  if( _v_vertex != NULL ) {
    unsigned max_shown = std::min((unsigned int)_v_vertex->size(), nb_shown);
    for( unsigned int i=0; i < max_shown; ++i) {
      out << DFORMAT(4) << i << " : ";
      out << FFORMAT(6,3) << (*_v_vertex)[i](0) << ", ";
      out << FFORMAT(6,3) << (*_v_vertex)[i](1) << ", ";
      out << FFORMAT(6,3) << (*_v_vertex)[i](2);
      out << "\n";
    }
  }
  
  out << "Dump from _v_indices\n";
  if( _v_indices != NULL ) {
    unsigned max_shown = std::min((unsigned int)_v_indices->size(), nb_shown);
    for( unsigned int i=0; i < max_shown; ++i) {
      out << DFORMAT(4) << i << " : ";
      out << DFORMAT(3) << (*_v_indices)[i] << ", ";
      out << DFORMAT(3) << (*_v_indices)[i+1] << ", ";
      out << DFORMAT(3) << (*_v_indices)[i+2];
      out << "\n";
    }
  }
}
// ********************************************************************** ATTACH
void MeshModel::attach( FileSCData *fileobject ) 
{
  _scdata = fileobject;
  // clean up if not NULL
  if (_v_vertex != NULL ) delete _v_vertex;
  _v_vertex = new std::vector<TVec3>( fileobject->_v_xyz );
  if (_v_indices != NULL ) delete _v_indices;
  _v_indices = new std::vector<unsigned short>( fileobject->_v_indices );
  // Make default color
  if (_v_color_default != NULL ) delete _v_color_default;
  _v_color_default = new std::vector<IColorPtr>;
  IColorPtr col = IColorPtr( new TColorF( 0.8f, 0.8f, 0.8f, 1.0f ) );
  std::cout << col->str_dump() << "\n";
  for( unsigned int i = 0; i < _v_vertex->size(); ++i) {
    _v_color_default->push_back( col );
  }
 
  notify_observers();
}
void MeshModel::custom_color_from_scdata( std::string type_name, unsigned int address ) 
{
  // uint
  if (type_name.compare( "uchar" ) == 0) {
    _scdata->read_v_color<unsigned char>( address );
  }
  else {
    std::cout << "MeshModel::custom_color_from_scdata : unknown type_name=" << type_name << "\n";
  }
  // Copy to custom
  _v_color_custom->clear();
  for( unsigned int i = 0; i < _scdata->_v_color.size(); ++i) {
    _v_color_custom->push_back( _scdata->_v_color[i] );
  }
}
//******************************************************************************
