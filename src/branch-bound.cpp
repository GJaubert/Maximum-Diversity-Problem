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
  std::vector<Element> unselected;
  for (int i = 0; i < allPoints.size(); i++) {
    for (int j = 0; j < solutions[0].solution.size(); j++) {
      if (allPoints[i].getPosition() == solutions[0].solution[j].getPosition()) {
        break;
      } else if (j == solutions[0].solution.size() - 1) {
        unselected.push_back(allPoints[i]);
      }
    }
  }
  float z1 = object.calculateZ();
  std::cout << z1 << "\n";
  float z2 = calculateUB2(object, unselected);
  std::cout << z2 << "\n";
  float z3 = calculateUB3(object, unselected);
  return z1;
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
  // for (int i = 0; i < selv.size(); i++) {
  //   std::cout << selv[i] << "\n";
  // }
  std::sort(selv.begin(), selv.end());
  std::reverse(selv.begin(),selv.end());
  return selv;
}

float BranchBound::calculateUB2(Mdp object, std::vector<Element> unselected) {  // siempre que trabajemos con solution.size nos referimos a k
  int UB2 = 0;
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
    std::cout << "dUnsel: \n";
    for (int l = 0; l < dUnsel.size(); l++) {
      std::cout << dUnsel[l] << " ";
    }
    std::cout << "\nLos que se suman de dUnsel: \n";
    for (int k = 0; k < m - (int)object.solution.size() - 1; k++) {
      newZ += dUnsel[k];
      std::cout << dUnsel[k] << " ";
    }
    std::cout << "\n";
    std::cout << "El numero que se divide entre dos: " << newZ << "\n\n";
    unselV.push_back(newZ * 0.5);
  }
  std::cout << "Unsel: \n";
  for (int i = 0; i < unselV.size(); i++) {
    std::cout << unselV[i] << " ";
  }
  std::cout << "\n";
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