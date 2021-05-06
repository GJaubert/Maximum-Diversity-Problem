#include "../lib/mdp.hpp"

Mdp::Mdp(std::string fileName, int mInput) {
  m = mInput;
  std::ifstream file;
  std::string tmpString;
  file.open(fileName);
  if (!file.is_open()) {
    throw std::string("Cannot open file\n");
  }
  file >> n;
  file >> k;
  for (int i = 0; i < n; i++) {
    std::vector<float> tmpvector;
    for (int j = 0; j < k; j++) {
      file >> tmpString;
      tmpvector.push_back(std::stof(tmpString));
    }
    Element element(tmpvector);
    set.push_back(element);
  }
}

Mdp::Mdp() {}

Mdp::~Mdp(){}

std::vector<float> Mdp::calculateCentre(std::vector<Element> inputSet) {
  float summation = 0;
  std::vector<float> centre;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < inputSet.size(); j++) {
      summation += inputSet[j].getPosition()[i];
    }
    centre.push_back(summation / inputSet.size());
    summation = 0;
  }
  return centre;
}

std::vector<Element> Mdp::getSet() {
  return set;
}

int Mdp::getM() {
  return m;
}

float Mdp::calculateDistance(std::vector<float> pointA, std::vector<float> pointB) {
  float summation = 0;
  for (int i = 0; i < k; i++) {
    summation += pow(pointA[i] - pointB[i], 2);
  }
  return sqrt(summation);
}

float Mdp::calculateZ() {
  float z = 0;
  for (int i = 0; i < solution.size() - 1; i++) {
    for (int j = i + 1; j < solution.size(); j++) {
      z += calculateDistance(solution[i].getPosition(), solution[j].getPosition());
    }
  }
 // std::cout << z<<"\n";
  return z;
}

Mdp& Mdp::operator=(const Mdp& other) {
  n = other.n;
  k = other.k;
  m = other.m;
  set = other.set;
  solution = other.solution;
  return *this;
}

void Mdp::printMdp() {
  for (int k = 0; k < solution.size(); k++) {
    solution[k].print();
  }
  std::cout << "Z: " << calculateZ() << "\n";
}
