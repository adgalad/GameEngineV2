//
//  NNCircleTest.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 5/21/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "NNCircleTest.hpp"

int size = 200;

double circleFitness(NeuralNetwork *nn){
  double f = 0;
  
  for (int i = 0 ; i < size ; ++i){
    for (int j = 0 ; j < size ; ++j){
      nn->evaluate({(double)i,(double)j});
      double value = nn->output[0]->value;
    
      
      if (pow(i-size/2,2) + pow(j-size/2,2) <= pow(size/4,2)){
        f += pow(value-1,2);
      } else {
        f += pow(value,2);
      }
    }
  }
  f /= size*size;
  cout << "Error: " << f << ", Fitness: " << 1.0 - f << endl;
  return 1.0-f;
}
