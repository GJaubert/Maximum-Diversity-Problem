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

/**
 * This struct is used to represent a nodes
 */
struct Node {
  Mdp mdp;
  float UB;
};

class BranchBound {
  private:
  /**
   * @property Vector of total solutions we found, the best
   * solution will be in position 0
   */
    std::vector<Mdp> solutions;
  /**
   * @property vector of all points in the problem
   */
    std::vector<Element> allPoints;
  /**
   * @property Number of generated nodes
   */
    int generatedNodes;
  /**
   * @property true if the algorithm has to finish
   */
    bool finish;
  /**
   * @property Current minimum bound
   */
    float bound;
    int m;
  public:
    BranchBound();
    ~BranchBound();
  /** Executes Branch and Bound algorithm
   *  @param object - object of type Mdp that stores all information about the problem
   *  @param constructionType - type of construction phase we want
   */
    Mdp computeSolution(Mdp object, int constructionType);
  /** Finds the local optimal for the given solution
   *  @param object
   *  @param mode of construction phase
   *  @return mdp object
   */
    Mdp constructionPhase(Mdp object, int mode);
  /** Executes the grasp algorith
   *  @param object
   *  @return object with grasp solution
   */
    Mdp grasp(Mdp object);
  /** Executes the greedy algorith
   *  @param object
   *  @return object with greedy solution
   */
    Mdp greedy(Mdp object);
  /** Executes BranchBound with lower UB strat
   *  @param object
   *  @return Mdp object 
   */
    Mdp lowerUbStrat(Mdp object);
  /** Executes BranchBound with deepest node strat
   *  @param object
   *  @return Mdp object 
   */
    Mdp deepestNodeStrat(Mdp object);
  /** Calculates UB with proposition 1 and 2 of the paper for this practice.
   *  @param object
   *  @return Mdp object 
   */
    float calculateUB(Mdp object);
  /** Calculates UB2 adding m - k elements from sel vector
   *  @param object
   *  @param unselected vector of unselected nodes
   *  @return float with UB2
   */
    float calculateUB2(Mdp object, std::vector<Element> unselected);
  /** Calculates UB3 adding m - k elements from unsel vector
   *  @param object
   *  @param unselected vector of unselected nodes
   *  @return float with UB3
   */           
    float calculateUB3(Mdp object, std::vector<Element> unselected);
  /** Calculates vector with zsel for all unselected nodes
   *  @param object
   *  @param unselected vector of unselected nodes
   *  @return vector with all zsel
   */   
    std::vector<float> zSelVector(Mdp object, std::vector<Element> unselected);
  /** Calculates vector with zunSel for all unselected nodes
   *  @param object
   *  @param unselected vector of unselected nodes
   *  @return vector with all zunSel
   */  
    std::vector<float> zUnselVector(Mdp object, std::vector<Element> unselected);
  /** Sorts a vector in descending order
   *  @param selv vector we want to sort
   *  @return sorted vector
   */   
    std::vector<float> sort(std::vector<float> selv);
  /** Analyze a node and adds all candidates from thath node
   *  @param queue vector of partial of complete solutions
   *  @param object
   *  @param strat strategy we want to use for finding the candidate node
   */  
    void addCandidates(std::vector<Node>& queue, Mdp object, int strat);
  /** Finds the node with lowest UB
   *  @param queue vector of partial of complete solutions
   *  @return index of the lowest UB node
   */ 
    int selectLowestNode(std::vector<Node> queue);
    int selectSecondHighestNode(std::vector<Node> queue); // MODIFICACION
  /** Finds the node with the biggest depth on the tree
   *  @param queue vector of partial of complete solutions
   *  @return index of the node with the biggest depth on the tree
   */ 
    int selectDeepestNode(std::vector<Node>& queue);
  /** Prune nodes with UB below minimum bound
   *  @param queue vector of partial of complete solutions
   */ 
    void pruneNodes(std::vector<Node>& queue);
    int getGeneratedNodes();
};

#endif