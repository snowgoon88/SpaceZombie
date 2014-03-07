// -*- coding: utf-8 -*-
/*
 * Alain - Mar 2012
 */
/**
 * Test des calculs simples avec Eigen.
 */

#include <Eigen/Dense>
#include <iostream>
#include "utils.h"

typedef Eigen::Vector3f TVec3;

void vec_to_angle(float x, float y, float z)
{
  TVec3 v( x, y, z);
  std::cout << "v=" << v << "\n";
  // Projection on Oxy
  TVec3 vxy = v;
  vxy(2) = 0;
  std::cout << "vxy=" << vxy << "\n";
  if( vxy.norm() > 0.0001 ) { 
    // Angle Ox,vxy
    TVec3 ux( 1, 0, 0);
    float Oxv = acos( ux.dot( vxy ) / vxy.norm() / ux.norm());
    std::cout << "Oxv=" << to_deg(Oxv) << " (" << Oxv << ")\n";
    // Angle vxy v
    float vvxy = acos( vxy.dot( v ) / v.norm() / vxy.norm() );
    std::cout << "vvxy=" << to_deg(vvxy) << " (" << vvxy << ")\n";
  }
  else {
    std::cout << "No projection\n";
    float Oxv = 0;
    if( v(2) > 0 ) {
      float vvxy = - M_PI / 2.0;
      std::cout << "Oxv=" << to_deg(Oxv) << " (" << Oxv << ")\n";
      std::cout << "vvxy=" << to_deg(vvxy) << " (" << vvxy << ")\n";
    }
    else {
      float vvxy = M_PI / 2.0;
      std::cout << "Oxv=" << to_deg(Oxv) << " (" << Oxv << ")\n";
      std::cout << "vvxy=" << to_deg(vvxy) << " (" << vvxy << ")\n";
    }    
  }
}
void test_ang_from_vec(float x, float y, float z)
{
  TVec3 v( x, y, z);
  float ang_z1, ang_y2;
  std::cout << "v=" << line_repr(v) << "\n";
  // Projection on Oxy
  TVec3 vxy = v;
  vxy(2) = 0;
  std::cout << "vxy=" << line_repr(vxy) << "\n";
  if( vxy.norm() > 0.0001 ) {
    std::cout << "||vxy|| > 0" << "\n";
    // Angle Ox,vxy
    TVec3 ux( 1, 0, 0);
    ang_z1 = acos( ux.dot( vxy ) / vxy.norm() / ux.norm());
    // Check for the right sign
    if( vxy(1) < 0 ) ang_z1 = -ang_z1;
    std::cout << "ang_z1=" << ang_z1 << "\n";
    
    // Angle vxy v
    ang_y2 = - acos( vxy.dot( v ) / v.norm() / vxy.norm() );
    // Check for the right sign
    if( v(2) < 0 ) ang_y2 = -ang_y2;
    std::cout << "ang_y2=" << ang_y2 << "\n";
  }
  else {
    std::cout << "||vxy|| == 0" << "\n";
    ang_z1 = 0;
    std::cout << "ang_z1=" << ang_z1 << "\n";
    if( v(2) > 0 ) {
      ang_y2 = - M_PI / 2.0;
    }
    else {
      ang_y2 = M_PI / 2.0;
    }
    std::cout << "ang_y2=" << ang_y2 << "\n";
  }
}
void test_product()
{
  TVec3 x(1,0,0);
  TVec3 y(0,1,0);
  TVec3 z(0,0,1);

  std::cout << "x x y = " << line_repr( x.cross(y) ) << "\n";

  std::cout << "n=" << line_repr( (x-z).cross(y-z)) << "\n";
  std::cout << "n=" << line_repr( (x-y).cross(z-y)) << "\n";

}
void test_proj()
{
  TVec3 pos3(1,2,3);
  //TVec2 pos2 = pos3.start(2); ==> Eigen2
  TVec2 pos2 = pos3.head(2);
  std::cout << "pos3=" << line_repr( pos3 ) << "\n";
  std::cout << "pos2=" << line_repr( pos2 ) << "\n";
}
int main(int argc, char *argv[] )
{
  // vec_to_angle(1, 1, 1);
  // vec_to_angle(1, 0, 0);
  // vec_to_angle(1, 0, 1);
  // vec_to_angle(0.5, 0.5, 0.707);
  // vec_to_angle(0, 0, 2);
  // test_product();
  // test_ang_from_vec( 1.41, -1.41, 0.00 );
  test_proj();
}
