//
//  XMLPlayerLoader.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/1/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef XMLPlayerLoader_hpp
#define XMLPlayerLoader_hpp

#include "XMLEntityLoader.hpp"
#include "Player.hpp"
class XMLPlayerLoader : public XMLEntityLoader {
	
	void loadPlayer(Player *p){
		loadEntity(p);
	}
public:
	void load(List *players){
		if (xmlDocument.empty()) {
			printf("ERROR load a xml file first\n");
			return;
		}
		node = xmlDocument.child("player");
		while (node.empty() == false){
			Player *p = new Player();
			loadPlayer(p);
			
			players->pushBack(p);
			node = node.next_sibling("player");
		}
		
	}
};
#endif /* XMLPlayerLoader_hpp */
