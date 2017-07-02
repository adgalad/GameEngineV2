//
//  GE_SDL.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef GE_SDL_hpp
#define GE_SDL_hpp

#ifdef __cplusplus

#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#ifdef ENGINE2D /* Only if compiling the 2D GameEngine */
#include <SDL2_image/SDL_image.h>
#endif


/* OpenGL */
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>


/* C++ Standard Libs */
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>


#include "Debug.hpp"

#define foreach(i, c) for (i = c.begin(); i != c.end(); ++i)

//#define ENABLE_BOOST_SERIALIZATION_XML
#ifdef ENABLE_BOOST_SERIALIZATION


  #include <boost/serialization/assume_abstract.hpp>
  #include <boost/serialization/utility.hpp>

  #include <boost/serialization/version.hpp>
  #include <boost/serialization/export.hpp>
  #include <boost/archive/tmpdir.hpp>

  /* STD Lib */
  #include <boost/serialization/vector.hpp>
  #include <boost/serialization/map.hpp>
  #include <boost/serialization/shared_ptr.hpp>

  #define SPLIT_SERIALIZATION BOOST_SERIALIZATION_SPLIT_MEMBER()
  #define SERIALIZE friend class boost::serialization::access;



  /* Enable xml serializations of C++ classes */
  #ifdef ENABLE_BOOST_SERIALIZATION_XML
    #include <boost/serialization/nvp.hpp>
    #include <boost/archive/xml_iarchive.hpp>
    #include <boost/archive/xml_oarchive.hpp>
    #include <boost/archive/text_oarchive.hpp>
    #include <boost/archive/text_iarchive.hpp>

    #define TAG_BASE(archive, T) \
      archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(T)

    #define TAG(archive,name) archive & BOOST_SERIALIZATION_NVP(name)

    #define TAG_IA(archive, obj) archive >> BOOST_SERIALIZATION_NVP(obj)

    #define TAG_OA(archive, obj) archive << BOOST_SERIALIZATION_NVP(obj)

    #define EXPORT_IMPLEMENT(T) BOOST_CLASS_EXPORT_IMPLEMENT(T)

    #define OUT_ARCHIVE boost::archive::xml_oarchive
    #define IN_ARCHIVE boost::archive::xml_iarchive

  #else
    #include <boost/archive/binary_oarchive.hpp>
    #include <boost/archive/binary_iarchive.hpp>
//    #include <boost/archive/text_oarchive.hpp>
//    #include <boost/archive/text_iarchive.hpp>
    #define TAG_BASE(archive, T) archive & boost::serialization::base_object<T>(*this)

    #define TAG(archive,name) archive & name

    #define TAG_IA(archive, obj) archive >> obj

    #define TAG_OA(archive, obj) archive << obj

    #define EXPORT_IMPLEMENT(T) BOOST_CLASS_EXPORT_IMPLEMENT(T)

    #define OUT_ARCHIVE boost::archive::binary_oarchive
    #define IN_ARCHIVE boost::archive::binary_iarchive

  #endif

  #define EXPORT_KEY(T) \
    BOOST_CLASS_EXPORT_KEY(T)
  //  BOOST_CLASS_TRACKING(T, 2)

  #define EXPORT_ABSTRACT_KEY(T) \
    BOOST_CLASS_EXPORT_KEY(T) \
    BOOST_SERIALIZATION_ASSUME_ABSTRACT(T)
  //  BOOST_CLASS_TRACKING(T, 2)


    #include <boost/config.hpp>

#else
  #define SPLIT_SERIALIZATION
  #define SERIALIZE

#endif


typedef struct {
  bool showColliders;
} GameOptions;

extern GameOptions Options;


extern const float PI;



namespace engine {
  using namespace std;

/**
	Prints an error menssage via stderr
 */
void error(string err);

/**
	Initialize the basic SDL modules and engine utils, like the Debug,
	before lauching the game
 */
void GameEngineInit();

/**
	Quit the basic SDL modules after quiting the game
 */
void GameEngineQuit();

}


template <class _SerializeType>
void saveSerialize(std::string filename, const _SerializeType &obj){
  std::ofstream ofs(filename);
  assert(ofs.good());
  OUT_ARCHIVE oa(ofs);
  TAG_OA(oa, obj);
  ofs.close();
}


template <class _SerializeType>
void loadSerialize(std::string filename, _SerializeType &obj){
  std::ifstream ifs(filename);
  assert(ifs.good());
  IN_ARCHIVE ia(ifs);
  TAG_IA(ia,obj);
  ifs.close();
}

template <class _SerializeType>
std::ostringstream serialize(const _SerializeType &obj){
  std::ostringstream oss (std::ostringstream::binary);
  assert(oss.good());
  OUT_ARCHIVE oa(oss);
  TAG_OA(oa, obj);
  return oss;
}

template <class _SerializeType>
void deserialize(std::string s, _SerializeType obj){
  std::istringstream iss (s, std::istringstream::binary);
  assert(iss.good());
  IN_ARCHIVE ia(iss);
  TAG_IA(ia, obj);
}



#endif

engine::string readFile(engine::string file);

#endif /* GE_SDL_hpp */
