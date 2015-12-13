//
//  XMLLoader.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/30/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef XMLLoader_hpp
#define XMLLoader_hpp

#include "pugixml.hpp"

using namespace std;
class XMLLoader {
protected:
	pugi::xml_document xmlDocument;
	
	
public:
	
	pugi::xml_node node;
	
	XMLLoader(){};
	virtual ~XMLLoader(){
		
	};
	

	bool openXMLFile(string file){
		if (!xmlDocument.load_file(file.c_str())) {
			fprintf(stderr,"ERROR Couldn't load the xml file \nfile: %s\n",file.c_str());
			return false;
		}
		return true;
	}
	
	virtual void load(){}
};

#endif /* XMLLoader_hpp */
