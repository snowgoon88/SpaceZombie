// -*- coding: utf-8 -*-
/*
 * Alain - Mars 2014
 */
/**
 * Open SC Mesh file and draw all triangles
 * Derived from test_base.cc
 */
#include "utils.h"
#include "object.h" 
#include <GL/glew.h>
#include <GL/glfw.h>

#include <float.h>
//#include "timer.h"

#include <iostream>
// Graphic
#include <cstdlib>
#include "scene.h"
#include "ref_frame_scigl.h"
#include "triangles_scigl.h"

// Graphic
ScenePtr _scene = ScenePtr (new Scene);
TrianglesPtr _triangles = TrianglesPtr( new Triangles );
//std::vector<TVec3> _vec_vertex;

//******************************************************************************
std::vector<TVec3> _v_vertex;
std::vector<unsigned int> _v_indices;
std::vector<TColorUC> _v_color_uc01;
std::vector<TColorUC> _v_color_uc02;
std::vector<TColorUC> _v_color_uc03;
std::vector<unsigned char *> _v_ukn0, _v_ukn1;
//******************************************************************** READ_MESH
unsigned char read_uchar( FILE *file )
{
  unsigned char var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
}
unsigned int read_ushort( FILE *file )
{
  unsigned short var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
}
unsigned int read_uint( FILE *file )
{
  unsigned int var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
} 
float read_float( FILE *file )
{
  float var;
  fread((void*)(&var), sizeof(var), 1, file);
  return var; 
}
//*******************************************************************************
void read_mesh_18h( FILE *file ) 
{
  // Unknown 0x00 -> 0x07
  for( int i = 0; i < 0x08; ++i) {
    read_uchar( file );
  }
  // 0x08 : size vertex, 0x0C : nb vertex 
  unsigned int size_vertex = read_uint( file );
  unsigned int nb_vertex = read_uint( file );
  printf( "%02Xh : %02Xh => %d (size_vertex)\n", 0x08, size_vertex, size_vertex );
  printf( "%02Xh : %02Xh => %d (nb_vertex)\n", 0x0C, nb_vertex, nb_vertex );
  // Unknown -> 0x44
  for( int i = 0x10; i < 0x44; ++i) {
    read_uchar( file );
  }
  // Read 3 floats
  for( unsigned int i = 0; i < nb_vertex; ++i) {
    // x,y,z coordinate as float
    float x = read_float( file );
    float y = read_float( file );
    float z = read_float( file );
    _v_vertex.push_back( TVec3(x,y,z) );
    printf( "%02Xh : xyz = %2.3f; %2.3f; %2.3f\n", 0x44+i*size_vertex, x,y,z);
    // r,g,b,a as unsigned char
    TColorUC col_uc;
    col_uc.r = read_uchar( file );
    col_uc.g = read_uchar( file );
    col_uc.b = read_uchar( file );
    col_uc.a = read_uchar( file );
    printf( "     : %3d %3d %3d %3d \n", col_uc.r, col_uc.g, col_uc.b, col_uc.a);
    _v_color_uc01.push_back( col_uc );
    // u, v coordinate
    float u = read_float( file );
    float v = read_float( file );
    printf( "     : xv = %2.3f; %2.3f\n", u, v);
  }
  // read triangles to the end
  unsigned int adr_file = 0x44 + nb_vertex * size_vertex;
  while( feof( file ) == false ) {
    unsigned short pt0 = read_ushort( file );
    unsigned short pt1 = read_ushort( file );
    unsigned short pt2 = read_ushort( file );
    _v_indices.push_back( pt0 );
    _v_indices.push_back( pt1 );
    _v_indices.push_back( pt2 );
    printf ( "%2Xh : %2d - %2d - %2d\n", adr_file, pt0, pt1, pt2 ); 
    adr_file += 3 * sizeof(unsigned short);
  }
}
//*******************************************************************************
void read_mesh_20h( FILE *file ) 
{
  
  // Unknown 0x00 -> 0x07
  for( int i = 0; i < 0x08; ++i) {
    read_uchar( file );
  }
  // 0x08 : size vertex, 0x0C : nb vertex 
  unsigned int size_vertex = read_uint( file );
  unsigned int nb_vertex = read_uint( file );
  printf( "%02Xh : %02Xh => %d (size_vertex)\n", 0x08, size_vertex, size_vertex );
  printf( "%02Xh : %02Xh => %d (nb_vertex)\n", 0x0C, nb_vertex, nb_vertex );
  // Unknown -> 0x44
  for( int i = 0x10; i < 0x44; ++i) {
    read_uchar( file );
  }
  // Read Vertex
  for( unsigned int i = 0; i < nb_vertex; ++i) {
    // x,y,z coordinate as float
    float x = read_float( file );
    float y = read_float( file );
    float z = read_float( file );
    _v_vertex.push_back( TVec3(x,y,z) );
    //printf( "%02Xh : xyz = %2.3f; %2.3f; %2.3f\n", 0x44+i*size_vertex, x,y,z);
    // 8 unknown char
    unsigned char * ukn0 = new unsigned char[8];
    for( unsigned int j=0; j<8; ++j) {
      ukn0[j] = read_uchar( file );
    }
    _v_ukn0.push_back( ukn0 );
    // r,g,b,a as unsigned char
    TColorUC col_uc;
    col_uc.r = ukn0[0];
    col_uc.g = ukn0[1];
    col_uc.b = ukn0[2];
    col_uc.a = ukn0[3];
    printf( "     : %3d %3d %3d %3d \n", col_uc.r, col_uc.g, col_uc.b, col_uc.a);
    _v_color_uc01.push_back( col_uc );
    TColorUC col_uc2;
    col_uc2.r = ukn0[4];
    col_uc2.g = ukn0[5];
    col_uc2.b = ukn0[6];
    col_uc2.a = ukn0[7];
    _v_color_uc02.push_back( col_uc2 );
    // u, v coordinate
    float u = read_float( file );
    float v = read_float( file );
    //printf( "     : xv = %2.3f; %2.3f\n", u, v);
    // 4 unknown char
    unsigned char * ukn1 = new unsigned char[4];
    for( unsigned int j=0; j<4; ++j) {
      ukn1[j] = read_uchar( file );
    }
    _v_ukn1.push_back( ukn1 );
    TColorUC col_uc3;
    col_uc3.r = ukn1[0];
    col_uc3.g = ukn1[1];
    col_uc3.b = ukn1[2];
    col_uc3.a = ukn1[3];
    _v_color_uc03.push_back( col_uc3 );

  }
  // read triangles to the end
  unsigned int adr_file = 0x44 + nb_vertex * size_vertex;
  while( feof( file ) == false ) {
    unsigned short pt0 = read_ushort( file );
    unsigned short pt1 = read_ushort( file );
    unsigned short pt2 = read_ushort( file );
    _v_indices.push_back( pt0 );
    _v_indices.push_back( pt1 );
    _v_indices.push_back( pt2 );
    //printf ( "%2Xh : %2d - %2d - %2d\n", adr_file, pt0, pt1, pt2 ); 
    adr_file += 3 * sizeof(unsigned short);
  }
}

/**
 * Called after every mouse button pressed.
 * see glfwSetMouseButtonCallback().
 */
void on_mouse_button( int button, int action )
{
  int x, y;
  glfwGetMousePos( &x, &y);
  //std::cout <<"Mouse Button at (" << x <<  ", " << y << ")\n";

  if( !TwEventMouseButtonGLFW( button, action ) )  { // send event to AntTweakBar
    // event has not been handled by AntTweakBar
    // your code here to handle the event
    // ...

    if( action == GLFW_PRESS ) {
      if( button == GLFW_MOUSE_BUTTON_MIDDLE ) {
	// With SHIFT ??
	if( glfwGetKey( GLFW_KEY_LSHIFT ) || glfwGetKey( GLFW_KEY_RSHIFT)) {
	  _scene->mouse_action_start ("move-resize",x,y);
	}
	else {
	  _scene->mouse_action_start ("rotate",x,y);
	}
      }
      else if( button == GLFW_MOUSE_BUTTON_RIGHT ) {
	_scene->mouse_action_start( "zoom", x, y);
      }
    }
    else if( action == GLFW_RELEASE ) {
      _scene->mouse_action_end( x, y);
    }
  }
}
/**
 * Called when the mouse moves.
 * see glfwSetMousePosCallback().
 */
void on_mouse_move (int x, int y)
{

  if( !TwEventMousePosGLFW( x, y ) )  { // send event to AntTweakBar
    // event has not been handled by AntTweakBar
    // your code here to handle the event
    // ...
    
    _scene->mouse_action (x,y);
    // TODO No equivalence for "glutPostRedisplay()"; ==> needed ??
  }
}
/**
 * Called when a key is pressed.
 * see glfwSetKeyCallback().
 */
void on_key_pressed( int key, int action)
{
    if( !TwEventKeyGLFW( key, action ) )  { // send event to AntTweakBar
    // event has not been handled by AntTweakBar
    // your code here to handle the event
    // ...

      // o or O : display orientation of scene
      if( ((key == 111) || (key == 79))  && (action == GLFW_PRESS)) {
	Orientation orien = _scene->get_orientation();
	std::cout << "Orient = (" << orien.x << ", " << orien.y << ")\n";
      }
      // p or P : plan 0xy
      else if( ((key == 112) || (key == 80))  && (action == GLFW_PRESS)) {
	_scene->set_orientation( 0, 0);
      }
      
      // else {
      //     std::cout << "key=" << key << " act=" << action << "(" << GLFW_KEY_TAB << ", " << GLFW_PRESS << ")" << std::endl;
      //   }
    }
}
/**
 * Display the Scene, and thus every object in it.
 */
void display (void) {
    glClearColor (1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _scene->render ();

    // Swap buffers
    glfwSwapBuffers();
}

int main (int argc, char **argv)
{
  // Some graphic parameters
  int width, height;

  // init triangles
  _v_vertex.clear();
  _v_indices.clear();

  // FILE *fp = fopen( "data/misc/cube1m.mdl-msh000", "r");
  // read_mesh_18h( fp );
  FILE *fp = fopen( "data/ship_race2_s_t4/race2_s_t4.mdl-msh000", "r");
  read_mesh_20h( fp );
  // for( unsigned int i=0; i < _v_vertex.size(); ++i ) {
  //   std::cout << "v[" << i << "]= " << _v_vertex[i] << "\n";
  // }
  printf( "Read %d vertex, %d triangles\n", _v_vertex.size(), _v_indices.size()/3 );

  // Initialise GLFW
  if( !glfwInit() ) {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    exit( EXIT_FAILURE );
  }
  
  // TODO Check that same parameters are used than : glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  // Open a window and create its OpenGL context
  if( !glfwOpenWindow( 1000, 800, 0,0,0,0, 0,0, GLFW_WINDOW ) ) {
    fprintf( stderr, "Failed to open GLFW window\n" );
    
    glfwTerminate();
    exit( EXIT_FAILURE );
  }
  glfwSetWindowTitle( "Test GLFW+SCIGL" );
  
  glfwSetMouseButtonCallback( on_mouse_button );
  glfwSetMousePosCallback( on_mouse_move );
  glfwSetKeyCallback( on_key_pressed );
  glfwSetCharCallback( (GLFWcharfun)TwEventCharGLFW );
  glfwSetMouseWheelCallback((GLFWmousewheelfun)TwEventMouseWheelGLFW);

  std::cout << "Init GLEW\n";
  if( !glewInit() ) {
    fprintf( stderr, "Failed to initialize GLEW\n" );
  }
  if (glewIsSupported("GL_EXT_framebuffer_object"))
    std::cout<<"Old EXT FBO available"<<std::endl;
  else
    std::cout<<"Old EXT FBO NOT available"<<std::endl;
  if (glewIsSupported("GL_ARB_framebuffer_object"))
    std::cout<<"Newer ARB FBO available"<<std::endl;
  else
    std::cout<<"Newer ARB FBO NOT available"<<std::endl;

  // Background color for scene
  _scene->set_bg_color (1,1,1,1);

  // Some Ref_Frame
  RefFramePtr _ref = RefFramePtr( new RefFrame());
  _ref->set_position( 0, 0, 0.0 );
  _ref->set_size( 0.5, 0.5, 0.5 );
  _ref->_ang_Oz1 =  0.0;
  _ref->_ang_Ox1 =  0.0;
  _ref->_ang_Oz2 =  0.0;
  _scene->add( _ref );

  // Objects of the scene
  _triangles->attach_vertex( &(_v_vertex) );
  _triangles->attach_indices( &(_v_indices) );
  _triangles->attach_color( &(_v_color_uc01) );
  //_triangles->attach_color( &(_v_color_uc02) );
  //_triangles->attach_color( &(_v_color_uc03) );
  _scene->add( _triangles );

  _scene->set_zoom(0.5);
  _scene->set_orientation( 70.0, 80.0 );

  _scene->setup();
  _scene->update();
  sleep(2);

  // Main loop of GLFW
  do {
    // Get window size (may be different than the requested size)
    glfwGetWindowSize( &width, &height );
    // Special case: avoid division by zero below
    height = height > 0 ? height : 1;
    
    glViewport( 0, 0, width, height );

    display();
    
  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
	 glfwGetWindowParam( GLFW_OPENED ) );


  // Terminate GLFW
  glfwTerminate();

  return 0;
}
