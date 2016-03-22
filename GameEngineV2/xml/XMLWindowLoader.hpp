//
//  XMLWindowLoader.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 12/26/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef XMLWindowLoader_hpp
#define XMLWindowLoader_hpp

#include "XMLSceneLoader.hpp"
#include "Window.hpp"

class XMLWindowLoader : public XMLLoader{
	
//public:
//
//	virtual bool openXMLFile(std::string file){
//		if (not XMLLoader::openXMLFile(file)) return false;
//		node = xmlDocument.child("Window");
//		return true;
//	}
//	
//
//	void load(Window *window){
//		int w, h, flags;
//		
//		if (not node.attribute("width").empty()){
//			w = node.attribute("width").as_int();
//		}
//		if (not node.attribute("height").empty()){
//			h = node.attribute("height").as_int();
//		}
//		if (not node.attribute("resizable").empty() and
//			    node.attribute("resizable").as_bool())
//		{
//			flags |= SDL_WINDOW_RESIZABLE;
//		}
//		if (not node.attribute("fullscreen").empty() and
//			node.attribute("fullscreen").as_bool())
//		{
//			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
//			#ifdef __APPLE__
//			flags &= ~SDL_WINDOW_FULLSCREEN;
//			#endif
//		}
//		#ifdef __APPLE__
//		if (not node.attribute("windowedFullscreen").empty() and
//			node.attribute("windowedFullscreen").as_bool())
//		{
//			flags |= SDL_WINDOW_FULLSCREEN;
//			flags &= ~SDL_WINDOW_FULLSCREEN_DESKTOP;
//		}
//		#endif
//		
//		window = new Window(w,h,flags);
//		
//		node = node.child("subwidget");
//		while(not node.empty()) {
//			
//			pugi::xml_node widgetsNode = node.first_child();
//			while (not widgetsNode.empty()) {
//				string name = widgetsNode.name();
//				if (name == "scene"){
//					XMLSceneLoader sl;
//					Scene *scene = NULL;
//					sl.node = widgetsNode;
//					sl.load(scene);
//					
//				}
//				else {
//					
//				}
//			}
//		}
//		
//	}
};
#endif /* XMLWindowLoader_hpp */
