#ifndef GRASP
#define GRASP
#define K 2

#include <time.h>
#include <chrono>
#include "./strategy.hpp"

class Grasp : public Strategy {
  virtual void computeSolution(Mdp object);
  int furthestElement(std::vector<float> centre, std::vector<Element> set, Mdp object);
  std::vector<Element> getLocalOptimal(Mdp object);
  bool greedyChange(Mdp& object);
  Mdp insertFromLrc(Mdp object);
};

#endif