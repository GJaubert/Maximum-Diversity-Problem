#include "../lib/grasp.hpp"

Grasp::Grasp (int k) {
  k_ = k;
}

Mdp Grasp::computeSolution(Mdp object) {
  srand(time(NULL));
  Mdp best;
  Mdp original;
  best = object;
  original = object;
  for (int iter = 0; iter < MAX_ITER; iter++) {
    do {
      object = insertFromLrc(object);
    } while (object.solution.size() < object.getM());
    object.solution = getLocalOptimal(object);
    if (object.calculateZ() > best.calculateZ()) {
      best = object;
    }
    object = original;
  }
  return best;
}

Mdp Grasp::insertFromLrc(Mdp object) {
    std::vector<Element> elem = object.getSet();
    std::vector<Element> originalElem = elem;
    std::vector<Element> Lrc;
    std::vector<int> LrcIndexes;

    for (int i = 0; i < k_; i++) {
      std::vector<float> centre;
      if (object.solution.size() == 0) {
        centre = object.calculateCentre(elem);
      } else {
        centre = object.calculateCentre(object.solution);
      }
      int index = furthestElement(centre, elem, object);
      Lrc.push_back(elem[index]);
      LrcIndexes.push_back(index);
      elem.erase(elem.begin() + index);
    }   

    int randomIndex = rand() % Lrc.size();
    object.solution.push_back(Lrc[randomIndex]);
    Lrc.erase(Lrc.begin() + randomIndex); // borramos de lrc el que acabamos de introducir
    for (int i = 0; i < Lrc.size(); i++) { // reinsertamos lrc
      elem.push_back(Lrc[i]);
    }
    object.getSet() = elem;
   return object;
}

int Grasp::furthestElement(std::vector<float> centre, std::vector<Element> set, Mdp object) {
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

std::vector<Element> Grasp::getLocalOptimal(Mdp object) {
  bool improvement = false;
  int i = 0;
  do {
    improvement = greedyChange(object);
    i++;
  } while (improvement);
  //maeobject.printMdp();
  return object.solution;
}

bool Grasp::greedyChange(Mdp& object) {
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

        object.getSet().push_back(object.solution[i]);
        object.getSet().erase(object.getSet().begin() + j);
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