#include "../lib/grasp.hpp"

void Grasp::computeSolution(Mdp object) {
  srand(time(NULL));
  std::vector<Element> elem = object.getSet();
  std::vector<float> centre = object.calculateCentre(elem);
  do {
    object = insertFromLrc(object);
  } while (object.solution.size() < object.getM());
  //object.printMdp();
  //object.solution = getLocalOptimal(object);
  //object.printMdp();
}

Mdp Grasp::insertFromLrc(Mdp object) {
    std::vector<Element> elem = object.getSet();
    std::vector<Element> originalElem = elem;
    std::vector<float> centre = object.calculateCentre(elem);
    std::vector<Element> Lrc;
    std::vector<int> LrcIndexes;

    for (int i = 0; i < K; i++) {
      int index = furthestElement(centre, elem, object);
      std::cout << "insertado en lrc: ";
      elem[index].print();
      Lrc.push_back(elem[index]);
      LrcIndexes.push_back(index);
      elem.erase(elem.begin() + index);
      centre = object.calculateCentre(elem);  //descrubir como hacer para que cada
                                              //vez que se llame a esta funcion el centre 
                                              //sea el de la solucion y no del conjunot inicial
    }

    int randomIndex = rand() % Lrc.size();
    object.solution.push_back(Lrc[randomIndex]);
    std::cout << "insertado en solution: ";
    Lrc[randomIndex].print();
    Lrc.erase(Lrc.begin() + randomIndex); // borramos de lrc el que acabamosde introducir
    for (int i = 0; i < Lrc.size(); i++) { //resinsertamos lrc
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