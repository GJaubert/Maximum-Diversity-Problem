#include "../lib/element.hpp"

Element::Element(std::vector<float> input) {
  position = input;
}

Element::Element() {}

Element::~Element(){}

void Element::print() {
  for (int i = 0; i < position.size(); i++) {
    std::cout << position[i] << " ";
  }
  std::cout << "\n";
}

std::vector<float> Element::getPosition() {
  return position;
}

Element& Element::operator=(const Element& other) {
  position = other.position;
}