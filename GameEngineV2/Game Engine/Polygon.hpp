//
//  Polygon.hpp
//  GameEngineV2
//
//  Created by Carlos Spaggiari Roa on 11/25/15.
//  Copyright © 2015 ARSC. All rights reserved.
//

#ifndef Polygon_hpp
#define Polygon_hpp

#include "Texture.hpp"
#include <math.h>
class Polygon : public Texture{
protected:
	std::vector<SDL_Point> vertexs;
	bool builded;
	
	void createPolygon(int w, int h){
		
		srcRect.w = w;
		srcRect.h = h;
		texture = Renderer::createTexture(SDL_PIXELFORMAT_ABGR8888,
										  SDL_TEXTUREACCESS_TARGET,
										  srcRect.w,
										  srcRect.h);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		if (!texture){
			fprintf(stderr
					,"ERROR creating Polygon's texture\ntexture: %p\nid: %d\n%s\n"
					,texture
					,_id
					,SDL_GetError()
					);
			exit(EXIT_FAILURE);
		}
	}
	
public:
	Color color;
	Polygon(){
		
	}

	void buildPolygon()
	{
		createPolygon(srcRect.w, srcRect.h);
		Renderer::setRendererTarget(texture);
		Renderer::clearRender();
		Renderer::setRenderColor(color);
		if(vertexs.size() == 0) return;
		if(vertexs.size() == 1) {
			Renderer::drawPoint(vertexs[0]);
		}
		else {
			
			Renderer::drawLines(&vertexs[0], (int)vertexs.size());
		}
		Renderer::setRenderColor(Color(0, 0, 0, 0));
		Renderer::setRendererTarget(NULL);
	}
	virtual inline void addVertex(SDL_Point point){
		if (point.x < 0) point.x = 0;
		else if (point.x > srcRect.w) srcRect.w = point.x+1;
		
		if (point.y < 0) point.y = 0;
		else if (point.y > srcRect.h) srcRect.h = point.y+1;
		builded = false;
		vertexs.push_back(point);
	}
	inline void addVertex(Tuple<int> point){
		SDL_Point p;
		p.x = point.x;
		p.y = point.y;
		addVertex(p);
	}
	inline void addVertex(int x, int y){
		SDL_Point p;
		p.x = x;
		p.y = y;
		addVertex(p);
	}
	
	virtual void renderTexture(Tuple<float> position){
		if (!builded){
			buildPolygon();
			builded = true;
		}
		Texture::renderTexture(position, &srcRect);
		
	}

};

class Poligonito : public Polygon {
	int r = 50;
	int c = 50;
	int s = 100;

public:

	Poligonito(){
		SDL_Point p;
		vertexs.push_back(p);
		srcRect.w = s;
		srcRect.h = s;
	}
	inline void addVertex(){

		SDL_Point p;
		vertexs.push_back(p);
		builded = false;
		double h = 2*3.14159265/(vertexs.size()-1);
		int j = 0;
		for (int i = 0; i < vertexs.size()-1 ; i++){
			double n = h*j;
			j += (vertexs.size()/2 + 1) % vertexs.size();
			vertexs[i].x = r*cos(n) + c;
			vertexs[i].y = r*sin(n) + c;
		}
		vertexs[vertexs.size()-1].x = r+c;
		vertexs[vertexs.size()-1].y = c;
	}
	
	inline void removeVertex(){
		if (vertexs.size() < 4) return;
		vertexs.erase(vertexs.begin());
		builded = false;
		int j = 0;
		double h = 2*3.14159265/(vertexs.size()-1);
		
		for (int i = 0; i < vertexs.size()-1 ; i++){
			double n = h*j;
			j += (vertexs.size()/2 + 1) % vertexs.size();
			vertexs[i].x = r*cos(n) + c;
			vertexs[i].y = r*sin(n) + c;
		}
		vertexs[vertexs.size()-1].x = r+c;
		vertexs[vertexs.size()-1].y = c;
	}
	
	
};

#endif /* Polygon_hpp */
