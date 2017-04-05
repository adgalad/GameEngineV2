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
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "Debug.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>


#define ENABLE_BOOST_SERIALIZATION
#define ENABLE_BOOST_XML_SERIALIZATION
#ifdef ENABLE_BOOST_SERIALIZATION

  #include <boost/serialization/nvp.hpp>
  #include <boost/archive/binary_oarchive.hpp>
  #include <boost/archive/binary_iarchive.hpp>
  #include <boost/archive/text_oarchive.hpp>
  #include <boost/archive/text_iarchive.hpp>
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
//  #ifdef ENABLE_BOOST_SERIALIZATION_XML

    #define TAG_BASE(archive, T) \
      archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(T)

    #define TAG(archive,name) archive & BOOST_SERIALIZATION_NVP(name)

    #define TAG_IA(archive, obj) archive >> BOOST_SERIALIZATION_NVP(obj)

    #define TAG_OA(archive, obj) archive << BOOST_SERIALIZATION_NVP(obj)

    #define EXPORT_IMPLEMENT(T) BOOST_CLASS_EXPORT_IMPLEMENT(T)


#define EXPORT_KEY(T) \
  BOOST_CLASS_EXPORT_KEY(T) \
//  BOOST_CLASS_TRACKING(T, 2)

#define EXPORT_ABSTRACT_KEY(T) \
  BOOST_CLASS_EXPORT_KEY(T) \
  BOOST_SERIALIZATION_ASSUME_ABSTRACT(T) \
//  BOOST_CLASS_TRACKING(T, 2)


  #include <boost/config.hpp>
  #include <boost/archive/xml_iarchive.hpp>
  #include <boost/archive/xml_oarchive.hpp>

#endif

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
#endif

#endif /* GE_SDL_hpp */
