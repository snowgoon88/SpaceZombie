// -*- coding: utf-8 -*-
/** @file test_arrow_scigl.cc
 * Drawing a simple world and arrows. The label of the arrows face the viewer
 * as the Scene object is rendered using "with_orientation".
 *
 * + a textbox above
 * + the_scene : made of a RefFrame and Arrow
 * + some menu with AntTweakBar
 *
 * Commands are
 * + o/O : print the orientation of the _scene
 * + p/P : set the orientation to (0,0)
 * + M_MOUSE : rotate
 * + Shift+M_MOUSE : translate
 * + R_MOUSE or Wheel : zoom
 * + ESC : exit
 *
 * Derived from test_physics_scigl.cc
 * @author Alain
 * @date 01/2014
 */

#include "utils.h"
#include "object.h" 
//#if defined(__APPLE__)
//    #include <Glutg/glut.h>
//#else
//    #include <GL/glut.h>
//#endif
#include <GL/glew.h>
#include <GL/glfw.h>

#include <float.h>
#include "timer.h"

#include <iostream>
#include <iomanip> // setw, setprecision
// Graphic
#include <cstdlib>
#include "scene.h"
#include "ref_frame_scigl.h"
#include "arrow_scigl.h"
#include "textbox.h" 
// AntTweakBar
#include <AntTweakBar.h>

// Graphic
ScenePtr _scene = ScenePtr (new Scene);
TextBoxPtr _textbox;
TwBar *_bar;         // Pointer to a tweak bar
SVec3 _pos_arrow = {0.0, 0.0, 0.0};
SVec3 _vec_arrow = {1.0, 1.0, 1.0};
ArrowPtr _arrow = ArrowPtr( new Arrow );
ArrowPtr _arrow_p = ArrowPtr( new Arrow );
ArrowPtr _arrow_x = ArrowPtr( new Arrow );
ArrowPtr _arrow_xy = ArrowPtr( new Arrow );
ArrowPtr _arrow_xyz = ArrowPtr( new Arrow );

// Mouse Wheel
int _old_pos = 100;

// FPS
Timer _timer_fps;
//double _time_frame_t1;
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

  if( !TwEventMouseButtonGLFW( button, action ) )  { // send event to AntTweakBarg
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
 * Called when the mousewheel is used.
 */
void on_mousewheel( int pos )
{
  float zoom = _scene->get_zoom() * (1.0f + (float) (pos - _old_pos)/10.0f);
  _scene->set_zoom(zoom);
  _old_pos = pos;
}
/**
 * Udate textbox string
 */
void update_textbox()
{
  std::stringstream ss;
  ss << _fps_5s << " : " << _fps_1s << " ";
  ss << "Disp. " << _time_frame_min << " / " << _time_frame_avg << " / " << _time_frame_max << " ";
  ss << "\n";
  _textbox->set_buffer( ss.str() );
}
/**
 * Display the Scene, and thus every object in it.
 *
 * Scene object is rendered using 'with_orientation' so as to allow "text labels" to
 * face the viewer.
 */
void display (void) {
    glClearColor (1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _scene->render_with_view_orientation();
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
  glfwSetWindowTitle( "test_arrow_scigl" );
  
  //glutReshapeFunc (reshape);
  //glutDisplayFunc (display);
  glfwSetMouseButtonCallback( on_mouse_button );
  glfwSetMousePosCallback( on_mouse_move );
  glfwSetKeyCallback( on_key_pressed );
  glfwSetCharCallback( (GLFWcharfun)TwEventCharGLFW );
  //glfwSetMouseWheelCallback((GLFWmousewheelfun)TwEventMouseWheelGLFW);
  glfwSetMouseWheel( _old_pos );
  glfwSetMouseWheelCallback( on_mousewheel );
  //glutReshapeWindow (400,400);

  // Initialize AntTweakBar
  TwInit(TW_OPENGL, NULL);
  // Create a tweak bar
  _bar = TwNewBar("_scene");
  TwType tw_SVec3 = TwDefineStruct("Vec3", SVec3Members, 3, sizeof(SVec3), NULL, NULL);
  TwAddVarRW( _bar, "_fg_moment", TW_TYPE_BOOLCPP, &(_arrow->_fg_moment), " Label='Moment' ");
  TwAddVarRW( _bar, "_vec_arrow", tw_SVec3, &_vec_arrow, " Group='Arrow' Label='Vector' ");
  TwAddVarRW( _bar, "_pos_arrow", tw_SVec3, &_pos_arrow, " Group='Arrow' Label='Position' ");

  //TwDefine( " _world iconified=true position='10 50'");
  //TwDefine( " GLOBAL help='AntTweak to alter rotation angle.' "); // Msg to the help bar.
  // TwAddVarRW( _bar, "fg_physic", TW_TYPE_BOOLCPP, &(_fg_physics),
  // 	      " label='fg_physics' keyIncr=g keyDecr=G help='FLAG physics engine' ");
  // TwAddVarRW( _bar, "fg_step_physics", TW_TYPE_BOOLCPP, &(_fg_step_physics),
  // 	      " label='fg_step' keyIncr=f keyDecr=F help='FLAG STEP physics engine' ");
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

  // Some Ref_Frame
  RefFramePtr _ref = RefFramePtr( new RefFrame());
  _ref->set_position( 0, 0, 0.0 );
  _ref->set_size( 0.5, 0.5, 0.5 );
  _ref->_ang_Oz1 =  0.0;
  _ref->_ang_Ox1 =  0.0;
  _ref->_ang_Oz2 =  0.0;
  _scene->add( _ref );

  // Some Arrow
  _arrow->set_br_color( 0, 0, 1, 1 );
  _arrow->set_fg_color( 0, 0, 1, 1 );
  _arrow->_fg_text = true;
  _arrow_p->set_br_color( 0.6, 0.6, 0.6, 1 );
  _arrow_p->set_fg_color( 0.6, 0.6, 0.6, 1 );
  _arrow_x->set_br_color( 0, 0, 0, 1 );
  _arrow_x->set_fg_color( 0, 0, 0, 1 );
  _arrow_xy->set_br_color( 0, 0, 0, 1 );
  _arrow_xy->set_fg_color( 0, 0, 0, 1 );
  _arrow_xyz->set_br_color( 0, 0, 0, 1 );
  _arrow_xyz->set_fg_color( 0, 0, 0, 1 );
  
  _scene->add( _arrow );
  _scene->add( _arrow_p );
  _scene->add( _arrow_x );
  _scene->add( _arrow_xy );
  _scene->add( _arrow_xyz );

  _scene->set_zoom(0.5);
  _scene->set_orientation( 70.0, 80.0 );

  // Then a text box with parameters
  _textbox = TextBoxPtr (new TextBox);
  _textbox->set_position( 0, 0, 1); // z=1 : front
  _textbox->set_fg_color (0,0,0,1);
  _textbox->set_bg_color (.9,.9,.9,.8);
  _textbox->set_fontsize (0);
  _textbox->set_autosize( false );
  _textbox->set_size( 1.0, 50, 1 );
  update_textbox();

  _scene->setup();
  _scene->update();
  sleep(1);

  // Init FPS
  _timer_fps.start();
  double time = _timer_fps.getElapsedTimeInMilliSec();
  _time_frame_fps1s = time;
  _time_frame_fps5s = time;

  // Main loop of GLFW
  do {
    // Get window size (may be different than the requested size)
    glfwGetWindowSize( &width, &height );
    // Special case: avoid division by zero below
    height = height > 0 ? height : 1;
    
    glViewport( 0, 0, width, height );
    TwWindowSize(width, height);
    
    // display
    double time_frame_before = _timer_fps.getElapsedTimeInMilliSec();
    TVec3 arrow_vec( _vec_arrow.x, _vec_arrow.y, _vec_arrow.z);
    TVec3 arrow_pos( _pos_arrow.x, _pos_arrow.y, _pos_arrow.z);
    _arrow->compute_from_vec( arrow_vec );
    std::stringstream sstr;
    sstr << std::setiosflags(std::ios::fixed) << std::setprecision(2) << arrow_vec.norm();
    _arrow->set_text( sstr.str() );
    //std::cout << "ang_z1=" << to_deg( _arrow->_ang_z1 ) << " (" << _arrow->_ang_z1 << ")\n";
    _arrow->set_position( arrow_pos );
    _arrow_p->compute_from_vec( arrow_pos );
    TVec3 ex(1,0,0); TVec3 ey(0,1,0); TVec3 ez(0,0,1);
    _arrow_x->set_position( arrow_pos );
    _arrow_x->compute_from_vec( ex * ex.dot(arrow_vec) );
    _arrow_xy->set_position( arrow_pos + ex * ex.dot(arrow_vec) );
    _arrow_xy->compute_from_vec( ey * ey.dot(arrow_vec) );
    _arrow_xyz->set_position( arrow_pos + ex * ex.dot(arrow_vec) + ey * ey.dot(arrow_vec));
    _arrow_xyz->compute_from_vec( ez * ez.dot(arrow_vec) );
    
    display();

    // update FPS
    double delta_time_frame = _timer_fps.getElapsedTimeInMilliSec() - time_frame_before;
    if( delta_time_frame < _time_frame_min ) _time_frame_min = delta_time_frame;
    if( delta_time_frame > _time_frame_max ) _time_frame_max = delta_time_frame;
    _time_frame_avg = 0.9 * _time_frame_avg + 0.1 * delta_time_frame;
    
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
