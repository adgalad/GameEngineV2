//
//  ListObject.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/24/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef ListObject_hpp
#define ListObject_hpp
#include "define.h"
#include <string>

class ListObject {
	
protected:
	int _id = -1;
	
public:
	
	virtual ~ListObject(){
		#ifdef GameEngineDebug
			printf("Deleting object: %p id: %d name: '%s'\n",this,id(),name.c_str());
		#endif
	}
	std::string name = "";

	inline int id() { return _id; }

};

#endif /* ListObject_hpp */
