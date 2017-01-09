//
//  Script.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 9/23/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Script_hpp
#define Script_hpp

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "Debug.hpp"
#include "GE_SDL.hpp"

extern "C" {
  #include "lua/lua.h"
  #include "lua/lauxlib.h"
  #include "lua/lualib.h"
}


using namespace std;
namespace engine {

class LuaScript {
  SERIALIZE
  template<class Archive>
  void load(Archive & ar, const unsigned int version)
  {
    TAG(ar, filename);
    TAG(ar, level);
    
    L = luaL_newstate();
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
      error("Error: failed to load (" + filename + ")");
      L = 0;
    }
    
    if(L) luaL_openlibs(L);
  }
  
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const
  {
    TAG(ar, filename);
    TAG(ar, level);
  }
  
  SPLIT_SERIALIZATION
  
public:
  LuaScript() {} 
  LuaScript(const string& filename);
  ~LuaScript();
  void printError(const string& variableName, const string& reason);
  vector<int> getIntVector(const string& name);
  vector<string> getTableKeys(const string& name);
  
  inline void clean() {
    int n = lua_gettop(L);
    lua_pop(L, n);
  }
  
  template<typename T>
  T get(const string& variableName) {
#ifdef GameEngineDebug
    if(!L) {
      printError(variableName, "Script is not loaded");
      return lua_getdefault<T>();
    }
#endif
    T result;
    if(lua_gettostack(variableName)) { // variable succesfully on top of stack
      result = lua_get<T>(variableName);
    } else {
      result = lua_getdefault<T>();
    }
    
    
    clean();
    return result;
  }
  
  bool lua_gettostack(const string& variableName) {
    level = 0;
    string var = "";
    for(int i = 0; i < variableName.size(); i++) {
      if(variableName.at(i) == '.') {
        if(level == 0) {
          lua_getglobal(L, var.c_str());
        } else {
          lua_getfield(L, -1, var.c_str());
        }
        
        if(lua_isnil(L, -1)) {
          printError(variableName, var + " is not defined");
          return false;
        } else {
          var = "";
          level++;
        }
      } else {
        var += variableName.at(i);
      }
    }
    
    if(level == 0) {
      lua_getglobal(L, var.c_str());
    } else {
      lua_getfield(L, -1, var.c_str());
    }
    if(lua_isnil(L, -1)) {
      printError(variableName, var + " is not defined");
      return false;
    }
    
    return true;
  }
  
  // Generic get
  template<typename T>
  T lua_get(const string& variableName) {
    return 0;
  }
  
  template<typename T>
  T lua_getdefault() {
    return 0;
  }
  
private:
  lua_State* L;
  string filename;
  int level;
};

// Specializations

template <>
inline bool LuaScript::lua_get<bool>(const string& variableName) {
  return (bool)lua_toboolean(L, -1);
}

template <>
inline float LuaScript::lua_get<float>(const string& variableName) {
  if(!lua_isnumber(L, -1)) {
    printError(variableName, "Not a number");
  }
  return (float)lua_tonumber(L, -1);
}

template <>
inline int LuaScript::lua_get<int>(const string& variableName) {
  if(!lua_isnumber(L, -1)) {
    printError(variableName, "Not a number");
  }
  return (int)lua_tonumber(L, -1);
}

template <>
inline string LuaScript::lua_get<string>(const string& variableName) {
  string s = "null";
  if(lua_isstring(L, -1)) {
    s = string(lua_tostring(L, -1));
  } else {
    printError(variableName, "Not a string");
  }
  return s;
}

template<>
inline string LuaScript::lua_getdefault<string>() {
  return "null";
}

}
#endif /* Script_hpp */
