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
#include "Texture.hpp"
class XMLTextureLoader : public XMLLoader{

public:
	void load(){
		if (xmlDocument.empty()) {
			printf("ERROR load a xml file first\n");
			return;
		}
		
		pugi::xml_node textureNode;
		textureNode = xmlDocument.child("texture");
		while (!textureNode.empty()){
			Texture *t = new Texture();
			/* Search for image path */
			if (!textureNode.attribute("path").empty()){
				int r,c;
				
				//Load number of rows
				if (textureNode.attribute("rows").empty()) {
					r = 1;
				} else {
					r = textureNode.attribute("rows").as_int();
				}
				//Get number of columns
				if (textureNode.attribute("columns").empty()) {
					c = 1;
				} else {
					c = textureNode.attribute("columns").as_int();
				}
				//Get path
				string image = textureNode.attribute("path").as_string();
				
				//Load image on Texture
				t->loadImage(image, r, c);
			}
			
			/* Search for name */
			if (!textureNode.attribute("name").empty()){
				t->name = textureNode.attribute("name").as_string();
			} else {
				t->name = "";
			}
			textureNode = textureNode.next_sibling("texture");
		}
	}
};

#endif /* XMLTextureLoader_hpp */
