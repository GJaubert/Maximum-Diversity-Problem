#ifndef GREEDY
#define GREEDY

#include "./strategy.hpp"

class Greedy : public Strategy{
  virtual void computeSolution(Mdp object);
  int furthestElement(std::vector<float> centre, std::vector<Element> set, Mdp object);
};

#endif