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
    std::vector<Element> set;
  public:
    std::vector<Element> solution;
    Mdp();
    Mdp(std::string fileName, int mInput);
    ~Mdp();
    std::vector<float> calculateCentre(std::vector<Element> inputSet);
    std::vector<Element>& getSet();
    int getM();
    float calculateDistance(std::vector<float> pointA, std::vector<float> pointB);
    float calculateZ();
    Mdp& operator=(const Mdp& other);
    void printMdp();
    std::string toString();
};


#endif