#ifndef GREEDY
#define GREEDY

#include "./strategy.hpp"

class Greedy : public Strategy {
  public:
    virtual Mdp computeSolution(Mdp object);
    int furthestElement(std::vector<float> centre, std::vector<Element> set, Mdp object);
    std::vector<Element> getLocalOptimal(Mdp object);
    bool greedyChange(Mdp& object);
};

#endif