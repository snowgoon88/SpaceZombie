// -*- coding: utf-8 -*-
/*
 * Alain - Jan 2012
 */
/**
 * Drawing a simple world and triangles
 * Derived from test_arrow_scigl.cc
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
// Graphic
#include <cstdlib>
#include "scene.h"
#include "ref_frame_scigl.h"
#include "torsor_scigl.h"
#include "textbox.h" 
// AntTweakBar
#include <AntTweakBar.h>

// Physic and Model
#include "bar.h"
#include "bar_scigl.h"
#include "loggedT.h"
#include "loggedTVec3_scigl.h"

// Graphic
ScenePtr _scene = ScenePtr (new Scene);
TextBoxPtr _textbox;
TwBar *_bar;         // Pointer to a tweak bar

// FPS timer
Timer _timer_fps;
//double _time_frame_t1;
double _time_frame_min = DBL_MAX;
double _time_frame_max = DBL_MIN;
double _time_frame_avg = 10.0;
double _time_frame_fps1s, _time_frame_fps5s;
double _fps_1s, _fps_5s;
int _frame_nb_1s = 0;
int _frame_nb_5s = 0;
// PHYSIC timer
double _time_physic;
double _time_physic_min = DBL_MAX;
double _time_physic_max = DBL_MIN;
double _time_physic_avg = 10.0;
bool _fg_physic = false;
bool _fg_physic_step = false;
bool _fg_physic_reset = true;
float _delta_time_physic = 0.001; // 1 ms
//bool _fg_step_physics = false;
//float _gravity = 9.81;

// OBJECTS of the World
// Bar
BarPtr _bar_phy;    
BarSciglPtr _bar_scigl;
SVec3 _bar_pos = {0.0, 0.0, 0.0};
float _bar_dir[3] = {1.0, 1.0, 0.0};
// Torsor
Torsor _torsor;
TorsorSciglPtr _torsor_scigl;
SVec3 _torsor_pos = {0.0, 0.0, 0.0};
float _torsor_res[3] = {0.0, 0.0, 1.0};
float _torsor_mom[3] = {0.0, 0.0, 0.0};
// Application of torsor at various position along the bar
const unsigned int _nb_applied = 9;
TVec3    _v_pos[_nb_applied];
TVec3    _v_applied[_nb_applied];
ArrowPtr _v_applied_scigl[_nb_applied];
const unsigned int _nb_tor = 3;
Torsor _v_tor[_nb_tor];
TorsorSciglPtr _v_tor_scigl[_nb_tor];

// PHYSICS Engine
float _time_simu = 0.0;      // current time
float _delta_step = 0.01;    // 10ms for integration 
float _time_step_next = 1.0;          // when is next bar, 1s
BarPtr _bar_phy_next;            // bar at next time step 
BarSciglPtr _bar_phy_next_scigl;
bool _fg_show_logged = false;
const unsigned int _nb_pt_logged = 3;
LoggedTPtr<TVec3>::Type _v_pt_logged[_nb_pt_logged];
LoggedTVec3SciglPtr _v_pt_logged_scigl[_nb_pt_logged];


//*********************************************************************** PHYSIC
void update_physics( float accel ) 
{
  // get current time 
  double time_now = _timer_fps.getElapsedTimeInMilliSec();
  float delta_t = (time_now - _time_physic) / 1000.0;
  _time_simu += delta_t;

  //std::cout << "PHY delta_t=" << delta_t << " t=" << time_now << " tp=" << _time_physic << " ts=" << _time_simu << "\n";

  for( float dt=0.0f; dt < delta_t; dt += _delta_time_physic ) {
    // apply rotation to bar from central axes
    _bar_phy->set_dir( _bar_phy->_dir + _delta_time_physic * _torsor._r.cross( _bar_phy->_dir ));
    // Move origine : its speed it the torsor applied at the point
    // deplacement
    // @todo should reduce torsor at given point of bar, then move it along this point. It would be cleaner.
    // @todo attach the torsor to a given point of the bar? (or this will be the case when the bar is "fixed" at one extremity ?
    TVec3 delta_p = _delta_time_physic * _torsor.apply( _bar_phy->_ori );
    _bar_phy->set_position( _bar_phy->_ori + delta_p);
    // And then, move the torsor to the new point
    _torsor._p += delta_p;
    //std::cout << "   dt=" << dt << " " << _bar_phy->dump_string() << "\n";
  }

  if( _fg_physic_step ) {
    _fg_physic = false;
    _fg_physic_step = false;
  }

  _time_physic = _timer_fps.getElapsedTimeInMilliSec();
}
void update_physics_step( float delta_t )
{
  // init next bar
  _bar_phy_next->set_position( _bar_phy->_ori );
  _bar_phy_next->set_dir( _bar_phy->_dir );
  // clear logged
  for( unsigned int i = 0; i < _nb_pt_logged; ++i) {
    _v_pt_logged[i]->clear();
  }
  
  Torsor tor = _torsor;

  for( float dt=0.0; dt < delta_t; dt += _delta_step) {
    // apply rotation to bar from central axes
    _bar_phy_next->set_dir( _bar_phy_next->_dir + _delta_step * tor._r.cross( _bar_phy_next->_dir ));
    // Move origine : its speed it the torsor applied at the point
    // @todo should reduce torsor at given point of bar, then move it along this point. It would be cleaner.
    // @todo attach the torsor to a given point of the bar? (or this will be the case when the bar is "fixed" at one extremity ?
    TVec3 delta_p = _delta_step * tor.apply( _bar_phy_next->_ori );
    _bar_phy_next->set_position( _bar_phy_next->_ori + delta_p );
    // And then move torsor point according to bar deplacement.
    tor._p += delta_p;
    // log result
    for( unsigned int i = 0; i < _nb_pt_logged; ++i) {
      TVec3 point;
      _bar_phy_next->get_point_at( -2.0 + ((float) i)/((float) (_nb_pt_logged-1))* 4.0, point);
    _v_pt_logged[i]->add_item( dt, point );
    }
  }
  
  // std::cout << "ORI " << _bar_phy->dump_string() << "\n";
  // std::cout << "   t.r x dir = " << line_repr(_torsor._r.cross( _bar_phy->_dir)) << "\n";
  // std::cout << "   t.apply=" << line_repr( _torsor.apply( _bar_phy->_ori ) ) << "\n";
  // std::cout << "NEW " << _bar_phy_next->dump_string() << "\n";
}
void init_physic()
{
  _bar_phy = BarPtr( new Bar( TVec3( _bar_pos.x, _bar_pos.y, _bar_pos.z),
			      Eigen::Map<TVec3>(_bar_dir),
			      -2.0f, 2.0f ));

  _torsor = Torsor( Eigen::Map<TVec3>(_torsor_res),
		    Eigen::Map<TVec3>(_torsor_mom),
		    TVec3( _torsor_pos.x, _torsor_pos.y, _torsor_pos.z ));
  
  _bar_phy_next = BarPtr( new Bar(*_bar_phy));
  // Logged pts of the bar
  for( unsigned int i = 0; i < _nb_pt_logged; ++i) {
    //_v_pt_logged[i] = LoggedTVec3Ptr (new LoggedT<TVec3>);
    _v_pt_logged[i] = LoggedTPtr<TVec3>::Type (new LoggedT<TVec3>);
  }

  if( _fg_show_logged ) {
    update_physics_step( _time_step_next );
  }

  // Torsor applied at different points of the bar
  //std::cout << "INIT_PHYSICS" << "\n";
  for( unsigned int i = 0; i < _nb_applied; ++i) {
    _bar_phy->get_point_at( -2.0 + ((float) i)/((float) (_nb_applied-1))* 4.0, _v_pos[i]); 
    _v_applied[i] = _torsor.apply( _v_pos[i] );
    //std::cout << "[" << i << "] pos=" << line_repr(_v_pos[i]) << " res=" <<  line_repr(_v_applied[i]) << "\n";
  }

  // Torsor reduced at different points of the bar
  for( unsigned int i = 0; i < _nb_tor; ++i) {
    _v_tor[i] = Torsor( _torsor );
  }

}
//******************************************************************** INTERFACE
// @todo use TwCallback for avoiding waste of time in updating non-changed elements or modify model to remember if changed...
void update_interface()
{
  // Reset = simu is stopped and reseted
  if( _fg_physic_reset ) {
    _fg_physic = false; _fg_physic_step = false;
    _time_physic = _timer_fps.getElapsedTimeInMilliSec();
    _time_simu = 0.0;
    
    _bar_phy->set_position( TVec3( _bar_pos.x, _bar_pos.y, _bar_pos.z) );
    _bar_phy->set_dir( Eigen::Map<TVec3>(_bar_dir) );
    _torsor._p = TVec3( _torsor_pos.x, _torsor_pos.y, _torsor_pos.z );
  }
  // ! fg_physic = simu is stopped
  if( !_fg_physic and !_fg_physic_step ) {
    _time_physic = _timer_fps.getElapsedTimeInMilliSec();
  }
  
  _torsor._r = Eigen::Map<TVec3>(_torsor_res);
  _torsor._m = Eigen::Map<TVec3>(_torsor_mom);
  

  if( _fg_show_logged ) {
    update_physics_step( _time_step_next );
  }
  
  // Torsor applied at different points of the bar
  for( unsigned int i = 0; i < _nb_applied; ++i) {
    
    _bar_phy->get_point_at( -2.0 + ((float) i)/((float) (_nb_applied-1))* 4.0, _v_pos[i]); 
    _v_applied[i] = _torsor.apply( _v_pos[i] );
  }

  // Torsor reduced at different points of the bar
  for( unsigned int i = 0; i < _nb_tor; ++i) {
    TVec3 point;
    _bar_phy->get_point_at( -2.0 + ((float) i)/((float) (_nb_tor-1))* 4.0, point);
    _v_tor[i] = _torsor;
    _v_tor[i].reduce_at( point );
  }
}
//******************************************************************** OBSERVERS
// @todo : should not exists...
void update_observers()
{
  for( unsigned int i = 0; i < _nb_pt_logged; ++i) {
    _v_pt_logged_scigl[i]->set_visible( _fg_show_logged ); // control
  }
  _bar_phy_next_scigl->set_visible( _fg_show_logged ); // control

  _torsor_scigl->update();
  // Torsor applied at different points of the bar
  //std::cout << "UPDATE_OBSERVERS" << "\n";
  for( unsigned int i = 0; i < _nb_applied; ++i) {
    _v_applied_scigl[i]->set_position( _v_pos[i] );
    _v_applied_scigl[i]->compute_from_vec( _v_applied[i] );
    //std::cout << "[" << i << "] pos=" << line_repr(_v_pos[i]) << " res=" <<  line_repr(_v_applied[i]) << "\n";
  }
  
  // Torsor reduced
  for( unsigned int i = 0; i < _nb_tor; ++i) {
    _v_tor_scigl[i]->update();
  }
}
void init_observers() 
{
  _bar_scigl = BarSciglPtr( new BarScigl( _bar_phy ));
  _scene->add( _bar_scigl );
  
  _torsor_scigl = TorsorSciglPtr( new TorsorScigl( TorsorPtr(&_torsor) ));
  _torsor_scigl->set_color( 0.8, 0.0, 0.8, 1.0 );
  _torsor_scigl->_fg_axis = true;
  _scene->add( _torsor_scigl );

  _bar_phy_next_scigl = BarSciglPtr( new BarScigl( _bar_phy_next ));
  _bar_phy_next_scigl->set_fg_color( 0.6, 0.6, 0.6, 1.0 );
  _scene->add( _bar_phy_next_scigl );

  // Torsor application
  for( unsigned int i = 0; i < _nb_applied; ++i) {
    _v_applied_scigl[i] = ArrowPtr( new Arrow( _v_applied[i] ));
    _v_applied_scigl[i]->set_br_color( 0.6, 0.3, 0.0, 1.0 );
    _v_applied_scigl[i]->set_fg_color( 0.6, 0.3, 0.0, 1.0 );
    _scene->add( _v_applied_scigl[i] );
  }

  // Torsor reduction
  for( unsigned int i = 0; i < _nb_tor; ++i) {
    _v_tor_scigl[i] = TorsorSciglPtr( new TorsorScigl( TorsorPtr(&_v_tor[i]) ));
    _v_tor_scigl[i]->set_color( 1.0, 0.686, 1.0, 1.0);
    _scene->add( _v_tor_scigl[i] );
  }

  // pt logged along bar
  for( unsigned int i = 0; i < _nb_pt_logged; ++i) {
    _v_pt_logged_scigl[i] = LoggedTVec3SciglPtr (new LoggedTVec3Scigl( _v_pt_logged[i] ));
    _v_pt_logged_scigl[i]->set_br_color( 0.0, 0.0, 0.7, 1.0 );
    _v_pt_logged_scigl[i]->set_visible( _fg_show_logged );
    _scene->add( _v_pt_logged_scigl[i] );
  }
  
}
//******************************************************************** INTERFACE
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
  ss << "Disp. " << SETPREC(3) << _time_frame_min << " / " << SETPREC(3) << _time_frame_avg << " / " << SETPREC(3) <<_time_frame_max << " ";
  ss << "  ";
  ss << "Phy. " << SETPREC(3) << _time_physic_min << " / " << SETPREC(3) << _time_physic_avg << " / " << SETPREC(3) << _time_physic_max << " ";

  ss << "\n";
  ss << _bar_phy->dump_string() << "\n";
  ss << _torsor.display_str();
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

  // init physic
  init_physic();
  update_interface();

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
  _bar = TwNewBar("_scene");
  TwDefine( " _scene iconified=false position='10 55' size='230 700'");
  TwType tw_SVec3 = TwDefineStruct("Vec3", SVec3Members, 3, sizeof(SVec3), NULL, NULL);
  // BAR
  TwAddVarRW( _bar, "_bar_ori", tw_SVec3, &(_bar_pos), " Group='Bar' Label='Ori' ");
  TwAddVarRW( _bar, "_bar_dir", TW_TYPE_DIR3F, &_bar_dir, " Group='Bar' Label='Dir'");
  // TORSOR
  TwAddVarRW( _bar, "_torsor_pos", tw_SVec3, &(_torsor_pos), " Group='Torsor Cinematique' Label='Ori' ");
  TwAddVarRW( _bar, "_torsor_res", TW_TYPE_DIR3F, &_torsor_res, " Group='Torsor Cinematique' Label='Rotation'");
  TwAddVarRW( _bar, "_torsor_mom", TW_TYPE_DIR3F, &_torsor_mom, " Group='Torsor Cinematique' Label='Vitesse'");
  // PHYSIC
  TwAddVarRW( _bar, "_fg_physic_reset", TW_TYPE_BOOLCPP, &_fg_physic_reset, "Group='Physic' Label='Reset'");
  TwAddVarRW( _bar, "_fg_physic", TW_TYPE_BOOLCPP, &_fg_physic, "Group='Physic' Label='Go'");
  TwAddVarRW( _bar, "_fg_physic_step", TW_TYPE_BOOLCPP, &_fg_physic_step, "Group='Physic' Label='Step'");
  // TIME
  TwAddVarRW( _bar, "_fg_show_logged", TW_TYPE_BOOLCPP, &_fg_show_logged, "Group='Time' Label='Show next'");
  TwAddVarRW( _bar, "_time_step_next", TW_TYPE_FLOAT, &_time_step_next, "Group='Time' Label='T next' min=0.0 max=300.0 step=0.1 keyIncr=t keyDecr=T");
  // ------------------------------- end AntTweakBar

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
  //_ref->set_size( 0.5, 0.5, 0.5 );
  _ref->_ang_Oz1 =  0.0;
  _ref->_ang_Ox1 =  0.0;
  _ref->_ang_Oz2 =  0.0;
  _scene->add( _ref );

  // Some Torsor
  //_scene->add( _tor );

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

  // init observers
  init_observers();
  update_observers();
  
  _scene->setup();
  _scene->update();


  // Init FPS
  _timer_fps.start();
  double time = _timer_fps.getElapsedTimeInMilliSec();
  _time_frame_fps1s = time;
  _time_frame_fps5s = time;
  _time_physic = time;
  _time_step_next = 0;

  // Main loop of GLFW
  do {
    // Get window size (may be different than the requested size)
    glfwGetWindowSize( &width, &height );
    // Special case: avoid division by zero below
    height = height > 0 ? height : 1;
    
    glViewport( 0, 0, width, height );
    TwWindowSize(width, height);
    
    // BEGIN of loop 
    double time_frame_before = _timer_fps.getElapsedTimeInMilliSec();
    double time_physic_before = _timer_fps.getElapsedTimeInMilliSec();
    
    // PHYSICS
    update_interface();
    if( _fg_physic or _fg_physic_step) {
      update_physics( 1.0 );
    }

    // TIMER physic
    double delta_time_physic = _timer_fps.getElapsedTimeInMilliSec() - time_physic_before;
    if( delta_time_physic < _time_physic_min ) _time_physic_min = delta_time_physic;
    if( delta_time_physic > _time_physic_max ) _time_physic_max = delta_time_physic;
    _time_physic_avg = 0.9 * _time_physic_avg + 0.1 * delta_time_physic;

    // DISPLAY
    update_observers();
    display();
    
    // TIMER FPS
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
