#include "../lib/mdp.hpp"
#include "../lib/strategy.hpp"
#include "../lib/greedy.hpp"
#include "../lib/grasp.hpp"
#include <memory>
#include <chrono>
#include <fstream>
using namespace std::chrono;

int main(int args, char* argv[]) {
  try {
    Mdp test(argv[1], std::stoi(argv[2]));
    std::shared_ptr<Strategy> ptr;
    ptr = std::make_shared<Grasp>();
    ptr->computeSolution(test);
    return 0;
  } catch(std::string err) {
    std::cout << err;
  }
}

//Mdp test(argv[1], std::stoi(argv[2]));