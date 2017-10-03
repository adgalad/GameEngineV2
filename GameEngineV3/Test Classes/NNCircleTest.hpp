//
//  NNCircleTest.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/21/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef NNCircleTest_hpp
#define NNCircleTest_hpp

#include "Game.hpp"
#include "NEAT.hpp"


double circleFitness(NeuralNetwork *nn);

extern int size;

class NNCircle : public Scene {
public:
  Population p;
  Texture t;
  
  NNCircle() : Scene("Circle", Rect(0,0, size,size)){
    t.createTargetTexture("a", Rect(0,0,size,size));
    p = Population(5, 2, 1);
    p.setupParameters( 0.3    // Min distance for compatibility
                       , 1     // c1
                       , 1     // c2
                       , 0.4   // c3
                       , 1 // Max Fitness
                       , 30    // Weight Mutation Probability over 100
                       , 30    // Connection Mutation Probability over 100
                       , 30    // New Neuron Mutation Probability over 100
                       );
    p.fitness = circleFitness;
  }
  

  void draw(NeuralNetwork *nn){
    double f = 0;
//    t.setAsRenderTarget();
    for (int i = 0 ; i < size ; ++i){
      for (int j = 0 ; j < size ; ++j){
        
        nn->evaluate({(double)i,(double)j});
        double value = nn->output[0]->value;
//        cout << "value: " << value << endl;
//        double value  = fRand(0, 1);
        bool inside = value > 0.5;
        
        if (pow(i-size/2,2) + pow(j-size/2,2) <= pow(size/4,2)){
          if (inside){
            Application.renderer()->setDrawColor(Color::red);
            Texture::drawPoint(Vector2(i,j));
            
          } else {
            Application.renderer()->setDrawColor(Color::yellow);
            Texture::drawPoint(Vector2(i,j));
          }
          f += pow(value-1,2);
        } else {
          if (not inside){
            Application.renderer()->setDrawColor(Color::blue);
            Texture::drawPoint(Vector2(i,j));
          } else {
            Application.renderer()->setDrawColor(Color::yellow);
            Texture::drawPoint(Vector2(i,j));
          }
          f += pow(value,2);
        }
      }
    }
    SDL_Delay(10);
//    Application.setSceneAsRenderTarget();
    nn->fitness = f / size*size;
  }
  
  
  int i = 0, j = 0;
  
  void Update(){
    
    p.species[i][j]->mutate();
    draw(p.species[i][j]);
    j++;
    if (j == p.species[i].size() ){
      j=0;
      i++;
      if (i == p.species.size()){
        p._calculateFitness();
        p.crossOver();
        p.generation++;
        i = 0;
        cout << p.info();
      }
    }
    
//    draw();
    
//    t.Render(Vector2(0,0),Vector2(4,4));
    
  }
  
  
};




#endif /* NNCircleTest_hpp */
