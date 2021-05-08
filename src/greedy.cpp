#include "../lib/greedy.hpp"

Mdp Greedy::computeSolution(Mdp object) {
  std::vector<Element> elem = object.getSet();
  std::vector<float> centre = object.calculateCentre(elem);
  do {
    int index = furthestElement(centre, elem, object);
    object.solution.push_back(elem[index]);
    elem.erase(elem.begin() + index);
    centre = object.calculateCentre(object.solution);
  } while (object.solution.size() < object.getM());
  object.solution = getLocalOptimal(object);
  object.printMdp();
  return object;
}

int Greedy::furthestElement(std::vector<float> centre, std::vector<Element> set, Mdp object) {
  float maximumDistance = 0;
  int index = -1;
  for (int i = 0; i < set.size(); i++) {
    float distance = object.calculateDistance(centre, set[i].getPosition());
    if (distance >= maximumDistance) {
      maximumDistance = distance;
      index = i;
    }
  }
  return index;
}

std::vector<Element> Greedy::getLocalOptimal(Mdp object) {
  bool improvement = false;
  int i = 0;
  do {
    improvement = greedyChange(object);
    i++;
  } while (improvement);
  return object.solution;
}

bool Greedy::greedyChange(Mdp& object) {
  bool improvement = false;
  Mdp originalCopy;
  Mdp bestMdp = object;
  float bestZ = object.calculateZ();
  originalCopy = object;
  for (int i = 0; i < object.solution.size(); i++) {
    for (int j = 0; j < object.getSet().size(); j++) {
      object.solution.erase(object.solution.begin() + i);
      object.solution.insert(object.solution.begin() + i, object.getSet()[j]);
      float tmpZ = object.calculateZ();
      if (tmpZ > bestZ) {
        bestMdp = object;
        bestZ = tmpZ;
        improvement = true;
      }
    }
    object = originalCopy;
  }
  //bestMdp.printMdp();
  object = bestMdp;
  return improvement;
}