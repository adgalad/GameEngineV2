//
//  XMLSceneLoader.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/1/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef XMLSceneLoader_hpp
#define XMLSceneLoader_hpp

#include "XMLPlayerLoader.hpp"
#include "Scene.hpp"
class XMLSceneLoader : public XMLLoader {
	
public:
	void load(Scene *scene){
		pugi::xml_node node = xmlDocument.child("scene");
		
		if (!node.attribute("texture").empty()){
			scene->loadTextureByName(node.attribute("texture").as_string());
		}

		XMLEntityLoader entityLoader;
		XMLPlayerLoader playerLoader;
		
		entityLoader.node = node;
		entityLoader.load(&scene->entities);
		playerLoader.node = node;
		playerLoader.load(&scene->players);
		
		pugi::xml_node auxiliarNode = node.child("entityXML");
		while(auxiliarNode.empty() == false){
		
			entityLoader.openXMLFile(auxiliarNode.attribute("path").as_string());
			entityLoader.load(&scene->entities);
			auxiliarNode = auxiliarNode.next_sibling("entityXML");
		}
		auxiliarNode = node.child("playerXML");
		while(auxiliarNode.empty() == false){
			playerLoader.openXMLFile(auxiliarNode.attribute("path").as_string());
			playerLoader.load(&scene->players);
			auxiliarNode = auxiliarNode.next_sibling("playerXML");
		}
	}
};

#endif /* XMLSceneLoader_hpp */
