//
//  NEAT.hpp
//  NEAT
//
//  Created by Carlos Spaggiari Roa on 4/23/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef NEAT_hpp
#define NEAT_hpp


#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

//#ifdef GAME_ENGINE_V3
#include "GE_SDL.hpp"
//#endif

using namespace std;


extern class NeuralNetwork *gBestNN;

extern double gBestFitness;

extern int wm, cm, nm;

extern int wProb, cProb, nProb;

double fRand(double fMin, double fMax);

double sigmoid (double x);
double cosigmoid (double x);

enum NeuronType {
  kSensor = 1,
  kHidden = 2,
  kOutput = 3,
  kBias   = 4
};

enum WeightMutation {
  kSwap    = 1,
  kSwap2,
  kSign,
  kPlus,
  kPlus2,
  kPlus3,
  kRandom,
  kPercent,
  kPercent2,
  kDisableOrEnable,
  
  _WeightMutationSize
};


class Neuron;

/**********************
 * NeuronalConnection *
 **********************/

class NeuronalConnection {
  SERIALIZE
  template<class Archive> void serialize(Archive & ar, const unsigned int version);
  
  NeuronalConnection(){};
  
  bool enable = true;

public:
  unsigned long innov = 0;
  double weight = 0;
  Neuron *from = NULL, *to = NULL;
  
  NeuronalConnection (double weight, Neuron* from, Neuron * to, int innov);
  
  void setEnable(bool d);
  
  bool isEnable();
  
};


/**********
 * Neuron *
 **********/

class Neuron {
  friend class Population;
  friend class NeuralNetwork;
  
  SERIALIZE
  template<class Archive> void serialize(Archive & ar, const unsigned int version);
  NeuronType type;

  
  Neuron(){}
  
public:
  
  double value  = 1;
  int inputs    = 0;
  int nImpulses = 0;
  int id = 0;
  vector<NeuronalConnection*> connections;
  
  Neuron (NeuronType type, int id);
  
  ~Neuron();
  
  void mutate(double min, double max);
  
  void evaluate();
};



/******************
 * Neural Netowrk *
 ******************/

class NeuralNetwork {
  
  friend class Population;
  
  SERIALIZE
  template<class Archive>
  void save(Archive & ar, const unsigned int version) const;

  template<class Archive>
  void load(Archive & ar, const unsigned int version);
  SPLIT_SERIALIZATION
  
public:
  vector<Neuron*> sensor;
  vector<Neuron*> hidden;
  vector<Neuron*> output;
  Neuron *bias;
  
  bool ill = false;
  
  
  
  static int globalInnov;
  
  
  double max, min;
  
  int ttl = 10;
  
  static int neuronId;
  double fitness;
  int specie;
  
  static double threshold;
  
  vector<NeuronalConnection*> connections;
  
  NeuralNetwork(){}
  
  NeuralNetwork(int sensors, int outputs);
  
  ~NeuralNetwork();
  
  void showInfo(){
    cout << "Fitness: "<<fitness << "\n";
    
    for (int i = 0 ; i < connections.size() ; ++i){
      NeuronalConnection *c = connections[i];
      cout << to_string(c->innov) + " " + to_string(c->weight);
      printf("\t(%d -> %d) %s",c->from->id, c->to->id, (c->isEnable() ? "" : "Disable"));
      cout << "\n";
    }
    cout << "\n";
    cout << "\n";
  }
  
  void evaluate(vector<double> input);
  
  void mutate();
  
  Neuron *searchHiddenById(int id);
  
  void addConnection();
  
  void newCustonConnection(Neuron *n1, Neuron *n2, double weight, int innov, bool enable);
  
  void newConnection(Neuron *n1, Neuron *n2);
  
  void addNode();
  
  bool hasLoop();

  static void reset(){
    globalInnov = 0;
  }
  
};



/**********
 * Specie *
 **********/




template <class T>
class SpecieT : public T {
  
  SERIALIZE
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    TAG(ar, oldShrdFitness);
    TAG(ar, sharedFitness);
    TAG(ar, offsprings);
    TAG(ar, _timeout);
    TAG_BASE(ar, T);
  }
  
  
public:
  SpecieT(){};
  
  double oldShrdFitness = 0;
  double sharedFitness = 0;
  uint32_t offsprings = 0;
  int _timeout = 20;
  
  
  int timeout();
};

typedef SpecieT<vector<NeuralNetwork*>> Specie;



/**************
 * Population *
 **************/

bool compNN (NeuralNetwork *nn1, NeuralNetwork *nn2);

class Population {
  SERIALIZE
  template<class Archive> void serialize(Archive & ar, const unsigned int version);
  

  
  /* coefficients of the linear combination to calculate compatibility distance */
  double c1 = 1, c2 = 1, c3 = 1;
  /* threshold of the compatibility distance */
  double minCompatibility = 0.5;
  
  double maxFitness;

  double calculateDistance(NeuralNetwork *nn1, NeuralNetwork *nn2);
  
  NeuralNetwork *cross(NeuralNetwork *nn1, NeuralNetwork *nn2);
  
  void crossAux(NeuralNetwork *newNN, NeuronalConnection *c, int *i);
  
public:
  
  uint32_t generation = 0;
  uint32_t population = 0;
  vector<Specie> species;
  double (*fitness)(NeuralNetwork*);
  
  Population(){};
  
  Population (int initialSize, int inputs, int outputs);
  

  
  void train();
  
  void calculateFitness();
  
  void _calculateFitness();
  
  void setupParameters(double minCompatibility, double c1, double c2, double c3, double maxFitness, int wProb, int cProb, int nProb);
  
  void classify (NeuralNetwork *nn);
  
  void crossOver();
  
  string info(){
    return "Generation: " + to_string(generation) + ", BestFitness: " + to_string(gBestFitness) + ", Population: " + to_string(population) + "\n";
  }
  
};

void savePopulation(string file, Population *p);

Population *loadPopulation(string filename);

EXPORT_KEY(NeuronalConnection);
EXPORT_KEY(Neuron);
EXPORT_KEY(NeuralNetwork);
EXPORT_KEY(Population);



#endif /* NEAT_hpp */
