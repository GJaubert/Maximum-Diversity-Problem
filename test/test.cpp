#include "../lib/mdp.hpp"
#include "../lib/strategy.hpp"
#include "../lib/greedy.hpp"
#include "../lib/grasp.hpp"
#include "../lib/branch-bound.hpp"
#include <memory>
#include <chrono>
#include <fstream>
using namespace std::chrono;

int main(int args, char* argv[]) {
  try {
    Mdp test(argv[1], std::stoi(argv[2]));
    // std::shared_ptr<BranchBound> ptr;
    // ptr = std::make_shared<BranchBound>();
    // ptr->computeSolution(test, 0);
    BranchBound branch;
    test = branch.computeSolution(test, 0);
    //test.printMdp();
    std::cout << "Nodos: " << branch.getGeneratedNodes() << "\n";
    return 0;
  } catch(std::string err) {
    std::cout << err;
  }
}

//Mdp test(argv[1], std::stoi(argv[2]));