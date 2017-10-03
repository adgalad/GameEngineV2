//
//  DrawPrimitives.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/5/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef DrawPrimitives_hpp
#define DrawPrimitives_hpp

#include "Game.hpp"
#include <set>


void loadDraw();



class Filler {
  double   _angle    = 0;
public:
  Filler(){};
  
  Filler(Color color){
    this->color1 = color;
  }
  
  Filler (Color c1, Color c2 = Color::black, int degree = 0, Point origin = Point(0,0), int distance = 10)
  {
    this->color1   = c1;
    this->color2   = c2;
    this->gradient = true;
    this->_angle    = -tan(( (degree % 360) *PI)/180);
    this->origin   = origin;
    this->distance = distance;
  }
  
  Color color1   = Color::black;
  Color color2   = Color::black;
  bool  gradient = false;
  
  Point origin   = Point(0,0);
  int   distance = 0;
  
  
  double angle(int degrees = -1){
    if (degrees < 0) return _angle;
    return _angle = -tan(( (degrees % 360) *PI)/180);
  }
  
};

class Line {

  double m;
  double b;
  
public:
  Line(){};
  
  Line(double m, double b){
    this->m = m;
    this->b = b;
  }
  
  Line (Point p, double angle){
    this->m = angle;
    this->b = isinf(m) ? p.x : (p.y - m*p.x);
  }
  
  Line (Point p1, Point p2) {
    this->m = (p2.y - p1.y) / (p2.x - p1.x);
    this->b = isinf(m) ? p1.x : (p1.y - m*p1.x);
  }
  
  double evaluate(double x){
    return m*x + b;
  }
  
  Point interception(Line l){
    Point p;
    if (isinf(l.m)){
      if (isinf(m))
        return Point(INFINITY,INFINITY);
      else{
        p = Point(l.b, evaluate(l.b));
      }
    }
    else if (isinf(m)){
      p = Point(b, l.evaluate(b));
    }
    else {
      double x =  (l.b - b)/(m-l.m);
      
      p = Point(x, evaluate(x));
    }
    
    return p.round();
  }
  
  bool contains(Vertex p){
    return abs(p.y - evaluate(p.x)) <= Epsilon;
  }
  
  double distanceFrom(Point p){
    if (isinf(m)){
      return abs(p.x - b);
    }
    return abs( (-m)*p.x + p.y + (-b) )/sqrt(m*m+1);
  }
  
  void draw(){
    Vector2 size = Application.window()->getSize();
    Texture::drawLine(Vector2(0,evaluate(0)), Vector2(size.x,evaluate(size.x)));
  }
};

class Edge : public Line {
  friend class Polygon;
protected:
  Vertex p1, p2;
public:
  Edge(){}
  
  Edge(Vertex p1, Vertex p2) : Line(p1, p2){
    this->p1 = p1;
    this->p2 = p2;
  }
  
  

  
  bool contains(Vertex p){
    return Line::contains(p) and
           min(p1.x,p2.x) <= p.x and p.x <= max(p1.x,p2.x) and
           min(p1.y,p2.y) <= p.y and p.y <= max(p1.y,p2.y);
  }
  
  bool operator *(Edge e){
    Vertex v = this->interception(e);
    if (isinf(v.x) || isinf(v.y) || isnan(v.x) || isnan(v.y)){
      return false;
    }
    return this->contains(v) && e.contains(v);
  }
  
  void draw(){
    Texture::drawLine(p1, p2);
  }
  
};

class Polygon : public Object {
  vector<Vertex> vertices;
  vector<Edge> edges;
  
  bool closed;
  
public:
  
  Color lineColor;
  Filler filler;
  
  Polygon(string name, Rect size, Color line, Filler filler = Filler()) : Object(name){
    texture   = shared_ptr<Texture>(new Texture());
    texture->createTargetTexture(name, size);
    lineColor = line;
    this->filler    = filler;
  }
  
  
  
  void addVertex(Vertex v){
    vertices.push_back(v);
  }
  
  void addVertexAndDraw(Vertex v){
    vertices.push_back(v);
    refreshPolygon();
  }
  
  void refreshPolygon(){
    Application.renderer()->clearRender();
    texture->setAsRenderTarget();
    Application.renderer()->clearTarget();
    Color oldColor = Application.renderer()->getDrawColor();
    
    edges.resize(vertices.size());
    for (int i = 0 ; i < vertices.size()-1; ++i){
      edges[i] = Edge(vertices[i], vertices[i+1]);
    }
    edges[vertices.size()-1] = Edge(vertices[vertices.size()-1], vertices[0]);
    
    fillPolygon();
    
    Application.renderer()->setDrawColor(lineColor);
    for (int i = 0 ; i < edges.size(); ++i){
      edges[i].draw();
    }
    
    Application.renderer()->setDrawColor(oldColor);
    Application.setSceneAsRenderTarget();
    
  }
  
  void fillPolygon(){
    int maxX = -2555555;
    int maxY = -2555555;
    int minX =  2555555;
    int minY =  2555555;
    Application.renderer()->setDrawColor(filler.color1);
    for (int i = 0 ; i < vertices.size() ; ++i){
      if (vertices[i].x > maxX) maxX = vertices[i].x;
      if (vertices[i].x < minX) minX = vertices[i].x;
      
      if (vertices[i].y > maxY) maxY = vertices[i].y;
      if (vertices[i].y < minY) minY = vertices[i].y;
    }
//    double m = tan((filler.degree * PI)/180);
//    double b = minY - m*minX;
//    vector<int> interceptedEdges;
    
    Line gradient = Line(filler.origin, filler.angle());
    
    Vertex start = Vertex(minX-1, minY-1);
    
    int dr = filler.color2.r - filler.color1.r;
    int dg = filler.color2.g - filler.color1.g;
    int db = filler.color2.b - filler.color1.b;
    
    Texture::drawPoint(start);
    Edge e;
    
    double m_edge, m_point;
    Point p;
    for (int i = minX+1 ; i < maxX ; ++i){
      for (int j = minY+1 ; j < maxY ; ++j){
        bool inside = false;
        
        // We start on the outside of the polygon
        for (int k = 0 ; k < edges.size() ; ++k){
          p = Vertex(i,j);
          Vertex A = edges[k].p1;
          Vertex B = edges[k].p2;
          // Make sure A is the lower point of the edge
          if (A.y > B.y){
            A = edges[k].p2;
            B = edges[k].p1;
          }
          // Make sure point is not at same height as vertex
          if (p.y == A.y or p.y == B.y){
            p.y += Epsilon;
          }
          
          if (p.y > B.y or p.y < A.y or p.x > max(A.x, B.x))
            // The horizontal ray does not intersect with the edge
            continue;
          
          if (p.x < min(A.x, B.x)){
            // The ray intersects with the edge
            inside = not inside;
            continue;
          }
          
          try{
            m_edge = (B.y - A.y) / (B.x - A.x);
          } catch(int e){
            m_edge = INFINITY;
          }
          
          try{
            m_point = (p.y - A.y) / (p.x - A.x);
          } catch(int e){
            m_point = INFINITY;
          }

          if (m_point >= m_edge){
            // The ray intersects with the edge
            inside = not inside;
            continue;
          }
        }

        if (inside){
          if (filler.gradient){
            double distance = gradient.distanceFrom(p);
            if (distance < filler.distance){
              Color nc = Color( filler.color1.r + (distance*dr)/filler.distance
                               ,filler.color1.g + (distance*dg)/filler.distance
                               ,filler.color1.b + (distance*db)/filler.distance );
              Application.renderer()->setDrawColor(nc);
            }
            else {
              Application.renderer()->setDrawColor(filler.color2);
            }
            
          }
          Texture::drawPoint(p);
        }
      }
      
    }
    Application.renderer()->setDrawColor(Color::yellow);
    gradient.draw();
    Application.renderer()->setDrawColor(Color::red);
    Texture::drawPoint(start);
  }
  
};


class DrawFigures : public Scene {
  Polygon *p;
  Filler f = Filler(Color::red, Color::blue);
  int degree = 0;
public:
//
  DrawFigures() : Scene("Drawing Figures :)", Rect(0,0, 800, 800)) {
    f.distance = 100;
    f.angle(degree);
    p = new Polygon("Object1", Rect(0,0,800,800), Color::green, f);
    addObject(p);
    
    int n = 1;
    p->addVertex(Vector2(0,0));
//    p->addVertex(Vector2(24,25)*n);
    p->addVertex(Vector2(0,50)*n);
    p->addVertex(Vector2(50,50)*n);
//    p->addVertex(Vector2(26,25)*n);
    p->addVertexAndDraw(Vector2(50,0)*n);
    
    
    
    p->setPosition(Vector2(0,0));
  }
  
  ~DrawFigures(){}
  
  void Update(){
  

    if (Input->KeyDown(KEY_Q)){
      degree = (degree + 1) % 360;
      f.angle(degree);
    }
    if (Input->KeyDown(KEY_W)){
      degree = (degree - 1) % 360;
      f.angle(degree);
    }
    
    if (Input->KeyDown(KEY_S)){
      f.distance++;
    }
    if (Input->KeyDown(KEY_A)){
      f.distance--;
    }
    
    if (Input->KeyPressed(KEY_Z)){
      p->setScale(p->transform.scale + Vector2(1,1));
    }
    if (Input->KeyPressed(KEY_X)){
      p->setScale(p->transform.scale - Vector2(1,1));
    }
    
    f.origin += Input->GetAxis();
    
    p->filler = f;
    p->refreshPolygon();
    
    Application.renderer()->setDrawColor(Color::black);
    Application.setSceneAsRenderTarget();
  }
};


#endif /* DrawPrimitives_hpp */
