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
	
	virtual bool openXMLFile(std::string file){
		if (not XMLLoader::openXMLFile(file)) return false;
		node = xmlDocument.child("player");
		return true;
	}
	
	virtual void load(List *players){
		printf("Entro\n");
		if (node.empty()) {
			printf("ERROR (XMLPlayerLoader) load a xml node first\n");
			return;
		}
		while (node.empty() == false){
			
			Player *p = new Player();
			loadPlayer(p);
			
			players->pushBack(p);
			node = node.next_sibling("player");
		}
		
	}
};
#endif /* XMLPlayerLoader_hpp */
