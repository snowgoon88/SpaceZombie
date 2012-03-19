// -*- coding: utf-8 -*-
/*
 * Alain - Jan 2012
 */
/**
 * Drawing a simple world
 */
#include "object.h" 
//#if defined(__APPLE__)
//    #include <Glutg/glut.h>
//#else
//    #include <GL/glut.h>
//#endif
#include <GL/glew.h>
#include <GL/glfw.h>

// DBL_MAX and DBL_MIN
#include <float.h>   
#include "timer.h"

#include <iostream>
// Graphic
#include <cstdlib>
#include "scene.h"
#include "ref_frame_scigl.h"
#include "world.h"
#include "world_scigl.h"
#include "textbox.h" 
// AntTweakBar
#include <AntTweakBar.h>

// Graphic
ScenePtr _scene = ScenePtr (new Scene);
WorldSCIGLPtr _world_scigl;
TextBoxPtr _textbox;
TwBar *_bar;         // Pointer to a tweak bar

// Global
WorldPtr _world;

// FPS
Timer _timer_fps;
double _time_frame_t1;
//double _time_frame_min = 1000000000.0;
double _time_frame_min = DBL_MAX;
double _time_frame_max = DBL_MIN;
double _time_frame_avg = 10.0;
double _time_frame_fps1s, _time_frame_fps5s;
double _fps_1s, _fps_5s;
int _frame_nb_1s = 0;
int _frame_nb_5s = 0;

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
      if( button == GLFW_MOUSE_BUTTON_LEFT ) {
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
 * Udate textbox string
 */
void update_textbox()
{
  std::stringstream ss;
  ss << _fps_5s << " : " << _fps_1s << " ";
  ss << "Disp. " << _time_frame_min << " / " << _time_frame_avg << " / " << _time_frame_max << " ";
  _textbox->set_buffer( ss.str() );
}
/**
 * Display the Scene, and thus every object in it.
 */
void display (void) {
    glClearColor (1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _scene->render ();
    _textbox->render();

    // Draw tweak bars
    TwDraw();

    // Swap buffers
    glfwSwapBuffers();
}

int main (int argc, char **argv)
{
  // Some graphic parameters
  int width, height;

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
  glfwSetWindowTitle( "World" );
  
  //glutReshapeFunc (reshape);
  //glutDisplayFunc (display);
  glfwSetMouseButtonCallback( on_mouse_button );
  glfwSetMousePosCallback( on_mouse_move );
  glfwSetKeyCallback( on_key_pressed );
  glfwSetCharCallback( (GLFWcharfun)TwEventCharGLFW );
  glfwSetMouseWheelCallback((GLFWmousewheelfun)TwEventMouseWheelGLFW);
  //glutReshapeWindow (400,400);

  // Initialize AntTweakBar
  TwInit(TW_OPENGL, NULL);
  // Create a tweak bar
  _bar = TwNewBar("World");
  //TwDefine( " GLOBAL help='AntTweak to alter rotation angle.' "); // Msg to the help bar.
  // Add '_angX' to bar : modifiable (RW), FLOAT, [0,360]
  //TwAddVarRW( _bar, "angX", TW_TYPE_FLOAT, &_angX, 
  //	      " label='AngX' min=0 max=360 step=1.0 keyIncr=x KeyDecr=X help='Rotation angle around Oz' ");
  // Add '_angZ' to bar : modifiable (RW), FLOAT, [0,360]
  //TwAddVarRW( _bar, "angZ", TW_TYPE_FLOAT, &_angZ, 
  //	      " label='AngZ' min=0 max=360 step=1.0 keyIncr=z KeyDecr=Z help='Rotation angle around Oy' ");
  

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

  // Add a system coordinate
  Position pos_rep( -0.5, -0.5, -0.5, 0);
  Range rg_x( -5, 5, 4, 4*5);
  Range rg_y( -5, 5, 4, 4*5);
  Range rg_z( -5, 5, 4, 4*5);

  // Then a text box with parameters
  _textbox = TextBoxPtr (new TextBox);
  _textbox->set_position( 0, 0, 1); // z=1 : front
  _textbox->set_fg_color (0,0,0,1);
  _textbox->set_bg_color (.9,.9,.9,.8);
  _textbox->set_fontsize (0);
  _textbox->set_autosize( false );
  _textbox->set_size( 1.0, 20, 1 );
  update_textbox();


  // World
  _world = WorldPtr( new World );
  _world->add_new_room( 0.0, 0.0, 0.0, 1, 4);
  _world->add_new_room( 2.0, 0.0, 0.0, 1, 2);
  _world->add_new_room( 3.0, 2.0, 1.0, 1, 2);
  std::vector< CellPtr > start, end;
  start.push_back( _world->_ground->_cells[0] );
  end.push_back( _world->_ground->_cells[4] );
  _world->connect_cells( start, end );  
  start.clear();
  start.push_back( _world->_ground->_cells[2] );
  start.push_back( _world->_ground->_cells[3] );
  end.clear();
  end.push_back( _world->_ground->_cells[6] );
  end.push_back( _world->_ground->_cells[7] );
  _world->connect_cells( start, end );  


  // Observer
  _world_scigl = WorldSCIGLPtr( new WorldSCIGL( _world ));
  _world->attach_observer( _world_scigl );
  _scene->add( _world_scigl );

  // Some Ref_Frame
  RefFramePtr _ref = RefFramePtr( new RefFrame());
  _ref->set_position( 0, 0, 0.0 );
  _ref->set_size( 0.5, 0.5, 0.5 );
  _ref->_ang_Oz1 =  0.0;
  _ref->_ang_Ox1 =  0.0;
  _ref->_ang_Oz2 =  0.0;
  _scene->add( _ref );
  
//   coord = BasisCubePtr (new BasisCube());
//   coord->set_range_coord_x( rg_x );
//   coord->set_range_coord_y( rg_y );
//   coord->set_range_coord_z( rg_z );
//   coord->set_title_coord_x("X");
//   coord->set_title_coord_y("Y");
//   coord->set_title_coord_z("Z");
//   coord->set_position( pos_rep );
//   _scene->add ( coord );


  _scene->set_zoom(0.5);
  _scene->set_orientation( 70.0, 80.0 );

  _scene->setup();
  _scene->update();

  // Init FPS
    _timer_fps.start();
    _time_frame_t1 = _timer_fps.getElapsedTimeInMilliSec();
    _time_frame_fps1s = _time_frame_t1;
    _time_frame_fps5s = _time_frame_t1;
  // Main loop of GLFW
  do {
    // Get window size (may be different than the requested size)
    glfwGetWindowSize( &width, &height );
    // Special case: avoid division by zero below
    height = height > 0 ? height : 1;
    
    glViewport( 0, 0, width, height );
    TwWindowSize(width, height);
    

    // display
    display();
    // update FPS
    double delta_time_frame = _timer_fps.getElapsedTimeInMilliSec() - _time_frame_t1;
    if( delta_time_frame < _time_frame_min ) _time_frame_min = delta_time_frame;
    if( delta_time_frame > _time_frame_max ) _time_frame_max = delta_time_frame;
    _time_frame_avg = 0.9 * _time_frame_avg + 0.1 * delta_time_frame;
    _time_frame_t1 = _timer_fps.getElapsedTimeInMilliSec();
    
    _frame_nb_1s ++;
    _frame_nb_5s ++;
    if( _timer_fps.getElapsedTime() - _time_frame_fps1s > 1 ) {
      _fps_1s = _frame_nb_1s;
      _frame_nb_1s = 0;
      _time_frame_fps1s = _timer_fps.getElapsedTime();
    }
    if( _timer_fps.getElapsedTime() - _time_frame_fps5s > 5 ) {
      _fps_5s = _frame_nb_5s / 5;
      _frame_nb_5s = 0;
      _time_frame_fps5s = _timer_fps.getElapsedTime();
    }
    update_textbox();
    

  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
	 glfwGetWindowParam( GLFW_OPENED ) );


  // Terminate AntTweakBar and GLFW
  TwTerminate();
  glfwTerminate();

  return 0;
}
