#include "Population.hpp"

Population::Population(float mutationRate, int popmax, Target *target) {
  this->mutationRate = mutationRate;
  this->popmax = popmax;
  this->target = target;
  this->chromosomes = (DNA**) std::malloc(popmax * sizeof (DNA*));

  for(int i = 0; i < popmax; i++) {
    this->chromosomes[i] = new DNA(mutationRate, target);
  }
}


void Population::print() {
  std::cout << std::fixed;
  std::cout.precision(4);
  for(int i = 0; i < this->popmax; i++) {
    std::cout << this->chromosomes[i]->getGenes() << " " <<
       this->chromosomes[i]->getFitness() << std::endl;
  }
}

float map(float value, float maxFitness) {
  return value / maxFitness;
}

void Population::naturalSelection() {
  float maxFitness = 0, buffer;
  int n;

  matingPool.erase(matingPool.begin(), matingPool.end());

  for(int i = 0; i < popmax; i++) {
    if(this->chromosomes[i]->getFitness() > maxFitness) {
      maxFitness = this->chromosomes[i]->getFitness();
    }
  }
  
  for(int i = 0; i < popmax; i++) {
    buffer = map(this->chromosomes[i]->getFitness(), maxFitness);
    n = buffer * 100;
    for(int i = 0; i < n; i++) {
      matingPool.push_back(this->chromosomes[i]);
    }
  }
  std::cout << matingPool.size() << std::endl;
}

void Population::generate() {
  std::list<DNA*>::iterator parentA, parentB;
  int a, b;
    
  for(int i = 0; i < popmax; i++) {
    a = std::rand() % matingPool.size();
    b = std::rand() % matingPool.size();
  
    parentA = matingPool.begin();
    parentB = matingPool.begin();
  
    for(int j = 0; j < a; j++) {
      parentA++;
    }

    for(int j = 0; j < b; j++) {
      parentB++;
    }
    
    this->chromosomes[i] = (*parentA)->crossover((*parentB));
  }
}

void Population::calcFitness() {
  for(int i = 0; i < popmax; i++) {
    this->chromosomes[i]->calcFitness();
  }
}

bool Population::isFinished() {
  for(int i = 0; i < popmax; i++) {
    if(this->chromosomes[i]->getFitness() == 1) {
      return true;
    }
  }
  return false;
}
