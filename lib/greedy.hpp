#ifndef GREEDY
#define GREEDY

#include "./strategy.hpp"

class Greedy : public Strategy {
  public:
  /** Executes greedy algorithm
   *  @param object - object of type Mdp that stores all information about the problem
   */
    virtual Mdp computeSolution(Mdp object);
  /** Finds the furthest element to a given centre
   *  @param centre - centre of gravity.
   *  @param set - set of points where we look for the furthest point
   *  @param object
   *  @return index respect to set of the furthest element
   */
    int furthestElement(std::vector<float> centre, std::vector<Element> set, Mdp object);
  /** Finds the local optimal for the given solution
   *  @param object
   *  @return solution of the local optimal
   */
    std::vector<Element> getLocalOptimal(Mdp object);
  /** Finds the best change for the local search
   *  @param object
   *  @return true if there has been and improvement
   */
    bool greedyChange(Mdp& object);
};

#endif