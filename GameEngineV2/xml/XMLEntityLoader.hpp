//
//  XMLEntityLoader.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/1/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef XMLEntityLoader_hpp
#define XMLEntityLoader_hpp

#include "XMLLoader.hpp"
#include "Entity.hpp"
class XMLEntityLoader : public XMLLoader {
protected:
	
	void loadEntity(Entity *e){

		e->name = node.attribute("name").as_string(e->name.c_str());
		e->loadTextureByName(node.attribute("texture").as_string());
		e->setPosition(Point<float>(node.attribute("X").as_float(),
									node.attribute("Y").as_float()));

		pugi::xml_node script = node.child("script");
		while (script.empty() == false){
			string path = script.attribute("path").as_string("No Script Here.");
			e->script_paths.push_back(path);
			script = script.next_sibling("script");
		}
	}
public:
	
	virtual bool openXMLFile(std::string file){
		if (not XMLLoader::openXMLFile(file)) return false;
		node = xmlDocument.child("entity");
		return true;
	}
	
	virtual void load(List *entities){
		if (node.empty()) {
			printf("ERROR (XMLEntityLoader) load a xml file first\n");
			return;
		}
		while (node.empty() == false) {
			Entity *e = new Entity();
			loadEntity(e);
			entities->pushBack(e);
			node = node.next_sibling("entity");
		}
	}
};

#endif /* XMLEntityLoader_hpp */
