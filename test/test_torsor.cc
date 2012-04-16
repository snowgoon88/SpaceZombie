// -*- coding: utf-8 -*-
/*
 * Alain - Mar 2012
 */
/**
 * Test des torseurs.
 */

#include "torsor.h"

void tt_assign_add()
{
  Torsor t1( TVec3(1,2,3), TVec3(4,5,6));
  std::cout << "t1 = " << t1.display_str(2) << "\n";

  Torsor t2( t1 );
  std::cout << "t2 = " << t2.display_str(2) << "\n";

  Torsor t3;
  std::cout << "t3 = " << t3.display_str(3) << "\n";
  t3 = t2;
  std::cout << "t3 = " << t3.display_str(3) << "\n";

  Torsor t4( TVec3(0.1,0.2,0.3), TVec3(0.11, 0.22, 0.33));
  std::cout << "t4 = " << t4.display_str(3) << "\n";
  std::cout << "t3+t4 = " << (t3+t4).display_str(3) << "\n";

  Torsor t5;
  t5 = (t3-t4);
  std::cout << "t5 = " << t5.display_str(3) << "\n";

  Torsor t6( TVec3(0.1,0.2,0.3), TVec3(0.11, 0.22, 0.33), TVec3(1,1,1));
  std::cout << "t6 = " << t6.display_str(3) << "\n";
  std::cout << "t3+t6 = " << (t3+t6).display_str(3) << "\n";
  
  t2 = t2 * 2;
  std::cout << "t2*2 = " << t2.display_str(2) << "\n";

  std::cout << "t2*t4 = " << t2.comoment(t4) << "\n";
  std::cout << "A(t2) = " << t2.automoment() << "\n";

  std::cout << "t6 at 0,0,0 = " << line_repr( t6.apply( TVec3(0,0,0) )) << "\n";
  std::cout << "t6 at 1,1,1 = " << line_repr( t6.apply( TVec3(1,1,1) )) << "\n";
  
  t6.reduce_at( TVec3(0,0,0 ));
  std::cout << "t6 = " << t6.display_str(3) << "\n";
} 
int main(int argc, char *argv[] )
{
  tt_assign_add();

  return 0;
}
