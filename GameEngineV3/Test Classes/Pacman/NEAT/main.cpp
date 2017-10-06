//
//  main.cpp
//  NEAT
//
//  Created by Carlos Spaggiari Roa on 4/23/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include <iostream>
#include "NEAT.hpp"

#define debug(x) printf("%s = %d\n",#x,x)
#define debugf(x) printf("%s = %f\n",#x,x)

Population *p = NULL;

double xorFitness(NeuralNetwork *nn){
  double fitness = 4;
  double a,b,c,d;
  nn->evaluate({0,0});
  a = nn->output[0]->value;
  fitness -= a;
  
  
  nn->evaluate({1,0});
  b = nn->output[0]->value;
  fitness -= 1-b;
  
  nn->evaluate({0,1});
  c = nn->output[0]->value;
  fitness -= 1-c;
  
  nn->evaluate({1,1});
  d = nn->output[0]->value;
  fitness -= d;
  
  if (nn->output[0]->nImpulses > 0 && nn->output[0]->nImpulses != nn->output[0]->inputs){
    nn->showInfo();
    int j; j++;
  }

  fitness += -sigmoid(nn->hidden.size())+1;
  fitness /= 4.5;
//  printf("%f     (%f, %f, %f, %f)\n", fitness, a,b,c,d);
  
  if (a < 0.5 && b > 0.5 && c > 0.5 && d < 0.5 ){
//    nn->showInfo();
//    savePopulation("/Users/carlosspaggiari/pop.xml", p);
    cout << "Woho!";
  }
  
  return fitness;
}

int main(int argc, const char * argv[]) {
  p = new Population(4, 2, 1);
  NeuralNetwork::threshold = 0.5;
  p->setupParameters( 0.3   // Min distance for compatibility
                     , 1    // c1
                     , 1    // c2
                     , 0.5  // c3
                     , 1.5  // Max Fitness
                     , 40   // Weight Mutation Probability over 100
                     , 20   // Connection Mutation Probability over 100
                     , 30   // New Neuron Mutation Probability over 100
                     );
  p->fitness = xorFitness;
  savePopulation("/Users/carlosspaggiari/pop.b", p);

  
  p = loadPopulation("/Users/carlosspaggiari/pop.b");
  NeuralNetwork::threshold = 0.5;
  p->fitness = xorFitness;
  
  
  
  int generations = 0;
  
  while (1){
    generations++;
    debug(generations);
    p->train();
    cout << "------------------\n";

    debugf(gBestFitness);
  }
  
  
  return 0;
}
