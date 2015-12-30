//
//  XMLTextureLoader.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/30/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef XMLTextureLoader_hpp
#define XMLTextureLoader_hpp

#include "XMLLoader.hpp"
#include "Sprite.hpp"
class XMLTextureLoader : public XMLLoader{

public:
	virtual bool openXMLFile(std::string file){
		if (not XMLLoader::openXMLFile(file)) return false;
		node = xmlDocument.child("texture");
		return true;
	}
	
	void load(){
		if (node.empty()) {
			printf("ERROR load a xml node first\n");
			return;
		}
		while (!node.empty()){
			Sprite *t = Sprite::createSprite(node.attribute("name").as_string());
			/* Search for image path */
			if (!node.attribute("path").empty()){
				int r,c;
				
				//Load number of rows
				if (node.attribute("rows").empty()) {
					r = 1;
				} else {
					r = node.attribute("rows").as_int();
				}
				//Get number of columns
				if (node.attribute("columns").empty()) {
					c = 1;
				} else {
					c = node.attribute("columns").as_int();
				}
				//Get path
				string image = node.attribute("path").as_string();
				
				//Load image on Texture
				t->loadImage(image, r, c);
			}
			
			/* Search for name */



			node = node.next_sibling("texture");
		}
	}
};



#endif /* XMLTextureLoader_hpp */
