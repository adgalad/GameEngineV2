//
//  GameEngineObject.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/18/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef GameEngineObject_hpp
#define GameEngineObject_hpp

#include <vector>
#include <string>

using namespace std;

class Script{
	
};

class GameEngineObject {
	
public:
	
	GameEngineObject();
	
	~GameEngineObject();
	
	void add_script(Script *);
	
	void remove_script(Script *);
	
	void CallUpdate();
	


protected:
	virtual void Start();
	
	virtual void Update();
	
	virtual void FixedUpdate();
	
	virtual void Finish();
	
private:
	
	vector<Script*> scripts;
	

	
	void loop();
	
	void render();
	
};

#endif /* GameEngineObject_hpp */
