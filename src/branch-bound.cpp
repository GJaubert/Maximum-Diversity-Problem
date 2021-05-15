#include "../lib/branch-bound.hpp"

BranchBound::BranchBound() {}

BranchBound::~BranchBound() {}

Mdp BranchBound::computeSolution(Mdp object, int constructionType) {
  allPoints = object.getSet();
  m = object.getM();
  Mdp firstSolution;
  firstSolution = constructionPhase(object, constructionType);
  solutions.push_back(firstSolution);
  float startingBound = calculateUB(firstSolution);
  return object;
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

Mdp BranchBound::grasp(Mdp object) {
  std::shared_ptr<Grasp> ptr;
  ptr = std::make_shared<Grasp>(2);
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
  float z1 = object.calculateZ();
  std::cout << z1 << "\n";
  float z2 = calculateUB2(object);
  std::cout << z2 << "\n";
  return z1;
}

std::vector<float> BranchBound::zSelVector(Mdp object) {
  float z = 0;
  std::vector<Element> unselected;
  std::vector<float> z2Vector;
  for (int i = 0; i < allPoints.size(); i++) {
    for (int j = 0; j < solutions[0].solution.size(); j++) {
      if (allPoints[i].getPosition() == solutions[0].solution[j].getPosition()) {
        break;
      } else if (j == solutions[0].solution.size() - 1) {
        unselected.push_back(allPoints[i]);
      }
    }
  }
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
  // for (int i = 0; i < selv.size(); i++) {
  //   std::cout << selv[i] << "\n";
  // }
  std::sort(selv.begin(), selv.end());
  std::reverse(selv.begin(),selv.end());
  return selv;
}

float BranchBound::calculateUB2(Mdp object) {  // siempre que trabajemos con solution.size nos referimos a k
  int UB2 = 0;
  std::vector<float> selv;
  selv = zSelVector(object);
  selv = sort(selv);
  for (int i = 0; i < m - object.solution.size(); i++) {
    UB2 += selv[i];
  }
  return UB2;
}
