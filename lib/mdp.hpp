#ifndef MDP
#define MDP

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "./element.hpp"

class Mdp {
  private:
    int n;
    int k;
    int m;
  /** Vector of points for the problem
   *  @property
   */
    std::vector<Element> set;
  public:
  /** Vector of points for the solution
   *  @property
   */
    std::vector<Element> solution;
    Mdp();
    Mdp(std::string fileName, int mInput);
    ~Mdp();
  /** Calculates the centre of some given points
   *  @param inputSet - set of points.
   *  @return vector of float defining the centre
   */
    std::vector<float> calculateCentre(std::vector<Element> inputSet);
    std::vector<Element>& getSet();
    int getM();
  /** Calculates the distance between two points
   *  @param pointA
   *  @param pointB
   *  @return distance
   */
    float calculateDistance(std::vector<float> pointA, std::vector<float> pointB);
  /** Calculates the z for a given solution
   *  @return z
   */
    float calculateZ();
    Mdp& operator=(const Mdp& other);
    void printMdp();
    std::string toString();
};


#endif