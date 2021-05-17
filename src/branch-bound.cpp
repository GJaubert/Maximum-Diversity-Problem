#include "../lib/branch-bound.hpp"

BranchBound::BranchBound() {
  generatedNodes = 0;
}

BranchBound::~BranchBound() {}

Mdp BranchBound::computeSolution(Mdp object, int constructionType) {
  allPoints = object.getSet();
  finish = false;
  m = object.getM();
  Mdp firstSolution;
  firstSolution = constructionPhase(object, constructionType);
  solutions.push_back(firstSolution);
  bound = calculateUB(firstSolution);
  //object = lowerUbStrat(object);
  object = deepestNodeStrat(object);
  //std::cout << generatedNodes << " ";
  return object;
}

Mdp BranchBound::lowerUbStrat(Mdp object) {
  std::vector<Node> queue;
  do {
    //generatedNodes++;
    addCandidates(queue, object, 0);
    pruneNodes(queue);
    //std::cout << " pruned:" << queue.size();
  }
  while ((queue.size() > 0) && (finish == false));
  return solutions[0];
}

Mdp BranchBound::deepestNodeStrat(Mdp object) {
  std::vector<Node> queue;
  do {
    //generatedNodes++;
    addCandidates(queue, object, 1);
    pruneNodes(queue);
  }
  while ((queue.size() > 0) && (finish == false));
  return solutions[0];
}

Mdp BranchBound::constructionPhase(Mdp object, int mode) {
  switch(mode) {
    case 0:
      object = greedy(object);
      break;
    case 1:
      object = grasp(object);
      break;
    default:
      break;
  }
  return object;
}

void BranchBound::pruneNodes(std::vector<Node>& queue) {
  for (int i = 0; i < queue.size(); i++) {
    if (queue[i].UB < bound) {
      //std::cout << "UB: " << queue[i].UB << " bound general: " << bound << "\n";
      queue.erase(queue.begin() + i);
      i--;
    }
  }
}

void BranchBound::addCandidates(std::vector<Node>& queue, Mdp object, int strat) {
  if (queue.size() == 0) {
    for (int i = 0; i < allPoints.size() - m + 1; i++) {
      Mdp newMdp;
      newMdp = object;
      newMdp.solution.push_back(allPoints[i]);
      newMdp.getSet() = std::vector<Element>(newMdp.getSet().begin() + i, newMdp.getSet().end());
      //newMdp.getSet().erase(newMdp.getSet().begin() + i);
      Node newNode;
      newNode.mdp = newMdp;
      newNode.UB = calculateUB(newMdp);
      //std::cout << newNode.UB << "\n";
      queue.push_back(newNode);
    }
  } else {
    int index;
    switch (strat) {
      case 0:
        index = selectLowestNode(queue);
        break;
      case 1:
        index = selectDeepestNode(queue);
        break;
      default:
        break;
    }
    if (index == -1) {
      finish = true;
      return;
    }
    if (queue[index].mdp.solution.size() == m) {  //  hemos llegado a una solucion completa, la añadimos al nuevo bound
      float tmpBound = calculateUB(queue[index].mdp);
      solutions[0].solution = queue[index].mdp.solution;
     // std::cout << "mejora\n";
      bound = calculateUB(queue[index].mdp);
    } else {
      //std::cout << " " << queue[index].mdp.solution.size();
     // std::cout << "angel: " << allPoints.size() - (m - queue[index].mdp.solution.size()) - index + 1 << "\n";
      int pointPosition = allPoints.size() - queue[index].mdp.getSet().size();
      generatedNodes += allPoints.size() - (m - queue[index].mdp.solution.size()) - pointPosition + 1;
      for (int i = 0; i < allPoints.size() - (m - queue[index].mdp.solution.size()) - pointPosition + 1; i++) {
        //std::cout << "hola";
        Mdp newMdp;
        newMdp = queue[index].mdp;
        newMdp.solution.push_back(newMdp.getSet()[i]);
        newMdp.getSet() = std::vector<Element>(newMdp.getSet().begin() + i, newMdp.getSet().end());
        //newMdp.getSet().erase(newMdp.getSet().begin() + i);
        Node newNode;
        newNode.mdp = newMdp;
        newNode.UB = calculateUB(newMdp);
        queue.push_back(newNode);
      }
      //std::cout << queue[index].UB << " solution size: " << queue[index].mdp.solution.size() << "\n";
    }
    queue.erase(queue.begin() + index);
    //std::cout << " " <<  queue.size();
  }
}

int BranchBound::selectLowestNode(std::vector<Node> queue) {
  int index = -1;
  float lowestUB = BIG_NUMBER;
  for (int i = 0; i < queue.size(); i++) {
    if (queue[i].UB < lowestUB) {
      lowestUB = queue[i].UB;
      index = i;
    }
  }
  return index;
}

int BranchBound::selectDeepestNode(std::vector<Node>& queue) {
  int index = -1;
  float biggestDepth = 0;
  for (int i = 0; i < queue.size(); i++) {
    if (queue[i].mdp.solution.size() > biggestDepth) {
      biggestDepth = queue[i].mdp.solution.size();
      index = i;
    }
  }
  return index;
}

Mdp BranchBound::grasp(Mdp object) {
  std::shared_ptr<Grasp> ptr;
  ptr = std::make_shared<Grasp>(5);
  object = ptr->computeSolution(object);
  return object;
}

Mdp BranchBound::greedy(Mdp object) {
  std::shared_ptr<Greedy> ptr;
  ptr = std::make_shared<Greedy>();
  object = ptr->computeSolution(object);
  return object;
}

float BranchBound::calculateUB(Mdp object) {
  std::vector<Element> unselected;
  for (int i = 0; i < allPoints.size(); i++) {
    for (int j = 0; j < object.solution.size(); j++) {
      if (allPoints[i].getPosition() == object.solution[j].getPosition()) {
        break;
      } else if (j == object.solution.size() - 1) {
        unselected.push_back(allPoints[i]);
      }
    }
  }
  float z1 = object.calculateZ();
  //std::cout << "z1 " << z1 << "\n";
  float z2 = calculateUB2(object, unselected);
  //std::cout << "z2 " << z2 << "\n";
  float z3 = calculateUB3(object, unselected);
  //std::cout << "z3 " << z3 << "\n";
  return z1 + z2 + z3;
}

std::vector<float> BranchBound::zSelVector(Mdp object, std::vector<Element> unselected) {
  float z = 0;
  std::vector<float> z2Vector;
  for (int i = 0; i < unselected.size(); i++) {
    z = 0;
    for (int j = 0; j < object.solution.size(); j++) {
      z += object.calculateDistance(object.solution[j].getPosition(), unselected[i].getPosition());
    }
    z2Vector.push_back(z);
  }
  return z2Vector;
}

std::vector<float> BranchBound::sort(std::vector<float> selv) {
  std::sort(selv.begin(), selv.end());
  std::reverse(selv.begin(),selv.end());
  return selv;
}

float BranchBound::calculateUB2(Mdp object, std::vector<Element> unselected) {  // siempre que trabajemos con solution.size nos referimos a k
  float UB2 = 0;
  std::vector<float> selV;
  selV = zSelVector(object, unselected);
  selV = sort(selV);

  for (int i = 0; i < m - object.solution.size(); i++) {
    UB2 += selV[i];
  }
  return UB2;
}

std::vector<float> BranchBound::zUnselVector(Mdp object, std::vector<Element> unselected) {
  std::vector<float> unselV;
  float z;
  for (int i = 0; i < unselected.size(); i++) {
    z = 0;
    std::vector<float> dUnsel;
    for (int j = 0; j < unselected.size(); j++) {
      if (unselected[i].getPosition() == unselected[j].getPosition()) {
        continue;
      }
      dUnsel.push_back(object.calculateDistance(unselected[i].getPosition(), unselected[j].getPosition()));
    }
    float newZ = 0;
    dUnsel = sort(dUnsel);
    for (int k = 0; k < m - (int)object.solution.size() - 1; k++) {
      newZ += dUnsel[k];
    }
    unselV.push_back(newZ * 0.5);
  }
  unselV = sort(unselV);
  return unselV;
}


float BranchBound::calculateUB3(Mdp object, std::vector<Element> unselected) {
  float UB3 = 0;
  std::vector<float> unselV;
  unselV = zUnselVector(object, unselected);
  for (int i = 0; i < m - object.solution.size(); i++) {
    UB3 += unselV[i];
  }
  return UB3;
}

int BranchBound::getGeneratedNodes() {
  return generatedNodes;
}