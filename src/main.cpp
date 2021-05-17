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
    std::ofstream file;
    file.open("tables/BranchBound-tables.md", std::ofstream::app);
    std::vector<std::string> sizes = {"15", "20", "30"};
    file << "| ID | n | k | m | Max_iter | z | S | CPU(μs) | Nodes generated\n";
    file << "|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|\n";
    //std::shared_ptr<Strategy> ptr;
    // ptr = std::make_shared<Greedy>();
    // ptr->computeSolution(test);
    // ptr = std::make_shared<Grasp>();
    Mdp result;
    for (int s = 0; s < sizes.size(); s++) {
      int k = 3;
      for (int m = 2; m < 6; m++) {
        std::string fileName = "data/max_div_";
        fileName += sizes[s];
        fileName += "_";
        fileName += std::to_string(k);
        fileName += ".txt";
        //for (int lrcSize = 2; lrcSize < 4; lrcSize++) {
          Mdp newMdp(fileName, m);
          BranchBound branch;
          //ptr = std::make_shared<Grasp>(lrcSize);
          auto start = high_resolution_clock::now();
          //result = ptr->computeSolution(newMdp);
          result = branch.computeSolution(newMdp, 1);
          auto stop = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(stop - start);
          file << fileName << "|" << sizes[s] << "|" << k << "|" << m << "|10|"  << result.calculateZ() << "|" << result.toString() << "|" << duration.count() << "|" << branch.getGeneratedNodes() << "\n"; 
        //}
      }
    }
    return 0;
  } catch(std::string err) {
    std::cout << err;
  }
}