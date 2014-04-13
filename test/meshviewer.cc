// -*- coding: utf-8 -*-
/** @file test_triangles_scigl.cc
 * Drawing a simple world and triangles
 *
 * + a textbox above
 * + the_scene : made of a RefFrame and a Triangles. 
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
 * Derived from test_arrow_scigl.cc
 * @author Alain
 * @date 12/2013
 */
#include "utils.h"
#include "object.h" 
#include "file_scdata.h"     // SC data files

#include <GL/glew.h>
#include <GL/glfw.h>

#include <float.h>
#include "timer.h"

#include <iostream>

// Graphic
#include <cstdlib>
#include "scene.h"
#include "ref_frame_scigl.h"
#include "mesh_model.h"
#include "mesh_viewer_scigl.h"
#include "mesh_control.h"
#include "textbox.h" 
// AntTweakBar
#include <AntTweakBar.h>

// Graphic
ScenePtr _scene = ScenePtr (new Scene);
TextBoxPtr _textbox;
TwBar *_bar;         // Pointer to a tweak bar


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
  std::cout << "ARGC=" << argc << "\n";
  // Some graphic parameters
  int width, height;

  // Scene
  MeshModelPtr _mesh_model = MeshModelPtr( new MeshModel );
  MeshViewerPtr _mesh_viewer = MeshViewerPtr( new MeshViewer( _mesh_model ) );
  MeshControlPtr _mesh_control = MeshControlPtr( new MeshControl( _mesh_model, _mesh_viewer) );
  _mesh_model->attach_observer( _mesh_viewer );
  
  std::string filename = "SCData/data/misc/cube1m.mdl-msh000";
  // read argv[1] if provided
  if (argc > 1) {
    filename.assign(argv[1]);
  }
  // init mesh from SCData
  // FileSCData fscdata( "SCData/data/misc/cube1m.mdl-msh000" );
  // FileSCData fscdata( "SCData/data/race1_l_t1.mdl-msh000" );
  FileSCData fscdata( filename );
  fscdata.read( true );
  std::cout << fscdata.str_brief() << "\n";
  _mesh_model->attach( &fscdata );
  _mesh_model->dump( std::cout );
  //_mesh_model->_v_color = _mesh_model->_v_color_default;


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
  glfwSetWindowTitle( "test_triangles_scigl" );
  
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
  //  float tw_tri_dir[3] = {1, 0, 0}; // direction pointing to +x and +y
  TwInit(TW_OPENGL, NULL);
  //   // Create a tweak bar
  _mesh_control->build_bar();

//   _bar = TwNewBar("_scene");
//   TwType tw_SVec3 = TwDefineStruct("Vec3", SVec3Members, 3, sizeof(SVec3), NULL, NULL);
//   TwAddVarRW( _bar, "_vec0", tw_SVec3, &(_vec_vertex[0]), " Label='Point_0' ");
//   TwAddVarRW( _bar, "_vec1", tw_SVec3, &(_vec_vertex[1]), " Label='Point_1' ");
//   TwAddVarRW( _bar, "_vec2", tw_SVec3, &(_vec_vertex[2]), " Label='Point_2' ");
// // ...
//   TwAddVarRW( _bar, "_tri_dir", TW_TYPE_DIR3F, &tw_tri_dir, " Label='Dir'");
//   TwAddVarRW( _bar, "fg_normal", TW_TYPE_BOOLCPP, &(_triangles->_fg_normal), " Label='fg_normal'" );
//   TwAddVarRW( _bar, "fg_light", TW_TYPE_BOOLCPP, &(_triangles->_fg_light), " Label='fg_light'" );
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
  std::cout << "MeshControl built" << "\n";

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

  // Some Mesh
   _scene->add( _mesh_viewer );

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

    // Values set in AntTWeakBar => orientation of the _triangles.
    //_mesh_viewer->orient_from_vec( TVec3( tw_tri_dir[0], tw_tri_dir[1], tw_tri_dir[2] ));
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
  std::cout << "Terminate TW" << "\n";
  TwTerminate();
  std::cout << "Terminate GLFW" << "\n";
  glfwTerminate();
  std::cout << "End of Prog" << "\n";

  return 0;
}
