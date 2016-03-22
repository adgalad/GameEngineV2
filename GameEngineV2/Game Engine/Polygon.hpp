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
//class Polygon : public Texture{
//protected:
//	std::vector<SDL_Point> vertexs;
//	bool builded;
//	
//	void createPolygon(int w, int h){
//		
//		srcRect_.w = w;
//		srcRect_.h = h;
//		texture_ = renderer_->create_texture(SDL_PIXELFORMAT_ABGR8888,
//										  SDL_TEXTUREACCESS_TARGET,
//										  srcRect_.w,
//										  srcRect_.h);
//		SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
//		if (!texture_){
//			fprintf(stderr
//					,"ERROR creating Polygon's texture\ntexture: %p\nid: %d\n%s\n"
//					,texture_
//					,_id
//					,SDL_GetError()
//					);
//			exit(EXIT_FAILURE);
//		}
//	}
//	
//public:
//	Color color;
//	Polygon(){
//		
//	}
//
//	void buildPolygon()
//	{
//		createPolygon(srcRect_.w, srcRect_.h);
//		renderer_->set_renderer_target(texture_);
//		renderer_->clear_render();
//		renderer_->set_render_color(color);
//		if(vertexs.size() == 0) return;
//		if(vertexs.size() == 1) {
//			renderer_->draw_point(vertexs[0]);
//		}
//		else {
//			
//			renderer_->draw_lines(&vertexs[0], (int)vertexs.size());
//		}
//		renderer_->set_render_color(Color(0, 0, 0, 0));
//		renderer_->set_renderer_target(NULL);
//	}
//	virtual inline void addVertex(SDL_Point point){
//		if (point.x < 0) point.x = 0;
//		else if (point.x > srcRect_.w) srcRect_.w = point.x+1;
//		
//		if (point.y < 0) point.y = 0;
//		else if (point.y > srcRect_.h) srcRect_.h = point.y+1;
//		builded = false;
//		vertexs.push_back(point);
//	}
//	inline void addVertex(Vector2D point){
//		SDL_Point p;
//		p.x = point.x;
//		p.y = point.y;
//		addVertex(p);
//	}
//	inline void addVertex(int x, int y){
//		SDL_Point p;
//		p.x = x;
//		p.y = y;
//		addVertex(p);
//	}
//	
//	virtual void renderTexture(Vector2D position){
//		if (!builded){
//			buildPolygon();
//			builded = true;
//		}
//		Texture::renderTexture(position, &srcRect_);
//		
//	}
//
//};
//
//class Poligonito : public Polygon {
//	int r = 50;
//	int c = 50;
//	int s = 100;
//
//public:
//
//	Poligonito(){
//		SDL_Point p;
//		vertexs.push_back(p);
//		srcRect_.w = s;
//		srcRect_.h = s;
//	}
//	inline void addVertex(){
//
//		SDL_Point p;
//		vertexs.push_back(p);
//		builded = false;
//		double h = 2*3.14159265/(vertexs.size()-1);
//		int j = 0;
//		for (int i = 0; i < vertexs.size()-1 ; i++){
//			double n = h*j;
//			j += (vertexs.size()/2 + 1) % vertexs.size();
//			vertexs[i].x = r*cos(n) + c;
//			vertexs[i].y = r*sin(n) + c;
//		}
//		vertexs[vertexs.size()-1].x = r+c;
//		vertexs[vertexs.size()-1].y = c;
//	}
//	
//	inline void removeVertex(){
//		if (vertexs.size() < 4) return;
//		vertexs.erase(vertexs.begin());
//		builded = false;
//		int j = 0;
//		double h = 2*3.14159265/(vertexs.size()-1);
//		
//		for (int i = 0; i < vertexs.size()-1 ; i++){
//			double n = h*j;
//			j += (vertexs.size()/2 + 1) % vertexs.size();
//			vertexs[i].x = r*cos(n) + c;
//			vertexs[i].y = r*sin(n) + c;
//		}
//		vertexs[vertexs.size()-1].x = r+c;
//		vertexs[vertexs.size()-1].y = c;
//	}
//	
//	
//};

#endif /* Polygon_hpp */
