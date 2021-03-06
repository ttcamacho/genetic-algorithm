#ifndef DNA_HPP
#define DNA_HPP

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Target.hpp"

class DNA {
  private:
    Target *target;;
    float fitness, mutationRate;
    char *genes;
  public:
    DNA(float mutationRate, Target *target);
    char* getGenes();
    float getFitness();
    char newChar();
    void calcFitness();
    DNA* crossover(DNA* parent);
    void mutation();
};

#endif
