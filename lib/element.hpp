#ifndef ELEMENT
#define ELEMENT

#include <iostream>
#include <vector>

class Element {
  private:
    std::vector<float> position;
  public:
    Element(std::vector<float>);
    ~Element();
    std::vector<float> getPosition();
    void print();
};

#endif