#ifndef STRATEGY
#define STRATEGY

#include "./mdp.hpp"

class Strategy {
  public:
    virtual Mdp computeSolution(Mdp object) = 0;
};

#endif