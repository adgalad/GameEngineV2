//
//  NEAT.cpp
//  NEAT
//
//  Created by Carlos Spaggiari Roa on 4/23/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "NEAT.hpp"

NeuralNetwork *gBestNN = NULL;

double gBestFitness = 0;
int wm = 0, cm = 0, nm = 0;
double fRand(double fMin, double fMax)
{
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}


double sigmoid (double x) {
  return 1/(1 + exp(-x));
}



double cosigmoid(double x){
  return (-sigmoid(x)+1);
}
bool compNN (NeuralNetwork *nn1, NeuralNetwork *nn2){
  return nn1->fitness < nn2->fitness;
}

int wProb = 20;
int cProb = 20;
int nProb = 20;

/**********************
 * NeuronalConnection *
 **********************/

NeuronalConnection::NeuronalConnection (double w, Neuron* from, Neuron * to, int innov){
  this->weight = w;
  this->from   = from;
  this->to     = to;
  this->innov  = innov;
  to->inputs++;
  
  this->from->connections.push_back(this);
  enable = true;
}

void NeuronalConnection::setEnable(bool cond)
{
  if (enable != cond) {
    if (cond == false){
      to->inputs--;
    }
    else {
      to->inputs++;
    }
    enable = cond;
  }
}

bool NeuronalConnection::isEnable() { return enable; }





/**********
 * Neuron *
 **********/

Neuron::Neuron (NeuronType type, int id){
  this->type = type;
  this->id = id;
}

Neuron::~Neuron() {
  for (int i = 0 ; i < connections.size() ; ++i){
    delete connections[i];
  }
}

void Neuron::mutate(double min, double max){
  
  int opt = rand() % (_WeightMutationSize*10);
  uint64_t r = rand() % connections.size();
  if (opt < _WeightMutationSize) switch ((WeightMutation)opt) {
    case kSwap:
    case kSwap2:{
      int r1 = rand() % connections.size();
      if (r != r1){
        double aux = connections[r]->weight;
        connections[r]->weight = connections[r1]->weight;
        connections[r1]->weight = aux;
      }
      break;
    }
    case kSign:
      connections[r]->weight *= -1;
      break;
    case kPlus:
    case kPlus2:
    case kPlus3:
      connections[r]->weight += fRand(-1, 1);
      break;
    case kRandom:
      connections[r]->weight  = fRand(min, max);
      break;
    case kPercent:
    case kPercent2:
      connections[r]->weight *= fRand(0.5, 1.5);
      break;
      
    case kDisableOrEnable:
      if (connections.size() > 1){
        connections[r]->setEnable(not connections[r]->isEnable());
      }
      break;
      
    default:
      break;
  }
}

void Neuron::evaluate(){
  nImpulses = 0;
  for (int i = 0 ; i < connections.size() ; ++i){
    if (connections[i]->isEnable()){
      Neuron *n = connections[i]->to;
      n->value += this->value * connections[i]->weight;
      if (n->inputs == ++(n->nImpulses)){
        n->evaluate();
      }
    }
  }
  if (type == kOutput){
    value = sigmoid(value);
  }
  
}




/******************
 * Neural Netowrk *
 ******************/

int NeuralNetwork::globalInnov = 0;
int NeuralNetwork::neuronId    = 0;
double NeuralNetwork::threshold   = 0;

NeuralNetwork::NeuralNetwork(int sensors, int outputs){
  max = (sqrt(2.0 / (double)sensors));
  min = -max;
  int innov = 0;
  neuronId = 0;
  bias = new Neuron(kBias, neuronId++);
  
  for (int i = 0 ; i < sensors ; ++i){
    sensor.push_back(new Neuron(kSensor, neuronId++));
  }
  
  for (int i = 0 ; i < outputs ; ++i){
    Neuron *n = new Neuron(kOutput, neuronId++);
    output.push_back(n);
  }
  
  
  for (int j = 0 ; j < outputs ; ++j){
    double r = fRand(min, max);
    connections.push_back(new NeuronalConnection(r, bias, output[j], innov++));
  }
  
  for (int i = 0 ; i < sensors ; ++i){
    for (int j = 0 ; j < outputs ; ++j){
      double r = fRand(min, max);
      connections.push_back(new NeuronalConnection(r, sensor[i], output[j], innov++));
    }
  }
  
  globalInnov = innov;
}

NeuralNetwork::~NeuralNetwork(){
  delete bias;
  
  for (int i = 0 ; i < sensor.size() ; ++i){
    delete sensor[i];
  }
  
  for (int i = 0 ; i < hidden.size() ; ++i){
    delete hidden[i];
  }
  
  for (int i = 0 ; i < output.size() ; ++i){
    delete output[i];
  }
}


void NeuralNetwork::evaluate(vector<double> input){
  if (sensor.size() != input.size()){
    fprintf(stderr,"Number of sensor nuerons does not match with the number ofinputs: Sensor: %lu, Input: %lu", sensor.size(), input.size());
    
  }
  bias->evaluate();
  for (int i = 0 ; i < sensor.size() ; ++i){
    sensor[i]->value = input[i];
    sensor[i]->evaluate();
  }
}



void NeuralNetwork::mutate(){
  
  int factor = (int)(100* (1+3*cosigmoid(abs(fitness-gBestFitness))));
  int i = rand() % factor;
  if ( i < wProb){
    bias->mutate(min, max);
    for (int i = 0 ; i < sensor.size() ; ++i){
      sensor[i]->mutate(min, max);
    }
    for (int i = 0 ; i < hidden.size() ; ++i){
      hidden[i]->mutate(min, max);
    }
    wm++;
  } else if (i < cProb){
    addConnection();
    cm++;
  } else if (i < nProb){
    addNode();
    nm++;
  }
}

Neuron *NeuralNetwork::searchHiddenById(int id){
  
  if (bias->id == id) return bias;
  
  for (int i = 0 ; i < sensor.size() ;++i){
    if (sensor[i]->id == id) return sensor[i];
  }
  
  for (int i = 0 ; i < output.size() ;++i){
    if (output[i]->id == id) return output[i];
  }
  
  for (int i = 0 ; i < hidden.size() ;++i){
    if (hidden[i]->id == id) return hidden[i];
  }
  return NULL;
}

void NeuralNetwork::addConnection(){
  
  uint64_t r = rand() % (sensor.size() + hidden.size() + 1);
  
  if (r == 0){
    uint64_t r1 = rand() % (hidden.size() + output.size());
    if (r1 < hidden.size())
    {
      newConnection(bias, hidden[r1]);
    } else {
      newConnection(bias, output[r1 - hidden.size()]);
    }
  }
  else if (r < sensor.size()+1){
    uint64_t r1 = rand() % (hidden.size() + output.size());
    if (r1 < hidden.size())
    {
      newConnection(sensor[r-1], hidden[r1]);
    } else {
      newConnection(sensor[r-1], output[r1 - hidden.size()]);
    }
  } else {
    r = r - sensor.size() - 1;
    uint64_t r1;
    do {
      r1 = rand() % (hidden.size() + output.size());
    } while(r == r1);
    
    if (r1 < hidden.size())
    {
      if (r > r1) {
        newConnection(hidden[r1], hidden[r]);
      } else {
        newConnection(hidden[r], hidden[r1]);
      }
    } else {
      newConnection(hidden[r], output[r1 - hidden.size()]);
    }
  }
}

void NeuralNetwork::newCustonConnection(Neuron *n1, Neuron *n2, double weight, int innov, bool enable){
  for (int i = 0 ; i < n1->connections.size(); ++i){
    if (n1->connections[i]->to->id == n2->id) return;
  }
  NeuronalConnection *c = new NeuronalConnection(weight, n1, n2, innov);
  connections.push_back(c);
  c->setEnable(enable);
  
  int j = 0;
  j++;
}
void NeuralNetwork::newConnection(Neuron *n1, Neuron *n2){
  for (int i = 0 ; i < n1->connections.size(); ++i){
    if (n1->connections[i]->to->id == n2->id) return;
  }
  connections.push_back(new NeuronalConnection(fRand(min, max), n1, n2, globalInnov++));
}

void NeuralNetwork::addNode() {
  uint64_t r;
  do {
    r = rand() % connections.size();
  } while (connections[r]->from == bias);
  
  Neuron *from = connections[r]->from;
  Neuron *to   = connections[r]->to;
  
  Neuron *newNode = new Neuron(kHidden, neuronId++);
  hidden.push_back(newNode);
  connections.push_back(new NeuronalConnection(fRand(min, max), from, newNode, globalInnov++));
  connections.push_back(new NeuronalConnection(fRand(min, max), newNode, to,   globalInnov++));
  
  connections[r]->setEnable(false);
  
}

bool NeuralNetwork::hasLoop(){
  bias->evaluate();
  for (int i = 0 ; i < sensor.size() ; ++i){
    sensor[i]->evaluate();
  }
  
  for (int i = 0 ; i < output.size() ; ++i){
    if (output[i]->nImpulses > 0 && output[i]->nImpulses != output[i]->inputs)
      return true;
  }
  
  return false;
}


/**********
 * Specie *
 **********/

template<> int SpecieT<vector<NeuralNetwork*>>::timeout()
{
  if (oldShrdFitness == 0){
    oldShrdFitness = sharedFitness;
  }
  else if (sharedFitness > oldShrdFitness && this->size() > 1){
    _timeout = 20;
    oldShrdFitness = sharedFitness;
  }
  else --_timeout;
  
  return _timeout;
}


/**************
 * Population *
 **************/

Population::Population (int initialSize, int inputs, int outputs) {
  Specie sp1;
  for (int i = 0 ; i < initialSize ; ++i){
    NeuralNetwork *nn = new NeuralNetwork(inputs, outputs);
    nn->specie = 0;
    sp1.push_back(nn);
  }
  population = initialSize;
  species.push_back(sp1);
}


void Population::classify (NeuralNetwork *nn){
  for (int i = 0 ; i < species.size() ; ++i){
    NeuralNetwork *aux = species[i][rand() % species[i].size()];
    double d = calculateDistance(nn, aux);
    if (d < minCompatibility) {
      species[i].push_back(nn);
      nn->specie = i+1;
      return;
    }
  }
  Specie s;
  s.push_back(nn);
  species.push_back(s);
  nn->specie = (int)species.size();
}


double Population::calculateDistance(NeuralNetwork *nn1, NeuralNetwork *nn2){
  double W = 0;
  double E = 0;
  double D = 0;
  double N = 0;
  
  int matches = 0;
  
  unsigned long i = 0, j = 0;
  unsigned long size1 = nn1->connections.size();
  unsigned long size2 = nn2->connections.size();
  while (1){
    if (nn1->connections[i]->innov == nn2->connections[j]->innov){
      W += abs(nn1->connections[i]->weight - nn2->connections[j]->weight);
      matches++;
      i++;
      j++;
    } else if (nn1->connections[i]->innov < nn2->connections[j]->innov){
      i++;
      D++;
    } else {
      j++;
      D++;
    }
    
    if (size1 == i){
      j = size2;
      N = (int)j;
      break;
    } else if (size2 == j){
      i = size1;
      N = (int)i;
      break;
    }
  }
  
  E = abs((int)(i-j));
  
//  if (N < 20) N = 1;
  
  return (c1*E + c2*D)/N + (c3*W)/matches;
}

void Population::train(){
  for (int i = 0 ; i < species.size() ; ++i){
    for (int j = 0 ; j < species[i].size() ; ++j){
      species[i][j]->mutate();
    }
  }
  calculateFitness();
  crossOver();
  generation++;
}


void Population::calculateFitness(){
  gBestFitness = 0;
  double totalFitness = 1;
  double specieFitness;
  population = 0;
  
  for (int i = 0 ; i < species.size() ; ++i){
    specieFitness = 0;

    for (int j = 0 ; j < species[i].size() ; ++j){
      if (species[i][j]->hasLoop()){
        species[i][j]->ill = true;
      } else {
        double fit = fitness(species[i][j]);
        species[i][j]->fitness = fit;
        specieFitness += species[i][j]->fitness;
        if (fit > gBestFitness) {
          gBestFitness = fit;
          gBestNN = species[i][j];
        }
      }
    }
    for (int j = 0 ; j < species[i].size() ; ++j){
      if (species[i][j]->ill){
        delete species[i][j];
        species[i][j] = species[i][0];
        species[i].erase(species[i].begin());
      }
    }
    if (species[i].size() == 0) {
      species[i].sharedFitness = 0;
    } else{
      species[i].sharedFitness = specieFitness/species[i].size();
    }
    
    totalFitness += species[i].sharedFitness;
    
  }
  
  for (vector<Specie>::iterator i = species.begin() ; i != species.end() ; ++i){
    if (i->timeout() == 0 && i->size() == 1){
      species.erase(i);
    } else {
      population += i->size();
    }
  }
  int tenPercent = population / 10;
  if (tenPercent > 0){
    for (int i = 0 ; i < species.size() ; ++i){
      species[i].offsprings = (int) (species[i].sharedFitness*tenPercent/totalFitness) + 1;
      if (species[i].offsprings > 1000){
        cout << "Total Fit: " << totalFitness;
        cout << "\n 10%: " << tenPercent;
        cout <<"\n Shared Fit: " << species[i].sharedFitness;
        cout << "\n";
      }
    }
  } else {
    for (int i = 0 ; i < species.size() ; ++i){
      species[i].offsprings =  1;
    }
  }
}

void Population::_calculateFitness(){
  gBestFitness = 0;
  double specieFitness;
  double totalFitness = 0;
  population = 0;
  for (int i = 0 ; i < species.size() ; ++i){
    specieFitness = 0;
    
    for (int j = 0 ; j < species[i].size() ; ++j){
      if (species[i][j]->hasLoop()){
        species[i][j]->ill = true;
      } else {
        double fit = species[i][j]->fitness;
        specieFitness += species[i][j]->fitness;
        if (fit > gBestFitness) gBestFitness = fit;
      }
    }
    for (int j = 0 ; j < species[i].size() ; ++j){
      if (species[i][j]->ill){
        delete species[i][j];
        species[i][j] = species[i][0];
        species[i].erase(species[i].begin());
      }
    }
    species[i].sharedFitness = specieFitness/species[i].size();
    totalFitness += species[i].sharedFitness;
  }
  
  for (vector<Specie>::iterator i = species.begin() ; i != species.end() ; ++i){
    if (i->timeout() == 0 && i->size() == 1){
      species.erase(i);
    } else {
      population += i->size();
    }
  }
  
  int tenPercent = population / 10;
  if (tenPercent > 0){
    for (int i = 0 ; i < species.size() ; ++i){
      species[i].offsprings = (int) (species[i].sharedFitness*tenPercent/totalFitness) + 1;
      if (species[i].offsprings > tenPercent)
        species[i].offsprings = 1;
    }
  } else {
    for (int i = 0 ; i < species.size() ; ++i){
      species[i].offsprings =  1;
    }
  }
}

void Population::setupParameters(double minCompatibility, double c1, double c2, double c3, double maxFitness , int _wProb, int _cProb, int _nProb){
  this->c1 = c1;
  this->c2 = c2;
  this->c3 = c3;
  this->minCompatibility = minCompatibility;
  this->maxFitness = maxFitness;
  wProb = _wProb;
  cProb = wProb + _cProb;
  nProb = cProb + _nProb;
}


void Population::crossOver(){
  NeuralNetwork *aux;
  int j = 0;
  for (int i = 0 ; i < species.size() ; ++i){
    sort(species[i].begin(), species[i].end(), compNN);
  }
  for (int i = 0 ; i < species.size() ; ++i){
    if (species[i].size() > 30 && species[i].offsprings > 5){
      for (j = 0 ; j < species[i].offsprings-5 ; ++j){
        if (species[i].size() > 0){
          delete species[i][0];
          species[i].erase(species[i].begin());
        }
      }
    }
  }
  j = 0;
  int size = (int)species.size();
  for (int i = 0 ; i < size ; ++i){
    if (species[j].size() == 0){
      species.erase(species.begin()+j);
    } else {
      j++;
    }
  }
  
  for (int i = 0 ; i < species.size() ; ++i){
    int s = (int)species[i].size() - 1;
    for (j = 0 ; j < species[i].offsprings ; ++j){
      if (s - 2*j - 1 >= 0){
        int r = rand() % 100;
        
        if (r < 5){
          do {
            r = rand() % species.size();
          } while(r == i && species.size() > 1);
          
          int s2 = (int)species[r].size() - 2*j - 2;
          
          if (s2 >= 0){
            aux = cross(species[i][s - 2*j], species[r][s2]);
          } else {
            goto l;
          }
          
        } else if (r < 10){
          do {
            r = rand() % species.size();
          } while(r == i && species.size() > 1);
          
          int s2 = (int)species[r].size() - 2*j - 1;
          
          if (s2 >= 0){
            
            aux = cross(species[r][s2], species[i][s - 2*j - 1]);
          } else {
            goto l;
          }
          
        }
        else {
        l:aux = cross(species[i][s - 2*j], species[i][s - 2*j - 1]);
          classify(aux);
        }
      }
    }
  }
  
  
}

NeuralNetwork *Population::cross(NeuralNetwork *nn1, NeuralNetwork *nn2){
  NeuralNetwork *newNN = new NeuralNetwork();
  
  
  int i = 0, j = 0;
  newNN->bias = new Neuron(nn1->bias->type, nn1->bias->id);
  Neuron *n, *m;
  for (int i = 0 ; i < nn1->sensor.size() ; ++i){
    n = new Neuron(nn1->sensor[i]->type, nn1->sensor[i]->id);
    newNN->sensor.push_back(n);
  }
  
  newNN->max = (sqrt(2.0 / (double)newNN->sensor.size()));
  newNN->min = -newNN->max;
  
  for (int i = 0 ; i < nn1->output.size() ; ++i){
    n = new Neuron(nn1->output[i]->type, nn1->output[i]->id);
    newNN->output.push_back(n);
  }
  
  while (i < nn1->connections.size() || j < nn2->connections.size()){
    NeuronalConnection *c1 = nn1->connections[i];
    NeuronalConnection *c2 = nn2->connections[j];
    
    if (i < nn1->connections.size() && j < nn2->connections.size()){
      if (c1->innov == c2->innov){
        n = newNN->searchHiddenById(c1->from->id);
        if (n == NULL){
          n = new Neuron(kHidden, c1->from->id);
          newNN->hidden.push_back(n);
        }
        m = newNN->searchHiddenById(c2->to->id);
        if (m == NULL){
          m = new Neuron(kHidden, c2->to->id);
          newNN->hidden.push_back(m);
        }
        double bestWeight;
        bool enable;
        if(nn1->fitness < nn2->fitness) {
          bestWeight = c2->weight;
          enable = c2->isEnable();
        } else {
          bestWeight = c1->weight;
          enable = c1->isEnable();
        }
        newNN->newCustonConnection(n, m, bestWeight, (int)c1->innov, enable);
        i++;
        j++;
      } else if (c1->innov < c2->innov) {
        crossAux(newNN, c1, &i);
      } else {
        crossAux(newNN, c2, &j);
      }
    } else if (i < nn1->connections.size()){
      crossAux(newNN, c1, &i);
    } else if (j < nn2->connections.size()){
      crossAux(newNN, c2, &j);
    }
    
  }
  return newNN;
}

void Population::crossAux(NeuralNetwork *newNN, NeuronalConnection *c, int *i){
  Neuron *n, *m;
  n = newNN->searchHiddenById(c->from->id);
  if (n == NULL){
    n = new Neuron(kHidden, c->from->id);
    newNN->hidden.push_back(n);
  }
  m = newNN->searchHiddenById(c->to->id);
  if (m == NULL){
    m = new Neuron(kHidden, c->to->id);
    newNN->hidden.push_back(m);
  }
  newNN->newCustonConnection(n, m, c->weight, (int)c->innov, c->isEnable());
  
  (*i)++;
}




template<class Archive>
void NeuronalConnection::serialize(Archive & ar, const unsigned int version)
{
  TAG(ar, innov);
  TAG(ar, enable);
  TAG(ar, weight);
  TAG(ar, from);
  TAG(ar, to);
}

template<class Archive>
void Neuron::serialize(Archive & ar, const unsigned int version)
{
  TAG(ar, type);
  TAG(ar, value);
  TAG(ar, inputs);
  TAG(ar, nImpulses);
  TAG(ar, id);
  TAG(ar, connections);
}


template<class Archive>
void NeuralNetwork::save(Archive & ar, const unsigned int version) const
{
  TAG(ar, sensor);
  TAG(ar, hidden);
  TAG(ar, output);
  TAG(ar, bias);
  TAG(ar, ill);
  TAG(ar, globalInnov);
  TAG(ar, min);
  TAG(ar, max);
  TAG(ar, specie);
  TAG(ar, fitness);
  TAG(ar, neuronId);
  TAG(ar, globalInnov);
  TAG(ar, connections);
}

template<class Archive>
void NeuralNetwork::load(Archive & ar, const unsigned int version){
  TAG(ar, sensor);
  TAG(ar, hidden);
  TAG(ar, output);
  TAG(ar, bias);
  TAG(ar, ill);
  TAG(ar, globalInnov);
  TAG(ar, min);
  TAG(ar, max);
  TAG(ar, specie);
  TAG(ar, fitness);
  TAG(ar, neuronId);
  TAG(ar, globalInnov);
  TAG(ar, connections);
  
  if (fitness > gBestFitness){
    gBestFitness = fitness;
  }
}

template<class Archive>
void Population::serialize(Archive & ar, const unsigned int version) {
  TAG(ar, c1);
  TAG(ar, c2);
  TAG(ar, c3);
  TAG(ar, minCompatibility);
  TAG(ar, species);
  TAG(ar, generation);
}




void savePopulation(string file, Population *p){
  std::ofstream ofs(file);
  assert(ofs.good());
  
  OUT_ARCHIVE oa(ofs);
  
  TAG_OA(oa, p);
  ofs.close();
}

Population *loadPopulation(string filename){
  Population *p = NULL;
  std::ifstream ifs(filename);
  assert(ifs.good());
  
  IN_ARCHIVE ia(ifs);
  
  TAG_IA(ia,p);
  
  ifs.close();
  return p;
}

