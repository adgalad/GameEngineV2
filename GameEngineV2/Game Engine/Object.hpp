//
//  Object.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/20/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "PhysicObject.hpp"
#include "Transform.hpp"


using namespace std;


class Object : public ListObject{
	static int	__id;
	
public:
	vector<std::string> script_paths_;
	Object *parent_;
	vector<Object*> childs_;
	Transform transform_;
	Texture *texture_;
	
	Object(){
		_id = __id++;
		script_paths_.clear();
	}

	virtual inline void loop(){

	}
		

	virtual void print(){
		printf("Object {\n\tid: %d\n\tname: %s\n\ttexture: %s\n\tx: %f  y: %f\n",
			   _id,name_.c_str(),
			   texture_->name_.c_str(),
			   transform_.position_.x,transform_.position_.y);
		for (int i = 0 ; i < script_paths_.size(); i++) {
			printf("\tscript: %s\n",script_paths_[i].c_str());
		}
		printf("  }\n\n");
	}
	
	void set_texture(Texture *texture){
		texture_ = texture;
	}
	

};

#endif /* Object_hpp */
