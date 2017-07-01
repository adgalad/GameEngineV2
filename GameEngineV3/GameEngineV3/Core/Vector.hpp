//
//  Vector.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp


#ifdef __cplusplus
#include "GE_SDL.hpp"

#define Epsilon 0.00001



namespace engine {


  class Point2 {
  public:
    double x = 0;
    double y = 0;
  };

  class Vector2 : public Point2 {
    SERIALIZE
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      TAG(ar,x);
      TAG(ar,y);
    }

    public:

    Vector2();

    Vector2(double, double);

    Vector2(SDL_Point);

    inline SDL_Point toSDLPoint() const { return {(int)std::round(x), (int)std::round(y)}; }
    #define to_Point toSDLPoint
    inline Vector2 operator = (SDL_Point p) const { return Vector2(p.x,p.y); }

    Vector2 operator +(Vector2) const;

    Vector2 operator -(Vector2) const;

    Vector2 operator -() const;

    Vector2 operator *(double) const;
      
    double operator *(Vector2) const;

    Vector2 operator /(double) const;

    void operator += (Vector2);

    void operator -= (Vector2);

    void operator *= (double);

    void operator *= (Vector2);

    void operator /= (double);

    bool operator == (Vector2);

    Vector2 round();

    double length() const;

    double squareLength() const;

    Vector2 unitary() const;

    Vector2 normal() const;

    inline string toStr() const{
      return	"(" + to_string(x) + ", " + to_string(y) + ")";
    }

    Vector2 round_ceil() const{
      return Vector2(ceil(x), ceil(y));
    }

    Vector2 round_floor() const{
      return Vector2(floor(x), floor(y));
    }
  };

  typedef Vector2 Point;
  typedef Vector2 Vertex;



  class Point3 {
  public:
    double x = 0;
    double y = 0;
    double z = 0;
    
    Point3(){}
    
    Point3(double x, double y, double z);
  };

  class Vector3 : public Point3 {
  public:

    Vector3();

    Vector3(double x, double y, double z);

    inline SDL_Point toSDLPoint() { return {(int)x, (int)y}; }

    Vector3 operator +(Vector3);

    Vector3 operator -(Vector3);

    Vector3 operator -();

    Vector3 operator *(int);

    Vector3 operator *(double);

    double operator * (Vector3);

    bool operator == (Vector3);

    double length();

    Vector3 unitary();

    Vector3 normal();

    string toStr(){
      return	"(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")" ;
  }




  };

  ostream& operator<<(ostream& os, const Vector3& v);

  
  class Point4 {
  public:
    double x = 0;
    double y = 0;
    double z = 0;
    double w = 0;
    
    Point4(){}
    
    Point4(double x, double y, double z, double w);
  };
  
  
  class Vector4 : public Point4 {
  public:
    
    
    
    Vector4();
    
    Vector4(double x, double y, double z, double w);
    
    inline SDL_Point toSDLPoint() { return {(int)x, (int)y}; }
    
    void operator = (Point4 p);
    
    Vector4 operator +(Vector4);

    Vector4 operator -(Vector4);
    
    Vector4 operator -();
    
    Vector4 operator *(int);
    
    Vector4 operator *(double);
    
    double operator * (Vector4);
    
    bool operator == (Vector4);
    
    double length();
    
    Vector4 unitary();
    

    
    string toStr(){
      return	"(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")" ;
    }
    
  };
  ostream& operator<<(ostream& os, const Vector4& v);
}



#endif
#endif /* Vector_hpp */
