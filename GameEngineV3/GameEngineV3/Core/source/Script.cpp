//
//  Script.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 9/23/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Script.hpp"

using namespace engine;

LuaScript::LuaScript(const string& filename) {
  L = luaL_newstate();
  if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
    error("Error: failed to load (" + filename + ")");
    L = 0;
  }
  
  if(L) luaL_openlibs(L);
}

LuaScript::~LuaScript() {
  if(L) lua_close(L);
}

void LuaScript::printError(const string& variableName, const string& reason) {
  error("Error: can't get [" + variableName + "]. " + reason);
}

vector<int> LuaScript::getIntVector(const string& name) {
  vector<int> v;
  lua_gettostack(name.c_str());
  if(lua_isnil(L, -1)) { // array is not found
    return vector<int>();
  }
  lua_pushnil(L);
  while(lua_next(L, -2)) {
    v.push_back((int)lua_tonumber(L, -1));
    lua_pop(L, 1);
  }
  clean();
  return v;
}

vector<string> LuaScript::getTableKeys(const string& name) {
  string code =
  "function getKeys(name) "
  "s = \"\""
  "for k, v in pairs(_G[name]) do "
  "    s = s..k..\",\" "
  "    end "
  "return s "
  "end"; // function for getting table keys
  luaL_loadstring(L,
                  code.c_str()); // execute code
  lua_pcall(L,0,0,0);
  lua_getglobal(L, "getKeys"); // get function
  lua_pushstring(L, name.c_str());
  lua_pcall(L, 1 , 1, 0); // execute function
  string test = lua_tostring(L, -1);
  vector<string> strings;
  string temp = "";
  cout<<"TEMP:"<<test<<endl;
  for(unsigned int i = 0; i < test.size(); i++) {
    if(test.at(i) != ',') {
      temp += test.at(i);
    } else {
      strings.push_back(temp);
      temp= "";
    }
  }
  clean();
  return strings;
}
