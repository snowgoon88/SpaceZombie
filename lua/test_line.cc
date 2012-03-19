// -*- coding: utf-8 -*-
/**
 * Lit une ligne et l'interprète en Lua
 * g++ -o test_line test_line.cc -I/opt/local/include -L/opt/local/lib -llua
 */

#include "lua.hpp"
#include <string>
#include <iostream>
int main( int argc, char **argv )
{

  lua_State * state;
  // on créer un contexte d'exécution de Lua
  state = lua_open();
  // on charge les bibliothèques standards de Lua
  luaL_openlibs(state);

  // boucle lecture
  std::string _line = "";
  while( _line != "quit" ) {
    std::cout << "lua> ";
    //std::cin >> _line;
    getline( std::cin, _line );
    std::cout << "(read -" << _line << "-)\n";
    
    // on interprète la ligne en Lua
    //if (luaL_dofile(state,"script.lua")!=0) // interprete file
    if (luaL_dostring( state, _line.c_str() ) != 0)
      {
	// il y a eu une erreur dans le script
	fprintf(stderr,"%s\n",lua_tostring(state,-1));
	exit(1);
      }
  }
    exit(0);
}
