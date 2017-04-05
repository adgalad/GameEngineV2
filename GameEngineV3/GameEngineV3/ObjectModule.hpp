//
//  ObjectModule.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/22/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef ObjectModule_hpp
#define ObjectModule_hpp


#ifdef __cplusplus
#include "Object.hpp"


namespace engine {

template<class Scene>
class ObjectModuleT{
  
	SERIALIZE
  
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const
  {
    // note, version is always the latest when saving
    TAG(ar, name);
//    TAG(ar, object);
  }
  
  template<class Archive>
  void load(Archive & ar, const unsigned int version)
  {
    TAG(ar, name);
//    TAG(ar, object);
  }
  SPLIT_SERIALIZATION
  
protected:
	string name;
	
	ObjectT<Scene,ObjectModuleT> *object = NULL;
	
	ObjectModuleT(){};
public:
		
	virtual ~ObjectModuleT();
	
	string getName();
  
  virtual void Init() { Start(); }
	
	virtual void setName(string name);
	
	virtual void setObject(ObjectT<Scene,ObjectModuleT> *obj);
	
	virtual void Start() = 0;
	
	virtual void Update() = 0;
		
};
  
  typedef ObjectModuleT<Scene>  ObjectModule;
}



EXPORT_ABSTRACT_KEY(ObjectModule);


#endif

#endif /* ObjectModule_hpp */
