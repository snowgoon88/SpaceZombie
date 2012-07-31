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

#include <float.h>
#include "timer.h"

#include <iostream>
// Graphic
#include <cstdlib>
#include "scene.h"
#include "ref_frame_scigl.h"
#include "textbox.h" 
// AntTweakBar
#include <AntTweakBar.h>

// Game
#include "game_model.h"
#include "game_observer.h"
GameModelPtr _game_model;
GameObserverPtr _game_observer;

// Graphic
ScenePtr _scene = ScenePtr (new Scene);
TextBoxPtr _textbox;
TwBar *_bar;         // Pointer to a tweak bar

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

// PHYSIC
#include "physic_engine.h"
PhysicEnginePtr _phys_engine;
double _time_physic;
double _time_physic_min = DBL_MAX;
double _time_physic_max = DBL_MIN;
double _time_physic_avg = 10.0;
bool _fg_physics = false;
bool _fg_step_physics = false;
float _gravity = 9.81;

/**
 * Update the physic of the World
 */
// Apply gravity when slope non-nul and stick to cell (no vertical rebound)
// void update_physic_gravity()
// {
//   double time_current = _timer_fps.getElapsedTimeInMilliSec();


//   // APPLICATION OF EXTERNAL FORCES : Gravity.
//   if( _fg_physics or _fg_step_physics ) {
//     float next_x, next_y, next_z;
//     PhyPointPtr pl = _world->_player;
//     if( pl->_player_state == PhyPoint::s_CONTACT ) {
//       // Apply gravity + ground reaction
//       // gravity : toward negative Z
//       // Projection de G sur repère sol Sxz. alpha = -PI/2 - angX
//       // Gsx = G cos(alpha), Gsz = G sin(alpha)
//       // Projection sur Oxz
//       // Fx = Gsx cos( angX ) = G cos(alpha)cos(angX)
//       // Fz = Gsz sin( angX ) = G cos(alpha)sin(angX)
//       // Only one of grav_sx or grav_sy shall be non-null
//       float grav_sx = _gravity * cosf( -M_PI / 2.0 - pl->_curr_cell->_ang_y );
//       float grav_sy = _gravity * cosf( -M_PI / 2.0 - pl->_curr_cell->_ang_x );
//       pl->apply_force( time_current - _time_physic, 
// 		       grav_sx * cosf( pl->_curr_cell->_ang_y ),
// 		       grav_sy * cosf( pl->_curr_cell->_ang_x ),
// 		       grav_sx * sinf( pl->_curr_cell->_ang_y ) + grav_sy * sinf( pl->_curr_cell->_ang_x ) );
//     }
//     else {
//       // Apply gravity
//       pl->apply_force( time_current - _time_physic, 
// 		       0.0, 0.0, -_gravity );
//     }

//     pl->get_future_pos(  time_current - _time_physic,
// 			 next_x, next_y, next_z );
//     std::cout << " next_p => (" << next_x << ", " << next_y << ", " << next_z << "\n";
//     CellPtr next_cell = _world->get_cell_at( next_x, next_y, next_z );
//     std::cout << pl->repr_dump() << "\n";
//     std::cout << "@@@ cur=" << (pl->_curr_cell ? pl->_curr_cell->repr_dump() : "NULL") << "\n";
//     std::cout << "@@@ next=" << (next_cell ? next_cell->repr_dump() : "NULL") << "\n";


//     // REALISATION OF MOVEMENT
//     float cur_z = pl->_z; // needed to correct speed
//     if( pl->_player_state == PhyPoint::s_CONTACT ) {
//       // Check if leaving cell
//       unsigned int dir;
//       if( pl->_curr_cell->is_leaving_cell( next_x, next_y, dir ) ) {
// 	// Check if neigbor cell in the dir of mouvement
// 	CellPtr neighbor_cell = pl->_curr_cell->_neighbors[dir];
// 	std::cout << "@@@ neighbor=" << (neighbor_cell ? neighbor_cell->repr_dump() : "NULL") << "\n";
// 	if( neighbor_cell ) {
// 	  // s_CONTACT [AND cell] -> cell_voisine : stick & s_CONTACT
// 	  std::cout << "s_CONTACT [AND cell] -> cell_voisine : stick & s_CONTACT\n";
// 	  // _player_state is the same
// 	  pl->_x = next_x;
// 	  pl->_y = next_y;
// 	  pl->_z = neighbor_cell->get_z_at( next_x, next_y );
// 	  next_cell = neighbor_cell;
// 	}
// 	else if( !next_cell ) {
// 	  // s_CONTACT [AND cell] -> null : REBOUND
// 	  std::cout << "s_CONTACT [AND cell] -> null : REBOUND\n";
// 	  // _player_state is the same
// 	  // Compute rebond
// 	  switch( dir ) {
// 	  case 0: // North
// 	    // update position : rebound toward South
// 	    pl->_y = pl->_curr_cell->_y + pl->_curr_cell->size -
// 	      (next_y - (pl->_curr_cell->_y + pl->_curr_cell->size));
// 	    // Invert vy
// 	    pl->_vy = -(pl->_vy );
// 	    break;
// 	  case 2: // South
// 	    // update position : rebound toward North
// 	    pl->_y = pl->_curr_cell->_y - pl->_curr_cell->size +
// 	      ((pl->_curr_cell->_y - pl->_curr_cell->size) - next_y);
// 	    // Invert vy
// 	    pl->_vy = -(pl->_vy );
// 	    break;
// 	  case 1: // East
// 	    // update position : rebound toward West
// 	    pl->_x = pl->_curr_cell->_x + pl->_curr_cell->size -
// 	      (next_x - (pl->_curr_cell->_x + pl->_curr_cell->size));
// 	    // Invert vx
// 	    pl->_vx = -(pl->_vx);
// 	    break;
// 	  case 3: // West
// 	    // update position : rebound toward East
// 	    pl->_x = pl->_curr_cell->_x - pl->_curr_cell->size +
// 	      ((pl->_curr_cell->_x - pl->_curr_cell->size) - next_x);
// 	    // Invert vx
// 	    pl->_vx = -(pl->_vx);
// 	    break;
// 	  }
// 	  next_cell = pl->_curr_cell;
// 	}
// 	else {
// 	  // s_CONTACT [AND cell] -> cell : stick & s_CONTACT
// 	  std::cout << "s_CONTACT [AND cell] -> cell : stick & s_CONTACT\n";
// 	  // _player_state is the same
// 	  pl->_x = next_x;
// 	  pl->_y = next_y;
// 	  pl->_z = next_cell->get_z_at( next_x, next_y );	
// 	}
// 	pl->_curr_cell = next_cell;
//       }
//       else {
// 	// s_CONTACT [AND cell] -> cell_same : stick & s_CONTACT
// 	std::cout << "s_CONTACT [AND cell] -> cell_same : stick & s_CONTACT\n";
// 	// _player_state is the same
// 	pl->_x = next_x;
// 	pl->_y = next_y;
// 	pl->_z = pl->_curr_cell->get_z_at( next_x, next_y );
//       }
//     }
//     else {
//       if( !next_cell ) {
// 	// s_VOID -> null : s_VOID
// 	std::cout << "s_VOID -> null : s_VOID\n";
// 	// _player_state is the same
// 	pl->_x = next_x;
// 	pl->_y = next_y;
// 	pl->_z = next_z;
//       }
//       else {
// 	// s_VOID -> cell : stick & s_CONTACT
// 	std::cout << "s_VOID -> cell : stick & s_CONTACT\n";
// 	pl->_player_state = PhyPoint::s_CONTACT;
// 	pl->_x = next_x;
// 	pl->_y = next_y;
// 	pl->_z = next_cell->get_z_at( next_x, next_y );	
//       }
//       pl->_curr_cell = next_cell;
//     }
//     // Correction of vz
//     pl->_vz = (pl->_z - cur_z)/(time_current - _time_physic);
//   }
//   _fg_step_physics = false;
//   _time_physic = time_current;
// }

// // Rebond on side of cells without neigbors and without cell below
// void update_physic_rebound()
// {
//   double time_current = _timer_fps.getElapsedTimeInMilliSec();
  
//   if( _fg_physics ) {
//     float next_x, next_y, next_z;
//     PhyPointPtr pl = _world->_player;
//     pl->get_future_pos(  time_current - _time_physic,
// 			 next_x, next_y, next_z );
//     CellPtr next_cell = _world->get_cell_at( next_x, next_y, next_z );
//     std::cout << pl->repr_dump() << "\n";
//     std::cout << "@@@ cur=" << (pl->_curr_cell ? pl->_curr_cell->repr_dump() : "NULL") << "\n";
//     std::cout << "@@@ next=" << (next_cell ? next_cell->repr_dump() : "NULL") << "\n";

//     if( pl->_player_state == PhyPoint::s_CONTACT ) {
//       // Check if leaving cell
//       unsigned int dir;
//       if( pl->_curr_cell->is_leaving_cell( next_x, next_y, dir ) ) {
// 	// Check if neigbor cell in the dir of mouvement
// 	CellPtr neighbor_cell = pl->_curr_cell->_neighbors[dir];
// 	std::cout << "@@@ neighbor=" << (neighbor_cell ? neighbor_cell->repr_dump() : "NULL") << "\n";
// 	if( neighbor_cell ) {
// 	  // s_CONTACT [AND cell] -> cell_voisine : stick & s_CONTACT
// 	  std::cout << "s_CONTACT [AND cell] -> cell_voisine : stick & s_CONTACT\n";
// 	  // _player_state is the same
// 	  pl->_x = next_x;
// 	  pl->_y = next_y;
// 	  pl->_z = neighbor_cell->get_z_at( next_x, next_y );
// 	  next_cell = neighbor_cell;
// 	}
// 	else if( !next_cell ) {
// 	  // s_CONTACT [AND cell] -> null : REBOUND
// 	  std::cout << "s_CONTACT [AND cell] -> null : REBOUND\n";
// 	  // _player_state is the same
// 	  // Compute rebond
// 	  switch( dir ) {
// 	  case 0: // North
// 	  case 2: // South
// 	    pl->_vy = -(pl->_vy );
// 	    break;
// 	  case 1: // East
// 	  case 3: // West
// 	    pl->_vx = -(pl->_vx);
// 	    break;
// 	  }
// 	  // TODO : Apply gravity
// 	  pl->_x = next_x;
// 	  pl->_y = next_y;
// 	  pl->_z = next_z;
// 	  next_cell = pl->_curr_cell;
// 	}
// 	else {
// 	  // s_CONTACT [AND cell] -> cell : stick & s_CONTACT
// 	  std::cout << "s_CONTACT [AND cell] -> cell : stick & s_CONTACT\n";
// 	  // _player_state is the same
// 	  pl->_x = next_x;
// 	  pl->_y = next_y;
// 	  pl->_z = next_cell->get_z_at( next_x, next_y );	
// 	}
// 	pl->_curr_cell = next_cell;
//       }
//       else {
// 	// s_CONTACT [AND cell] -> cell_same : stick & s_CONTACT
// 	std::cout << "s_CONTACT [AND cell] -> cell_same : stick & s_CONTACT\n";
// 	// _player_state is the same
// 	pl->_x = next_x;
// 	pl->_y = next_y;
// 	pl->_z = pl->_curr_cell->get_z_at( next_x, next_y );
//       }
//     }
//     else {
//       if( !next_cell ) {
// 	// s_VOID -> null : s_VOID
// 	std::cout << "s_VOID -> null : s_VOID\n";
// 	// _player_state is the same
// 	pl->_x = next_x;
// 	pl->_y = next_y;
// 	pl->_z = next_z;
//       }
//       else {
// 	// s_VOID -> cell : stick & s_CONTACT
// 	std::cout << "s_VOID -> cell : stick & s_CONTACT\n";
// 	pl->_player_state = PhyPoint::s_CONTACT;
// 	pl->_x = next_x;
// 	pl->_y = next_y;
// 	pl->_z = next_cell->get_z_at( next_x, next_y );	
//       }
//       pl->_curr_cell = next_cell;
//     }
//   }
//   _time_physic = time_current;
// }
// // La physique particulière de l'instant
// // suit les cases ou reste de niveau
// // s_CONTACT [AND cell] -> cell_same : stick & s_CONTACT
// // s_CONTACT [AND cell] -> cell_voisine : stick & s_CONTACT
// // s_CONTACT [AND cell] OR s_VOID -> cell : stick & s_CONTACT
// // s_CONTACT [AND cell] OR s_VOID -> null : s_VOID
// void update_physic_slope()
// {
//   double time_current = _timer_fps.getElapsedTimeInMilliSec();
  
//   if( _fg_physics ) {
//     float next_x, next_y, next_z;
//     PhyPointPtr pl = _world->_player;
//     pl->get_future_pos(  time_current - _time_physic,
// 			 next_x, next_y, next_z );
//     CellPtr next_cell = _world->get_cell_at( next_x, next_y, next_z );
//     std::cout << "@@@ next=" << (next_cell ? next_cell->repr_dump() : "NULL") << "\n";

//     if( pl->_player_state == PhyPoint::s_CONTACT ) {
//       // Check if leaving cell
//       unsigned int dir;
//       if( pl->_curr_cell->is_leaving_cell( next_x, next_y, dir ) ) {
// 	// Check if neigbor cell in the dir of mouvement
// 	CellPtr neighbor_cell = pl->_curr_cell->_neighbors[dir];
// 	std::cout << "@@@ neighbor=" << (neighbor_cell ? neighbor_cell->repr_dump() : "NULL") << "\n";
// 	if( neighbor_cell ) {
// 	  // s_CONTACT [AND cell] -> cell_voisine : stick & s_CONTACT
// 	  std::cout << "s_CONTACT [AND cell] -> cell_voisine : stick & s_CONTACT\n";
// 	  // _player_state is the same
// 	  pl->_x = next_x;
// 	  pl->_y = next_y;
// 	  pl->_z = neighbor_cell->get_z_at( next_x, next_y );
// 	  next_cell = neighbor_cell;
// 	}
// 	else if( !next_cell ) {
// 	  // s_CONTACT [AND cell] -> null : s_VOID
// 	  std::cout << "s_CONTACT [AND cell] -> null : s_VOID\n";
// 	  pl->_player_state = PhyPoint::s_VOID;
// 	  pl->_x = next_x;
// 	  pl->_y = next_y;
// 	  pl->_z = next_z;
// 	}
// 	else {
// 	  // s_CONTACT [AND cell] -> cell : stick & s_CONTACT
// 	  std::cout << "s_CONTACT [AND cell] -> cell : stick & s_CONTACT\n";
// 	  // _player_state is the same
// 	  pl->_x = next_x;
// 	  pl->_y = next_y;
// 	  pl->_z = next_cell->get_z_at( next_x, next_y );	
// 	}
// 	pl->_curr_cell = next_cell;
//       }
//       else {
// 	// s_CONTACT [AND cell] -> cell_same : stick & s_CONTACT
// 	std::cout << "s_CONTACT [AND cell] -> cell_same : stick & s_CONTACT\n";
// 	// _player_state is the same
// 	pl->_x = next_x;
// 	pl->_y = next_y;
// 	pl->_z = pl->_curr_cell->get_z_at( next_x, next_y );
//       }
//     }
//     else {
//       if( !next_cell ) {
// 	// s_VOID -> null : s_VOID
// 	std::cout << "s_VOID -> null : s_VOID\n";
// 	// _player_state is the same
// 	pl->_x = next_x;
// 	pl->_y = next_y;
// 	pl->_z = next_z;
//       }
//       else {
// 	// s_VOID -> cell : stick & s_CONTACT
// 	std::cout << "s_VOID -> cell : stick & s_CONTACT\n";
// 	pl->_player_state = PhyPoint::s_CONTACT;
// 	pl->_x = next_x;
// 	pl->_y = next_y;
// 	pl->_z = next_cell->get_z_at( next_x, next_y );	
//       }
//       pl->_curr_cell = next_cell;
//     }
//   }
//   _time_physic = time_current;
// }
// // Stick to cells in going down.
// // WARN::Would not be able to 'climb' a cell.
// void update_physic_follow()
// {
//   double time_current = _timer_fps.getElapsedTimeInMilliSec();
  
//   if( _fg_physics ) {
//     // Move player
//     _world->_player->get_future_pos(  time_current - _time_physic,
// 				      _world->_player->_x,
// 				      _world->_player->_y,
// 				      _world->_player->_z );
    
//     CellPtr cell_cur = _world->get_cell_at( _world->_player->_x,
// 					    _world->_player->_y,
// 					    _world->_player->_z, true);
//     // Above a cell ?
//     if( cell_cur ) {
//       // stick to it
//       _world->_player->_z = cell_cur->get_z_at( _world->_player->_x, _world->_player->_y );
//       _world->_player->_fg_contact = true;
//     }
//     else {
//       _world->_player->_fg_contact = false;
//     }
//   }
//   _time_physic = time_current;
// }
// // straight line, no collision -------------------------------------------
// void update_physic()
// {
//   double time_current = _timer_fps.getElapsedTimeInMilliSec();
//   _world->_player->get_future_pos(  time_current - _time_physic,
// 				   _world->_player->_x,
// 				   _world->_player->_y,
// 				   _world->_player->_z );
//   _time_physic = time_current;
// }

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
      // // d or D : dump world
      // else if( ((key == 100) || (key == 68))  && (action == GLFW_PRESS)) {
      // 	std::cout << _world->repr_dump();
      // }
      
      else {
	std::cout << "key=" << key << " act=" << action << "(" << GLFW_KEY_TAB << ", " << GLFW_PRESS << ")" << std::endl;
        }
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
  ss << "Phy. " << _time_physic_min << " / " << _time_physic_avg << " / " << _time_physic_max << " ";
  //ss << "\n" << _world->_player->repr_dump();
  _textbox->set_buffer( ss.str() );
}
/**
 * Display the Scene, and thus every object in it.
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
  // World
  _game_model = GameModelPtr( new GameModel() );
  _game_observer = GameObserverPtr( new GameObserver( _game_model ));

  // Physic Engine
  _phys_engine = PhysicEnginePtr( new PhysicEngine( _game_model ));
  
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
  _bar = TwNewBar("_world");
  TwDefine( " _world iconified=true position='10 50'");
  //TwDefine( " GLOBAL help='AntTweak to alter rotation angle.' "); // Msg to the help bar.
  TwAddVarRW( _bar, "fg_physic", TW_TYPE_BOOLCPP, &(_fg_physics),
	      " label='fg_physics' keyIncr=g keyDecr=G help='FLAG physics engine' ");
  TwAddVarRW( _bar, "fg_step_physics", TW_TYPE_BOOLCPP, &(_fg_step_physics),
	      " label='fg_step' keyIncr=f keyDecr=F help='FLAG STEP physics engine' ");
  // Add '_angX' to bar : modifiable (RW), FLOAT, [0,360]
  //TwAddVarRW( _bar, "angX", TW_TYPE_FLOAT, &_angX, 
  //	      " label='AngX' min=0 max=360 step=1.0 keyIncr=x KeyDecr=X help='Rotation angle around Oz' ");
  // Add '_angZ' to bar : modifiable (RW), FLOAT, [0,360]

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

  // Observer
  _game_observer->init( _scene );

  
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

  // Then a text box with parameters
  _textbox = TextBoxPtr (new TextBox);
  _textbox->set_position( 0, 0, 1); // z=1 : front
  _textbox->set_fg_color (0,0,0,1);
  _textbox->set_bg_color (.9,.9,.9,.8);
  _textbox->set_fontsize (0);
  _textbox->set_autosize( false );
  _textbox->set_size( 1.0, 50, 1 );
  update_textbox();


  // Init FPS
  _timer_fps.start();
  double time = _timer_fps.getElapsedTimeInMilliSec();
  _time_frame_fps1s = time;
  _time_frame_fps5s = time;
  // Physics
  _time_physic = time;
  _phys_engine->start( _time_physic );
  // Main loop of GLFW
  do {
    // Get window size (may be different than the requested size)
    glfwGetWindowSize( &width, &height );
    // Special case: avoid division by zero below
    height = height > 0 ? height : 1;
    
    glViewport( 0, 0, width, height );
    TwWindowSize(width, height);
    
    // PHYSICS
    double time_physic_before = _timer_fps.getElapsedTimeInMilliSec();
    if( _fg_physics or _fg_step_physics ) {
      _phys_engine->update( time_physic_before - _time_physic );
      _fg_step_physics = false;
    }
    _time_physic = time_physic_before;

    double delta_time_physic = _timer_fps.getElapsedTimeInMilliSec() - _time_physic;
    if( delta_time_physic < _time_physic_min ) _time_physic_min = delta_time_physic;
    if( delta_time_physic > _time_physic_max ) _time_physic_max = delta_time_physic;
    _time_physic_avg = 0.9 * _time_physic_avg + 0.1 * delta_time_physic;

    // display
    double time_frame_before = _timer_fps.getElapsedTimeInMilliSec();
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
