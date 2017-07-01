//
//  GLRenderer.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/18/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef GLRenderer_hpp
#define GLRenderer_hpp

#include "GE_SDL.hpp"
#include "Color.hpp"
#include "Window.hpp"

namespace engine{
  
  class Shader {
    friend class ShaderProgram;
    
    
    GLuint id;            /** The id of the sahder **/
    vector<string> files; /** List of shader source files **/
    GLenum type;          /** Type of Shader **/
    
  public:
    
    Shader(GLenum type){
      this->type = type;
      id = glCreateShader(type);
    }
    
    Shader(vector<string> files, GLenum type){
      this->type = type;
      this->files = files;
      id = glCreateShader(type);
    }
    
    void Init(){
      vector<char*> sources;
      vector<int> sizes;
      
      for (int i = 0 ; i < files.size() ; ++i){
        string srcString = readFile(files[i]);
        char *src = const_cast<char*>(srcString.c_str());
        sources.push_back(src);
        sizes.push_back((int)srcString.length());
      }

      glShaderSource(id, (int)files.size(), (char**)&sources[0], &sizes[0]);
      glCompileShader(id);
      
      // Ask OpenGL if the shaders was compiled
      int wasCompiled = 0;
      glGetShaderiv(id, GL_COMPILE_STATUS, &wasCompiled);
      PrintShaderCompilationErrorInfo(id);
      
      // Exit if compilation failed
      if (not wasCompiled)
        exit(EXIT_FAILURE);
    }
    
    
    void PrintShaderCompilationErrorInfo(int32_t shaderId)
    {
      // Find length of shader info log
      int maxLength;
      glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
      
      // Get shader info log
      char* shaderInfoLog = new char[maxLength];
      glGetShaderInfoLog(shaderId, maxLength, &maxLength, shaderInfoLog );
      
      std::string log = shaderInfoLog;
      
      if (log.length())
      {
        cout << "=======================================\n";
        cout <<  shaderInfoLog << std::endl;
        cout << "=======================================\n\n";
      }
      free(shaderInfoLog);
    }

    
  };


  class ShaderProgram{
  
    
    GLuint id;                /** The Shader Program id **/
    vector<Shader*> shaders;  /** List of Shaders **/
    string name;
    
  public:
    ShaderProgram(string name){
      id = glCreateProgram();
      this->name = name;
    };
    
    void addShader(Shader *shader){
      shaders.push_back(shader);
    }
    
    void Init(){
      for (int i = 0 ; i < shaders.size() ; ++i){
        shaders[i]->Init();
        glAttachShader(id, shaders[i]->id);
      }
      glLinkProgram(id);
      
      
      // Verify that the linking succeeded
      int isLinked;
      glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
      
      if (isLinked == false){
        PrintShaderLinkingError(id);
        exit(EXIT_FAILURE);
      }
    }
    
    void PrintShaderLinkingError(int32_t shaderId)
    {
      std::cout << "=======================================\n";
      std::cout << "Shader linking failed : " << std::endl;
      
      // Find length of shader info log
      int maxLength;
      glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
      
      std::cout << "Info Length : " << maxLength << std::endl;
      
      // Get shader info log
      char* shaderProgramInfoLog = new char[maxLength];
      glGetProgramInfoLog(id, maxLength, &maxLength, shaderProgramInfoLog);
      
      std::cout << "Linker error message : " << shaderProgramInfoLog << std::endl;
      
      // Handle the error by printing it to the console
      free(shaderProgramInfoLog);
      return;
    }
  
    void UseProgram()
    {
      // Load the shader into the rendering pipeline
      glUseProgram(id);
    }
    
  };
  
  

class GLRenderer {
  Vector4 _glColor;
  Color   _renderColor;
  vector<ShaderProgram*> programs;
  Window *mainWindow;
  SDL_GLContext context;
  
public:

  ~GLRenderer(){
    SDL_GL_DeleteContext(context);
  }
  
  GLRenderer(Window* window){
    mainWindow = window;
    SDL_GL_CreateContext(mainWindow->sdl_window);
    
    // OpenGL Version 3.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    // Enable Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // This means that the old, deprecated code are disabled, only the newer versions can be used.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif
  }
  
  void setDrawColor(Color color) {
    _renderColor = color;
    _glColor = color.GL_Color();

  }
  Color getDrawColor(){
    return _renderColor;
  };
  
  void clearRender() {
    glClearColor(_glColor.x, _glColor.y, _glColor.z, _glColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
  }
  
  void renderPresent(){
    SDL_GL_SwapWindow(mainWindow->sdl_window);
  }
  
  void Init(){
    for (int i = 0 ; i < programs.size() ; ++i){
      programs[i]->Init();
    }
  }
};



}

#endif /* GLRenderer_hpp */
