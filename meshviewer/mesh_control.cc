// -*- coding: utf-8 -*-

#include "mesh_control.h"
#include <iostream>
#include <sstream>
#include<boost/tokenizer.hpp>  // tok
#include <stdlib.h>            // strtol

//********************************************************************* CREATION
/** Creation */
MeshControl::MeshControl( MeshModelPtr model, MeshViewerPtr viewer )
{
  _model = model;
  _viewer = viewer;

  _color_custom_str = "uchar 0x0C";
  _mem_start = 0;
  _mem_nb = 12;
}
/** Destruction */
MeshControl::~MeshControl()
{
}
//*********************************************************************** STRING
std::string MeshControl::str_dump()
{
  std::stringstream ss;
  
  ss << "MeshControl::dump_string()" << "\n";
  
  return ss.str();
}
//******************************************************************************
void MeshControl::build_bar()
{ 
  // Create a tweak bar
  meshBar = TwNewBar( "Mesh" );
  TwDefine(" Mesh label='Mesh TweakBar' position='10 60' help='Use this bar to alter the Mesh and its rendering' ");
  
  // Add a variable bool to control fg_wireframe in viewer.
  TwAddVarRW( meshBar, "WireFrame", TW_TYPE_BOOLCPP, &(_viewer->_fg_wireframe) ,
	      " label='(W)ire/Solid' help='Switch between WireFrame and Solid view' key=w");
 
  // Add a bool to switch between NoColor and DefaultColor in model.
  // TwAddVarCB( meshBar, "DefColor", TW_TYPE_BOOLCPP, set_fg_color_cbk, get_fg_color_cbk, this /*clientData*/,
  // 	      " label='(D)efColor' help='Switch between No or Default color' key=d"); 

  // Add an enum variable for color control
  TwEnumVal enumColor[] = {
    { MeshModel::NO_COLOR, "NO color" },
    { MeshModel::DEFAULT_COLOR, "DEFAULT color" },
    { MeshModel::CUSTOM_COLOR, "CUSTOM color" }
  };
  TwType EColorType = TwDefineEnum("ColorMode", enumColor, 3);  // create a new TwType associated to the enum defined by the enumColor array
  TwAddVarRW( meshBar, "FgColor", EColorType, &(_model->_e_color),
  	      " label='(C)olor' group=Color help='Switch Color Mode' key=c");
  // Add a STDSTRING var to control where custom_color is read
  TwAddVarCB( meshBar, "custColStr", TW_TYPE_STDSTRING,
	      set_custom_color_str_cbk, get_custom_color_str_cbk, this,
	      " label='->Custom' group=Color help='Define custom color using : <type> <address> string'");

  // Add a variable bool to control fg_normal in viewer.
  TwAddVarRW( meshBar, "Normals", TW_TYPE_BOOLCPP, &(_viewer->_fg_normal) ,
	      " label='(N)ormals' help='With or without Normals' key=n");

  // Add a variable bool to control fg_light in viewer.
  TwAddVarRW( meshBar, "Light", TW_TYPE_BOOLCPP, &(_viewer->_fg_light) ,
	      " label='(L)ight' help='With or without light' key=l");

  // Add a button to dump mesh
  TwAddButton( meshBar, "Dump", act_str_dump, this,
	       " label='(D)ump' help='Dump Mesh' key=d");

  // Add 2 variables to control dump extends
  TwAddVarRW( meshBar, "MemS", TW_TYPE_UINT32, &(_mem_start),
	      " label='Mem Start' group=Memory help='First memory line to be dumped'");
  TwAddVarRW( meshBar, "MemN", TW_TYPE_UINT32, &(_mem_nb),
	      " label='Mem Nb' group=Memory help='Nb of memory lines to be dumped'");
  TwAddButton( meshBar, "MemDump", act_mem_dump, this,
	       " label='(M)em Dump' group=memory help='Dump Memory' key=m");

}
//******************************************************************************
void MeshControl::decode_custom_str( void ) 
{
  boost::tokenizer<> tok( _color_custom_str );
  // for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
  //   std::cout << *beg << "\n";
  // }

  boost::tokenizer<>::iterator beg=tok.begin();
  if (beg == tok.end()) {
    std::cerr << "custom_color is void !!!" << "\n";
    return;
  }
  // First should be type
  std::string type = *beg;

  // Second should be address
  ++beg;
  if (beg == tok.end()) {
    std::cerr << "custom_color has no address !!!" << "\n";
    return;
  }
  std::string address = *beg;

  char *endptr;
  const char *str = address.c_str();
  errno = 0;    /* To distinguish success/failure after call */
  long val = strtol(str, &endptr, 0);

  /* Check for various possible errors */
  if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
      || (errno != 0 && val == 0)) {
    std::cerr << "strtol error : " << strerror(errno) << std::endl;
    return;
  }

  if (endptr == str) {
    std::cerr << "No digits were found" << std::endl;
    return;
  }
  int add_custom = (int) val;

  /* If we got here, strtol() successfully parsed a number */
  std::cout << "strtol = " << val  << "\n";
  std::cout << " asint = " << add_custom  << "\n";
  
  _model->custom_color_from_scdata( type, (unsigned int) val );

}
// ***************************************************************************
//******************************************************************************
void TW_CALL get_fg_color_cbk( void *value, void *clientData ) 
{
  //std::cout << "TWCALL get_fg_color_cbk" << "\n";

  MeshControl *mc = static_cast<MeshControl *>(clientData); // stored in clientData
  *(bool *)value = mc->_viewer->_fg_color;
}
void TW_CALL set_fg_color_cbk( const void *value, void *clientData )
{
  std::cout << "MeshControl::set_fg_color_cbk = " << *(bool *)value << "\n";
  MeshControl *mc = static_cast<MeshControl *>(clientData); // stored in clientData

  mc->_viewer->_fg_color = *(const bool *)value;
}
//******************************************************************************
void TW_CALL set_custom_color_str_cbk(const void *value, void * clientData )
{
  MeshControl *mc = static_cast<MeshControl *>(clientData); // stored in clientData
  // Set: copy the value of _color_custom_str from AntTweakBar
  const std::string *srcPtr = static_cast<const std::string *>(value);
  mc->_color_custom_str = *srcPtr;
  std::cout << "set_custom_color_str_cbk : " << mc->_color_custom_str << "\n";
  mc->decode_custom_str();
}
void TW_CALL get_custom_color_str_cbk(void *value, void *clientData)
{
  MeshControl *mc = static_cast<MeshControl *>(clientData); // stored in clientData
  // Get: copy the value of s to AntTweakBar
  std::string *destPtr = static_cast<std::string *>(value);
  TwCopyStdStringToLibrary(*destPtr, mc->_color_custom_str); // the use of TwCopyStdStringToLibrary is required here
}
// ***************************************************************************
//******************************************************************************
void TW_CALL act_str_dump( void *clientData ) 
{
  MeshControl *mc = static_cast<MeshControl *>(clientData); // stored in clientData
  mc->_model->dump( std::cout, mc->_mem_nb, mc->_mem_start);
}
// ***************************************************************************
//******************************************************************************
void TW_CALL act_mem_dump( void *clientData ) 
{
  MeshControl *mc = static_cast<MeshControl *>(clientData); // stored in clientData
  FileSCData *sc = mc->_model->_scdata;
  unsigned min_shown = std::min((unsigned int)sc->_raw_vertex.size()-1, mc->_mem_start);
  unsigned max_shown = std::min((unsigned int)sc->_raw_vertex.size(), mc->_mem_start+mc->_mem_nb);
  for( unsigned int i = min_shown; i < max_shown; ++i) {
    std::cout << sc->str_mem(i) << "\n";
  }
}
// ***************************************************************************
