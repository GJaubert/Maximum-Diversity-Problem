#ifndef STRATEGY
#define STRATEGY

#include "./mdp.hpp"

class Strategy {
  public:
    virtual void computeSolution(Mdp object) = 0;
};

#endif