#ifndef BRANCHBOUND
#define BRANCHBOUND

#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <memory>
#include <algorithm>
#include <map>
#include "./mdp.hpp"
#include "./greedy.hpp"
#include "./grasp.hpp"

class BranchBound {
  private:
    std::vector<Mdp> solutions;
    std::vector<Element> allPoints;
    std::map<float, Element> zSelMap;
    int m;
  public:
    BranchBound();
    ~BranchBound();
    Mdp computeSolution(Mdp object, int constructionType);
    Mdp constructionPhase(Mdp object, int mode);
    Mdp grasp(Mdp object);
    Mdp greedy(Mdp object);
    float calculateUB(Mdp object);
    float calculateUB2(Mdp object, std::vector<Element> unselected);
    float calculateUB3(Mdp object, std::vector<Element> unselected);
    std::vector<float> zSelVector(Mdp object, std::vector<Element> unselected);
    std::vector<float> sort(std::vector<float> selv);
    std::vector<float> zUnselVector(Mdp object, std::vector<Element> unselected);
};

#endif