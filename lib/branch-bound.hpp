#ifndef BRANCHBOUND
#define BRANCHBOUND

#define BIG_NUMBER 99999

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

struct Node {
  Mdp mdp;
  float UB;
};

class BranchBound {
  private:
    std::vector<Mdp> solutions;
    std::vector<Element> allPoints;
    std::map<float, Element> zSelMap;
    int generatedNodes;
    bool finish;
    float bound;
    int m;
  public:
    BranchBound();
    ~BranchBound();
    Mdp computeSolution(Mdp object, int constructionType);
    Mdp constructionPhase(Mdp object, int mode);
    Mdp grasp(Mdp object);
    Mdp greedy(Mdp object);
    Mdp lowerUbStrat(Mdp object);
    Mdp deepestNodeStrat(Mdp object);
    float calculateUB(Mdp object);
    float calculateUB2(Mdp object, std::vector<Element> unselected);
    float calculateUB3(Mdp object, std::vector<Element> unselected);
    std::vector<float> zSelVector(Mdp object, std::vector<Element> unselected);
    std::vector<float> sort(std::vector<float> selv);
    std::vector<float> zUnselVector(Mdp object, std::vector<Element> unselected);
    void addCandidates(std::vector<Node>& queue, Mdp object, int strat);
    int selectLowestNode(std::vector<Node> queue);
    void pruneNodes(std::vector<Node>& queue);
    int selectDeepestNode(std::vector<Node>& queue);
    int getGeneratedNodes();
};

#endif