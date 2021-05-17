#ifndef ELEMENT
#define ELEMENT

#include <iostream>
#include <vector>

class Element {
  private:
  /** Position of the point
   *  @property
   */
    std::vector<float> position;
  public:
    Element(std::vector<float>);
    Element();
    ~Element();
    std::vector<float> getPosition();
    Element& operator=(const Element& other);
    void print();
};

#endif